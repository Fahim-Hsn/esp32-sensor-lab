#include <Arduino.h>
#include "esp_camera.h"
#include "camera_pins.h"

// Magic sync marker
const uint8_t FRAME_HEADER[4] = {0xAA, 0x55, 0xAA, 0x55};
const uint8_t FRAME_FOOTER[2] = {0x55, 0xAA};

String detected_sensor_name = "Unknown";
volatile bool resolution_changed = false;

void handleSerialCommands() {
    while (Serial.available() > 0) {
        String cmd = Serial.readStringUntil('\n');
        cmd.trim();
        if (cmd.length() == 0) continue;

        char type = cmd.charAt(0);
        int val = cmd.substring(1).toInt();
        sensor_t *s = esp_camera_sensor_get();
        if (!s) return;

        switch (type) {
            case 'R': { // Resolution
                framesize_t fs = (framesize_t)val;
                s->set_framesize(s, fs);
                
                // Automatically adapt quality based on resolution to maintain smooth USB throughput
                if (fs >= FRAMESIZE_UXGA) {
                    s->set_quality(s, 20);
                } else if (fs >= FRAMESIZE_XGA) {
                    s->set_quality(s, 16);
                } else {
                    s->set_quality(s, 12);
                }
                
                // Discard transitional frames generated during sensor PLL clock reconfiguration
                for (int i = 0; i < 3; i++) {
                    camera_fb_t *fb_trans = esp_camera_fb_get();
                    if (fb_trans) {
                        esp_camera_fb_return(fb_trans);
                    }
                    delay(20);
                }
                break;
            }
            case 'Q': // Quality (10-63)
                s->set_quality(s, val);
                break;
            case 'F': // Flip vertical
                s->set_vflip(s, val);
                break;
            case 'M': // Mirror horizontal
                s->set_hmirror(s, val);
                break;
            case 'B': // Brightness (-2 to 2)
                s->set_brightness(s, val);
                break;
            case 'C': // Contrast (-2 to 2)
                s->set_contrast(s, val);
                break;
            default:
                break;
        }
    }
}

void setup() {
    // 921600 baud for UART bridge, or full 12 Mbps for native USB CDC
    Serial.begin(921600);
    delay(1000);

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
    config.frame_size = FRAMESIZE_VGA; // Crisp default resolution
    config.jpeg_quality = 12;          // High initial sharpness
    config.fb_count = 2;               // Double buffering in PSRAM
    config.fb_location = CAMERA_FB_IN_PSRAM;
    config.grab_mode = CAMERA_GRAB_LATEST;

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        while(1) {
            delay(1000);
        }
    }

    sensor_t *s = esp_camera_sensor_get();
    if (s != NULL) {
        if (s->id.PID == OV3660_PID) {
            s->set_vflip(s, 1);
            s->set_brightness(s, 1);
            s->set_saturation(s, -1);
        } else if (s->id.PID == OV2640_PID) {
            s->set_vflip(s, 1);
        }
    }
}

// Chunked writing helper to prevent hardware FIFO overflows
void writeBytesPaced(const uint8_t *data, size_t len) {
    const size_t CHUNK_SIZE = 4096;
    size_t sent = 0;
    while (sent < len) {
        size_t to_write = (len - sent > CHUNK_SIZE) ? CHUNK_SIZE : (len - sent);
        Serial.write(data + sent, to_write);
        sent += to_write;
        if (sent < len) {
            yield();
        }
    }
}

void loop() {
    int64_t t_frame_start = esp_timer_get_time();

    // Check for incoming commands
    handleSerialCommands();

    // Capture Frame
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
        vTaskDelay(pdMS_TO_TICKS(5));
        return;
    }

    // Verify JPEG SOI marker (0xFF, 0xD8) to guarantee frame integrity before sending
    if (fb->len > 4 && fb->buf[0] == 0xFF && fb->buf[1] == 0xD8) {
        // Write Sync Header
        Serial.write(FRAME_HEADER, 4);

        // Write 4-byte Payload Length (Big Endian)
        uint32_t len = fb->len;
        uint8_t len_bytes[4];
        len_bytes[0] = (len >> 24) & 0xFF;
        len_bytes[1] = (len >> 16) & 0xFF;
        len_bytes[2] = (len >> 8) & 0xFF;
        len_bytes[3] = len & 0xFF;
        Serial.write(len_bytes, 4);

        // Write JPEG Payload cleanly
        writeBytesPaced(fb->buf, fb->len);

        // Write End Marker
        Serial.write(FRAME_FOOTER, 2);
    }

    // Return frame buffer immediately
    esp_camera_fb_return(fb);

    // Frame Pacing: target smooth 30 FPS without overwhelming USB host buffers
    int64_t t_elapsed = (esp_timer_get_time() - t_frame_start) / 1000;
    if (t_elapsed < 33) {
        vTaskDelay(pdMS_TO_TICKS(33 - t_elapsed));
    } else {
        vTaskDelay(pdMS_TO_TICKS(2));
    }
}
