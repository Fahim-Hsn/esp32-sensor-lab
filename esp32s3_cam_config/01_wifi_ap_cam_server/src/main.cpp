#include <Arduino.h>
#include <WiFi.h>
#include "esp_camera.h"
#include "esp_http_server.h"
#include "camera_pins.h"
#include "web_ui.h"

// Access Point Settings
const char* AP_SSID = "ESP32S3-CAM-AP";
const char* AP_PASS = ""; // Open AP (no password needed)

httpd_handle_t stream_httpd = NULL;
httpd_handle_t camera_httpd = NULL;

#define PART_BOUNDARY "123456789000000000000987654321"
static const char* _STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char* _STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char* _STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";

String detected_sensor_name = "Unknown Sensor";

// Handler for root page
static esp_err_t index_handler(httpd_req_t *req) {
    httpd_resp_set_type(req, "text/html");
    return httpd_resp_send(req, INDEX_HTML, HTTPD_RESP_USE_STRLEN);
}

// Handler for single snapshot capture
static esp_err_t capture_handler(httpd_req_t *req) {
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
        Serial.println("[ERROR] Camera capture failed");
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "image/jpeg");
    httpd_resp_set_hdr(req, "Content-Disposition", "inline; filename=capture.jpg");
    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");

    esp_err_t res = httpd_resp_send(req, (const char *)fb->buf, fb->len);
    esp_camera_fb_return(fb);
    return res;
}

// Handler for live MJPEG video stream
static esp_err_t stream_handler(httpd_req_t *req) {
    camera_fb_t *fb = NULL;
    esp_err_t res = ESP_OK;
    char part_buf[64];

    res = httpd_resp_set_type(req, _STREAM_CONTENT_TYPE);
    if (res != ESP_OK) return res;
    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");

    while (true) {
        fb = esp_camera_fb_get();
        if (!fb) {
            Serial.println("[ERROR] Failed to get camera frame buffer");
            res = ESP_FAIL;
            break;
        }

        size_t hlen = snprintf(part_buf, 64, _STREAM_PART, fb->len);
        res = httpd_resp_send_chunk(req, _STREAM_BOUNDARY, strlen(_STREAM_BOUNDARY));
        if (res == ESP_OK) {
            res = httpd_resp_send_chunk(req, part_buf, hlen);
        }
        if (res == ESP_OK) {
            res = httpd_resp_send_chunk(req, (const char *)fb->buf, fb->len);
        }

        esp_camera_fb_return(fb);
        fb = NULL;

        if (res != ESP_OK) {
            break;
        }
    }
    return res;
}

// Handler for camera controls (resolution, quality, brightness, etc.)
static esp_err_t control_handler(httpd_req_t *req) {
    char query[64];
    char var[32];
    char val_str[32];

    if (httpd_req_get_url_query_str(req, query, sizeof(query)) == ESP_OK) {
        if (httpd_query_key_value(query, "var", var, sizeof(var)) == ESP_OK &&
            httpd_query_key_value(query, "val", val_str, sizeof(val_str)) == ESP_OK) {
            
            int val = atoi(val_str);
            sensor_t *s = esp_camera_sensor_get();
            int res = 0;

            if (!strcmp(var, "framesize")) {
                if (s->pixformat == PIXFORMAT_JPEG) {
                    res = s->set_framesize(s, (framesize_t)val);
                }
            } else if (!strcmp(var, "quality")) {
                res = s->set_quality(s, val);
            } else if (!strcmp(var, "contrast")) {
                res = s->set_contrast(s, val);
            } else if (!strcmp(var, "brightness")) {
                res = s->set_brightness(s, val);
            } else if (!strcmp(var, "saturation")) {
                res = s->set_saturation(s, val);
            } else if (!strcmp(var, "special_effect")) {
                res = s->set_special_effect(s, val);
            } else if (!strcmp(var, "vflip")) {
                res = s->set_vflip(s, val);
            } else if (!strcmp(var, "hmirror")) {
                res = s->set_hmirror(s, val);
            } else {
                res = -1;
            }

            if (res < 0) {
                return httpd_resp_send_500(req);
            }
        }
    }

    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
    return httpd_resp_send(req, "{\"status\":\"ok\"}", 15);
}

// Handler for hardware status/diagnostics
static esp_err_t status_handler(httpd_req_t *req) {
    char json_response[256];
    float free_psram_mb = (float)ESP.getFreePsram() / (1024.0 * 1024.0);
    uint32_t free_heap_kb = ESP.getFreeHeap() / 1024;

    snprintf(json_response, sizeof(json_response),
             "{\"sensor\":\"%s\",\"psram_mb\":%.2f,\"heap_kb\":%u}",
             detected_sensor_name.c_str(), free_psram_mb, free_heap_kb);

    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
    return httpd_resp_send(req, json_response, strlen(json_response));
}

void startCameraServer() {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.server_port = 80;
    config.ctrl_port = 32768;

    httpd_uri_t index_uri = {
        .uri       = "/",
        .method    = HTTP_GET,
        .handler   = index_handler,
        .user_ctx  = NULL
    };

    httpd_uri_t capture_uri = {
        .uri       = "/capture",
        .method    = HTTP_GET,
        .handler   = capture_handler,
        .user_ctx  = NULL
    };

    httpd_uri_t control_uri = {
        .uri       = "/control",
        .method    = HTTP_GET,
        .handler   = control_handler,
        .user_ctx  = NULL
    };

    httpd_uri_t status_uri = {
        .uri       = "/status",
        .method    = HTTP_GET,
        .handler   = status_handler,
        .user_ctx  = NULL
    };

    httpd_uri_t stream_uri = {
        .uri       = "/stream",
        .method    = HTTP_GET,
        .handler   = stream_handler,
        .user_ctx  = NULL
    };

    if (httpd_start(&camera_httpd, &config) == ESP_OK) {
        httpd_register_uri_handler(camera_httpd, &index_uri);
        httpd_register_uri_handler(camera_httpd, &capture_uri);
        httpd_register_uri_handler(camera_httpd, &control_uri);
        httpd_register_uri_handler(camera_httpd, &status_uri);
        httpd_register_uri_handler(camera_httpd, &stream_uri);
        Serial.println("[INFO] Web Dashboard server successfully started on port 80");
    } else {
        Serial.println("[ERROR] Failed to start HTTP server");
    }
}

void setup() {
    Serial.begin(115200);
    delay(1500);

    Serial.println("\n==========================================");
    Serial.println("  ESP32-S3 Freenove CAM Studio - AP Mode  ");
    Serial.println("==========================================");

    // Initialize PSRAM check
    if (psramFound()) {
        Serial.printf("[INFO] PSRAM initialized successfully! Total: %.2f MB\n", 
                      (float)ESP.getPsramSize() / (1024.0 * 1024.0));
    } else {
        Serial.println("[WARNING] PSRAM NOT found! High resolutions may fail!");
    }

    // Camera Configuration
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sccb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;
    config.frame_size = FRAMESIZE_VGA;
    config.jpeg_quality = 12; // 10-63
    config.fb_count = 2;      // Smooth double buffering
    config.fb_location = CAMERA_FB_IN_PSRAM;
    config.grab_mode = CAMERA_GRAB_LATEST;

    // Initialize Camera
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("[FATAL] Camera init failed with error 0x%x\n", err);
        Serial.println("Check: 1. Camera ribbon cable seated tightly.");
        Serial.println("       2. Pins matching Freenove ESP32-S3 CAM.");
        return;
    }

    // Detect Sensor Model
    sensor_t *s = esp_camera_sensor_get();
    if (s != NULL) {
        switch (s->id.PID) {
            case OV2640_PID:
                detected_sensor_name = "OV2640 (2MP)";
                s->set_vflip(s, 1); // standard upright orientation
                break;
            case OV3660_PID:
                detected_sensor_name = "OV3660 (3MP)";
                s->set_vflip(s, 1);
                s->set_brightness(s, 1);
                s->set_saturation(s, -1);
                break;
            case OV5640_PID:
                detected_sensor_name = "OV5640 (5MP)";
                s->set_vflip(s, 0);
                break;
            default:
                detected_sensor_name = "OmniVision Sensor (PID: " + String(s->id.PID, HEX) + ")";
                break;
        }
        Serial.printf("[INFO] Detected Camera Sensor: %s\n", detected_sensor_name.c_str());
    }

    // Start Wi-Fi Access Point
    Serial.println("\n[INFO] Starting Wi-Fi Access Point...");
    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PASS);

    IPAddress IP = WiFi.softAPIP();
    Serial.println("==========================================");
    Serial.printf(" Wi-Fi Hotspot SSID : %s\n", AP_SSID);
    Serial.printf(" Hotspot IP Address : http://%s\n", IP.toString().c_str());
    Serial.println("==========================================");
    Serial.println("Instructions:");
    Serial.println("1. Connect your PC or Phone Wi-Fi to 'ESP32S3-CAM-AP'");
    Serial.println("2. Open your web browser (Chrome/Edge/Firefox)");
    Serial.printf("3. Navigate to: http://%s\n", IP.toString().c_str());
    Serial.println("==========================================");

    // Start Web Server
    startCameraServer();
}

void loop() {
    delay(10000);
}
