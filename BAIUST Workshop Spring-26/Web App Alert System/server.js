const express = require('express');
const cors = require('cors');
const app = express();

app.use(cors());
app.use(express.json());

let sensorInfo = { count: 0, time: "N/A" };
let isD2On = false;
let shouldReset = false; 


app.post('/api/reset-count', (req, res) => {
    sensorInfo.count = 0;
    shouldReset = true; 
    console.log("Request Success ESP32 waiting...");
    res.json({ success: true });
});


app.get('/api/check-led-d2', (req, res) => {
    
    let resetSignal = shouldReset ? "1" : "0";
    res.send(`${isD2On ? "ON" : "OFF"}|${resetSignal}`);
    
   
    if(shouldReset) {
        shouldReset = false;
        console.log("Signal reset ESP32 response sent");
    }
});

// D2 LED
app.post('/api/toggle-d2', (req, res) => {
    isD2On = req.body.status;
    console.log("D2 LED Status:", isD2On ? "ON" : "OFF");
    res.json({ success: true });
});

// sensor data receive
app.post('/api/sensor-data', (req, res) => {
    sensorInfo.count = req.body.count;
    sensorInfo.time = new Date().toLocaleTimeString();
    console.log("New Count:", sensorInfo.count);
    res.send("OK");
});

// for fontend
app.get('/api/get-sensor-data', (req, res) => {
    res.json(sensorInfo);
});

app.listen(3000, () => console.log('Server running on port 3000'));
