#pragma once

// Ultra-fast, responsive Glassmorphism Web Dashboard for ESP32-S3 CAM
const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>ESP32-S3 CAM Studio</title>
  <style>
    :root {
      --bg: #0b0f19;
      --card-bg: rgba(22, 27, 46, 0.85);
      --card-border: rgba(255, 255, 255, 0.08);
      --accent: #6366f1;
      --accent-glow: rgba(99, 102, 241, 0.4);
      --accent-hover: #4f46e5;
      --success: #10b981;
      --text: #f3f4f6;
      --text-muted: #9ca3af;
      --panel-width: 320px;
    }
    * {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
      font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, sans-serif;
    }
    body {
      background: radial-gradient(circle at top right, #1e1b4b, #0b0f19 70%);
      color: var(--text);
      min-height: 100vh;
      display: flex;
      flex-direction: column;
    }
    header {
      padding: 12px 20px;
      display: flex;
      align-items: center;
      justify-content: space-between;
      border-bottom: 1px solid var(--card-border);
      background: rgba(11, 15, 25, 0.95);
      backdrop-filter: blur(12px);
      position: sticky;
      top: 0;
      z-index: 100;
    }
    .brand {
      display: flex;
      align-items: center;
      gap: 10px;
    }
    .badge-icon {
      width: 36px;
      height: 36px;
      border-radius: 9px;
      background: linear-gradient(135deg, #6366f1, #a855f7);
      display: flex;
      align-items: center;
      justify-content: center;
      box-shadow: 0 4px 15px var(--accent-glow);
    }
    .badge-icon svg {
      width: 18px;
      height: 18px;
      fill: #fff;
    }
    .brand-title {
      font-size: 1.05rem;
      font-weight: 700;
      letter-spacing: -0.02em;
    }
    .brand-subtitle {
      font-size: 0.7rem;
      color: var(--text-muted);
    }
    .status-badge {
      display: inline-flex;
      align-items: center;
      gap: 6px;
      background: rgba(16, 185, 129, 0.15);
      color: var(--success);
      padding: 4px 10px;
      border-radius: 16px;
      font-size: 0.75rem;
      font-weight: 600;
      border: 1px solid rgba(16, 185, 129, 0.3);
    }
    .pulse-dot {
      width: 7px;
      height: 7px;
      border-radius: 50%;
      background: var(--success);
      box-shadow: 0 0 8px var(--success);
      animation: pulse 1.8s infinite;
    }
    @keyframes pulse {
      0%, 100% { opacity: 1; transform: scale(1); }
      50% { opacity: 0.4; transform: scale(0.85); }
    }
    .main-layout {
      flex: 1;
      display: grid;
      grid-template-columns: 1fr var(--panel-width);
      gap: 20px;
      padding: 18px;
      max-width: 1400px;
      margin: 0 auto;
      width: 100%;
    }
    @media (max-width: 860px) {
      .main-layout {
        grid-template-columns: 1fr;
        padding: 12px;
      }
    }
    .viewport-card {
      background: var(--card-bg);
      border: 1px solid var(--card-border);
      border-radius: 14px;
      padding: 16px;
      backdrop-filter: blur(16px);
      display: flex;
      flex-direction: column;
    }
    .stream-container {
      position: relative;
      width: 100%;
      aspect-ratio: 4 / 3;
      max-height: 65vh;
      background: #000;
      border-radius: 10px;
      overflow: hidden;
      display: flex;
      align-items: center;
      justify-content: center;
      border: 1px solid rgba(255, 255, 255, 0.05);
    }
    .stream-container img {
      width: 100%;
      height: 100%;
      object-fit: contain;
    }
    .overlay-hud {
      position: absolute;
      top: 10px;
      left: 10px;
      display: flex;
      gap: 6px;
      z-index: 10;
    }
    .hud-pill {
      background: rgba(0, 0, 0, 0.7);
      backdrop-filter: blur(6px);
      padding: 4px 8px;
      border-radius: 6px;
      font-size: 0.7rem;
      font-weight: 600;
      letter-spacing: 0.03em;
      border: 1px solid rgba(255,255,255,0.1);
    }
    .viewport-actions {
      display: flex;
      gap: 10px;
      margin-top: 14px;
      flex-wrap: wrap;
    }
    .btn {
      display: inline-flex;
      align-items: center;
      justify-content: center;
      gap: 6px;
      padding: 9px 15px;
      border-radius: 8px;
      font-size: 0.8rem;
      font-weight: 600;
      cursor: pointer;
      border: none;
      transition: all 0.2s ease;
      color: #fff;
    }
    .btn-primary {
      background: linear-gradient(135deg, var(--accent), #4338ca);
      box-shadow: 0 4px 12px var(--accent-glow);
    }
    .btn-primary:hover {
      background: linear-gradient(135deg, var(--accent-hover), #3730a3);
    }
    .btn-secondary {
      background: rgba(255, 255, 255, 0.08);
      border: 1px solid rgba(255, 255, 255, 0.12);
    }
    .btn-secondary:hover {
      background: rgba(255, 255, 255, 0.14);
    }
    .sidebar {
      display: flex;
      flex-direction: column;
      gap: 14px;
    }
    .panel {
      background: var(--card-bg);
      border: 1px solid var(--card-border);
      border-radius: 12px;
      padding: 16px;
      backdrop-filter: blur(16px);
    }
    .panel-title {
      font-size: 0.85rem;
      font-weight: 700;
      text-transform: uppercase;
      letter-spacing: 0.05em;
      color: var(--text-muted);
      margin-bottom: 12px;
      display: flex;
      align-items: center;
      justify-content: space-between;
    }
    .control-row {
      margin-bottom: 12px;
      display: flex;
      flex-direction: column;
      gap: 5px;
    }
    .control-row:last-child {
      margin-bottom: 0;
    }
    .control-header {
      display: flex;
      justify-content: space-between;
      font-size: 0.75rem;
      font-weight: 500;
    }
    .control-val {
      color: var(--accent);
      font-weight: 700;
    }
    select, input[type="range"] {
      width: 100%;
    }
    select {
      background: rgba(11, 15, 25, 0.85);
      border: 1px solid var(--card-border);
      color: var(--text);
      padding: 8px 10px;
      border-radius: 6px;
      font-size: 0.8rem;
      outline: none;
      cursor: pointer;
    }
    select:focus {
      border-color: var(--accent);
    }
    input[type="range"] {
      -webkit-appearance: none;
      appearance: none;
      height: 5px;
      background: rgba(255, 255, 255, 0.12);
      border-radius: 4px;
      outline: none;
    }
    input[type="range"]::-webkit-slider-thumb {
      -webkit-appearance: none;
      width: 15px;
      height: 15px;
      border-radius: 50%;
      background: var(--accent);
      cursor: pointer;
      box-shadow: 0 0 8px var(--accent-glow);
    }
    .toggle-row {
      display: flex;
      align-items: center;
      justify-content: space-between;
      padding: 5px 0;
      font-size: 0.8rem;
    }
    .switch {
      position: relative;
      display: inline-block;
      width: 38px;
      height: 20px;
    }
    .switch input {
      opacity: 0;
      width: 0;
      height: 0;
    }
    .slider {
      position: absolute;
      cursor: pointer;
      top: 0; left: 0; right: 0; bottom: 0;
      background-color: rgba(255, 255, 255, 0.15);
      transition: .25s;
      border-radius: 20px;
    }
    .slider:before {
      position: absolute;
      content: "";
      height: 14px;
      width: 14px;
      left: 3px;
      bottom: 3px;
      background-color: white;
      transition: .25s;
      border-radius: 50%;
    }
    input:checked + .slider {
      background-color: var(--accent);
    }
    input:checked + .slider:before {
      transform: translateX(18px);
    }
    .info-grid {
      display: grid;
      grid-template-columns: 1fr 1fr;
      gap: 8px;
    }
    .info-box {
      background: rgba(0,0,0,0.3);
      padding: 8px;
      border-radius: 6px;
      border: 1px solid rgba(255,255,255,0.04);
    }
    .info-label {
      font-size: 0.65rem;
      color: var(--text-muted);
      margin-bottom: 2px;
    }
    .info-value {
      font-size: 0.8rem;
      font-weight: 700;
      color: #fff;
    }
  </style>
</head>
<body>
  <header>
    <div class="brand">
      <div class="badge-icon">
        <svg viewBox="0 0 24 24"><path d="M12 2C6.48 2 2 6.48 2 12s4.48 10 10 10 10-4.48 10-10S17.52 2 12 2zm0 18c-4.41 0-8-3.59-8-8s3.59-8 8-8 8 3.59 8 8-3.59 8-8 8zm-5-8.5l3.5 4.5 2.5-3.01L16.5 17H7.5l-2-2.5z"/></svg>
      </div>
      <div>
        <div class="brand-title">ESP32-S3 CAM Studio</div>
        <div class="brand-subtitle">High-Speed Dedicated Stream Engine</div>
      </div>
    </div>
    <div class="status-badge">
      <span class="pulse-dot"></span>
      <span id="stream-status">STREAM ACTIVE</span>
    </div>
  </header>

  <div class="main-layout">
    <div class="viewport-card">
      <div class="stream-container" id="stream-box">
        <div class="overlay-hud">
          <div class="hud-pill" id="hud-port">PORT: 81 (ISOLATED)</div>
          <div class="hud-pill" id="hud-res">VGA (640x480)</div>
        </div>
        <img id="stream-view" alt="ESP32 Stream">
      </div>
      <div class="viewport-actions">
        <button class="btn btn-primary" onclick="captureSnapshot()">
          <svg width="15" height="15" fill="currentColor" viewBox="0 0 24 24"><path d="M9 3L7.17 5H4c-1.1 0-2 .9-2 2v12c0 1.1.9 2 2 2h16c1.1 0 2-.9 2-2V7c0-1.1-.9-2-2-2h-3.17L15 3H9zm3 15c-2.76 0-5-2.24-5-5s2.24-5 5-5 5 2.24 5 5-2.24 5-5 5zm0-8c-1.66 0-3 1.34-3 3s1.34 3 3 3 3-1.34 3-3-1.34-3-3-3z"/></svg>
          Capture Snapshot
        </button>
        <button class="btn btn-secondary" id="toggle-stream-btn" onclick="toggleStream()">
          Pause Stream
        </button>
        <button class="btn btn-secondary" onclick="toggleFullscreen()">
          Fullscreen
        </button>
      </div>
    </div>

    <div class="sidebar">
      <div class="panel">
        <div class="panel-title">Camera Controls</div>
        
        <div class="control-row">
          <div class="control-header">
            <span>Resolution</span>
          </div>
          <select id="framesize" onchange="updateParam('framesize', this.value)">
            <option value="13">UXGA (1600x1200)</option>
            <option value="12">SXGA (1280x1024)</option>
            <option value="10">XGA (1024x768)</option>
            <option value="9">SVGA (800x600)</option>
            <option value="8" selected>VGA (640x480)</option>
            <option value="6">CIF (400x296)</option>
            <option value="5">QVGA (320x240)</option>
            <option value="3">HQVGA (240x176)</option>
            <option value="1">QQVGA (160x120)</option>
          </select>
        </div>

        <div class="control-row">
          <div class="control-header">
            <span>Quality (Compression)</span>
            <span class="control-val" id="val-quality">14</span>
          </div>
          <input type="range" id="quality" min="10" max="63" value="14" oninput="updateParam('quality', this.value); document.getElementById('val-quality').innerText = this.value">
        </div>

        <div class="control-row">
          <div class="control-header">
            <span>Brightness</span>
            <span class="control-val" id="val-brightness">0</span>
          </div>
          <input type="range" id="brightness" min="-2" max="2" value="0" oninput="updateParam('brightness', this.value); document.getElementById('val-brightness').innerText = this.value">
        </div>

        <div class="control-row">
          <div class="control-header">
            <span>Contrast</span>
            <span class="control-val" id="val-contrast">0</span>
          </div>
          <input type="range" id="contrast" min="-2" max="2" value="0" oninput="updateParam('contrast', this.value); document.getElementById('val-contrast').innerText = this.value">
        </div>

        <div class="toggle-row">
          <span>Vertical Flip (V-Flip)</span>
          <label class="switch">
            <input type="checkbox" id="vflip" onchange="updateParam('vflip', this.checked ? 1 : 0)">
            <span class="slider"></span>
          </label>
        </div>

        <div class="toggle-row">
          <span>Horizontal Mirror (H-Mirror)</span>
          <label class="switch">
            <input type="checkbox" id="hmirror" onchange="updateParam('hmirror', this.checked ? 1 : 0)">
            <span class="slider"></span>
          </label>
        </div>
      </div>

      <div class="panel">
        <div class="panel-title">
          <span>Diagnostics</span>
          <button style="background:none; border:none; color:var(--accent); cursor:pointer; font-size:0.7rem;" onclick="fetchDiagnostics()">Refresh</button>
        </div>
        <div class="info-grid">
          <div class="info-box">
            <div class="info-label">SENSOR</div>
            <div class="info-value" id="diag-sensor">Loading...</div>
          </div>
          <div class="info-box">
            <div class="info-label">FREE PSRAM</div>
            <div class="info-value" id="diag-psram">-- MB</div>
          </div>
          <div class="info-box">
            <div class="info-label">FREE HEAP</div>
            <div class="info-value" id="diag-heap">-- KB</div>
          </div>
          <div class="info-box">
            <div class="info-label">HOTSPOT IP</div>
            <div class="info-value">192.168.4.1</div>
          </div>
        </div>
      </div>
    </div>
  </div>

  <script>
    const streamImg = document.getElementById('stream-view');
    let isStreaming = true;

    // Stream runs on isolated Port 81 so it never blocks web controls or captive portal
    const streamHost = 'http://' + window.location.hostname + ':81/stream';

    function startStream() {
      streamImg.src = streamHost + '?t=' + Date.now();
      isStreaming = true;
      document.getElementById('toggle-stream-btn').innerText = 'Pause Stream';
      document.getElementById('stream-status').innerText = 'STREAM ACTIVE';
      document.getElementById('stream-status').parentElement.style.color = '#10b981';
    }

    function updateParam(param, val) {
      fetch('/control?var=' + param + '&val=' + val)
        .then(r => r.json())
        .then(d => {
          if (param === 'framesize') {
            const sel = document.getElementById('framesize');
            document.getElementById('hud-res').innerText = sel.options[sel.selectedIndex].text.split(' ')[0];
          }
        })
        .catch(e => console.warn("Param update warning:", e));
    }

    function toggleStream() {
      const btn = document.getElementById('toggle-stream-btn');
      const status = document.getElementById('stream-status');
      if (isStreaming) {
        streamImg.src = '';
        isStreaming = false;
        btn.innerText = 'Resume Stream';
        status.innerText = 'STREAM PAUSED';
        status.parentElement.style.color = '#ef4444';
      } else {
        startStream();
      }
    }

    function captureSnapshot() {
      const link = document.createElement('a');
      link.href = '/capture?t=' + Date.now();
      link.download = `esp32s3_snap_${Date.now()}.jpg`;
      document.body.appendChild(link);
      link.click();
      document.body.removeChild(link);
    }

    function toggleFullscreen() {
      const box = document.getElementById('stream-box');
      if (!document.fullscreenElement) {
        box.requestFullscreen().catch(err => alert(err.message));
      } else {
        document.exitFullscreen();
      }
    }

    function fetchDiagnostics() {
      fetch('/status')
        .then(res => res.json())
        .then(data => {
          if (data.sensor) document.getElementById('diag-sensor').innerText = data.sensor;
          if (data.psram_mb) document.getElementById('diag-psram').innerText = data.psram_mb + ' MB';
          if (data.heap_kb) document.getElementById('diag-heap').innerText = data.heap_kb + ' KB';
        })
        .catch(() => {});
    }

    // Start stream immediately on load
    window.addEventListener('DOMContentLoaded', () => {
      startStream();
      fetchDiagnostics();
    });
  </script>
</body>
</html>
)rawliteral";
