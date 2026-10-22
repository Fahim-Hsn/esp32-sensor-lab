#pragma once

// High-speed, Ultra-low Latency Glassmorphism Web Dashboard for ESP32-S3 CAM
const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>ESP32-S3 Real-Time Studio</title>
  <style>
    :root {
      --bg: #0b0f19;
      --card-bg: rgba(22, 27, 46, 0.88);
      --card-border: rgba(255, 255, 255, 0.08);
      --accent: #6366f1;
      --accent-glow: rgba(99, 102, 241, 0.4);
      --accent-hover: #4f46e5;
      --success: #10b981;
      --warning: #f59e0b;
      --danger: #ef4444;
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
      padding: 10px 18px;
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
      width: 34px;
      height: 34px;
      border-radius: 8px;
      background: linear-gradient(135deg, #6366f1, #a855f7);
      display: flex;
      align-items: center;
      justify-content: center;
      box-shadow: 0 4px 12px var(--accent-glow);
    }
    .badge-icon svg {
      width: 18px;
      height: 18px;
      fill: #fff;
    }
    .brand-title {
      font-size: 1rem;
      font-weight: 700;
      letter-spacing: -0.02em;
    }
    .brand-subtitle {
      font-size: 0.68rem;
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
      font-size: 0.72rem;
      font-weight: 600;
      border: 1px solid rgba(16, 185, 129, 0.3);
    }
    .pulse-dot {
      width: 7px;
      height: 7px;
      border-radius: 50%;
      background: currentColor;
    }
    .main-layout {
      flex: 1;
      display: grid;
      grid-template-columns: 1fr var(--panel-width);
      gap: 16px;
      padding: 16px;
      max-width: 1400px;
      margin: 0 auto;
      width: 100%;
    }
    @media (max-width: 860px) {
      .main-layout {
        grid-template-columns: 1fr;
        padding: 10px;
      }
    }
    .viewport-card {
      background: var(--card-bg);
      border: 1px solid var(--card-border);
      border-radius: 14px;
      padding: 14px;
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
    /* Hardware accelerated zero-lag canvas */
    #stream-canvas {
      width: 100%;
      height: 100%;
      object-fit: contain;
    }
    /* Legacy fallback image element */
    #stream-img {
      width: 100%;
      height: 100%;
      object-fit: contain;
      display: none;
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
      background: rgba(0, 0, 0, 0.75);
      backdrop-filter: blur(6px);
      padding: 3px 8px;
      border-radius: 6px;
      font-size: 0.7rem;
      font-weight: 600;
      letter-spacing: 0.03em;
      border: 1px solid rgba(255,255,255,0.1);
    }
    .hud-pill.highlight {
      color: var(--success);
      border-color: rgba(16, 185, 129, 0.3);
    }
    .viewport-actions {
      display: flex;
      gap: 8px;
      margin-top: 12px;
      flex-wrap: wrap;
    }
    .btn {
      display: inline-flex;
      align-items: center;
      justify-content: center;
      gap: 6px;
      padding: 8px 14px;
      border-radius: 8px;
      font-size: 0.78rem;
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
      gap: 12px;
    }
    .panel {
      background: var(--card-bg);
      border: 1px solid var(--card-border);
      border-radius: 12px;
      padding: 14px;
      backdrop-filter: blur(16px);
    }
    .panel-title {
      font-size: 0.8rem;
      font-weight: 700;
      text-transform: uppercase;
      letter-spacing: 0.05em;
      color: var(--text-muted);
      margin-bottom: 10px;
      display: flex;
      align-items: center;
      justify-content: space-between;
    }
    .control-row {
      margin-bottom: 10px;
      display: flex;
      flex-direction: column;
      gap: 4px;
    }
    .control-row:last-child {
      margin-bottom: 0;
    }
    .control-header {
      display: flex;
      justify-content: space-between;
      font-size: 0.72rem;
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
      padding: 7px 9px;
      border-radius: 6px;
      font-size: 0.78rem;
      outline: none;
      cursor: pointer;
    }
    select:focus {
      border-color: var(--accent);
    }
    input[type="range"] {
      -webkit-appearance: none;
      appearance: none;
      height: 4px;
      background: rgba(255, 255, 255, 0.12);
      border-radius: 4px;
      outline: none;
    }
    input[type="range"]::-webkit-slider-thumb {
      -webkit-appearance: none;
      width: 14px;
      height: 14px;
      border-radius: 50%;
      background: var(--accent);
      cursor: pointer;
      box-shadow: 0 0 8px var(--accent-glow);
    }
    .toggle-row {
      display: flex;
      align-items: center;
      justify-content: space-between;
      padding: 4px 0;
      font-size: 0.78rem;
    }
    .switch {
      position: relative;
      display: inline-block;
      width: 36px;
      height: 18px;
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
      height: 12px;
      width: 12px;
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
      gap: 6px;
    }
    .info-box {
      background: rgba(0,0,0,0.3);
      padding: 7px;
      border-radius: 6px;
      border: 1px solid rgba(255,255,255,0.04);
    }
    .info-label {
      font-size: 0.62rem;
      color: var(--text-muted);
      margin-bottom: 2px;
    }
    .info-value {
      font-size: 0.75rem;
      font-weight: 700;
      color: #fff;
    }
    .mode-switch-container {
      display: flex;
      background: rgba(0,0,0,0.3);
      padding: 3px;
      border-radius: 8px;
      gap: 4px;
      margin-bottom: 12px;
    }
    .mode-tab {
      flex: 1;
      text-align: center;
      padding: 6px 4px;
      font-size: 0.72rem;
      font-weight: 600;
      border-radius: 6px;
      cursor: pointer;
      color: var(--text-muted);
      transition: all 0.2s;
    }
    .mode-tab.active {
      background: var(--accent);
      color: #fff;
      box-shadow: 0 2px 8px var(--accent-glow);
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
        <div class="brand-title">ESP32-S3 Real-Time Studio</div>
        <div class="brand-subtitle">Zero-Buffer Ultra-Low Latency Engine</div>
      </div>
    </div>
    <div class="status-badge" id="status-badge">
      <span class="pulse-dot"></span>
      <span id="stream-status">LIVE (< 60ms LAG)</span>
    </div>
  </header>

  <div class="main-layout">
    <div class="viewport-card">
      <div class="stream-container" id="stream-box">
        <div class="overlay-hud">
          <div class="hud-pill highlight" id="hud-mode">ZERO-LAG CANVAS</div>
          <div class="hud-pill" id="hud-latency">-- ms PING</div>
          <div class="hud-pill" id="hud-fps">0 FPS</div>
          <div class="hud-pill" id="hud-res">VGA (640x480)</div>
        </div>
        
        <!-- Ultra-low Latency Hardware Accelerated Canvas -->
        <canvas id="stream-canvas"></canvas>
        
        <!-- Legacy MJPEG image fallback -->
        <img id="stream-img" alt="ESP32 Stream">
      </div>
      
      <div class="viewport-actions">
        <button class="btn btn-primary" onclick="captureSnapshot()">
          <svg width="14" height="14" fill="currentColor" viewBox="0 0 24 24"><path d="M9 3L7.17 5H4c-1.1 0-2 .9-2 2v12c0 1.1.9 2 2 2h16c1.1 0 2-.9 2-2V7c0-1.1-.9-2-2-2h-3.17L15 3H9zm3 15c-2.76 0-5-2.24-5-5s2.24-5 5-5 5 2.24 5 5-2.24 5-5 5zm0-8c-1.66 0-3 1.34-3 3s1.34 3 3 3 3-1.34 3-3-1.34-3-3-3z"/></svg>
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
        <div class="panel-title">Streaming Engine Mode</div>
        <div class="mode-switch-container">
          <div class="mode-tab active" id="tab-canvas" onclick="setEngineMode('canvas')">
            Zero-Lag Canvas
          </div>
          <div class="mode-tab" id="tab-mjpeg" onclick="setEngineMode('mjpeg')">
            MJPEG (Port 81)
          </div>
        </div>

        <div class="control-row">
          <div class="control-header">
            <span>Resolution Preset</span>
          </div>
          <select id="framesize" onchange="updateParam('framesize', this.value)">
            <option value="8" selected>VGA (640x480) - Recommended</option>
            <option value="9">SVGA (800x600) - Smooth</option>
            <option value="6">CIF (400x296) - Fast</option>
            <option value="5">QVGA (320x240) - Ultra-Fast (30+ FPS)</option>
            <option value="10">XGA (1024x768)</option>
            <option value="12">SXGA (1280x1024)</option>
            <option value="13">UXGA (1600x1200)</option>
          </select>
        </div>

        <div class="control-row">
          <div class="control-header">
            <span>Quality (Compression)</span>
            <span class="control-val" id="val-quality">16</span>
          </div>
          <input type="range" id="quality" min="10" max="63" value="16" oninput="updateParam('quality', this.value); document.getElementById('val-quality').innerText = this.value">
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
          <button style="background:none; border:none; color:var(--accent); cursor:pointer; font-size:0.68rem;" onclick="fetchDiagnostics()">Refresh</button>
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
    const canvas = document.getElementById('stream-canvas');
    const ctx = canvas.getContext('2d', { alpha: false, desynchronized: true });
    const imgEl = document.getElementById('stream-img');
    const statusText = document.getElementById('stream-status');
    const hudLatency = document.getElementById('hud-latency');
    const hudFps = document.getElementById('hud-fps');
    const hudMode = document.getElementById('hud-mode');

    let currentMode = 'canvas'; // 'canvas' (zero buffer/lag) or 'mjpeg' (port 81)
    let isStreaming = true;
    let frameCount = 0;
    let lastFpsTime = performance.now();
    let abortController = null;

    // Zero-lag real-time frame engine
    async function runCanvasLoop() {
      while (isStreaming && currentMode === 'canvas') {
        const tStart = performance.now();
        abortController = new AbortController();

        try {
          // Pull absolute freshest frame with zero network queueing
          const res = await fetch('/capture?t=' + Date.now(), { 
            cache: 'no-store',
            signal: abortController.signal
          });

          if (!res.ok) {
            await new Promise(r => setTimeout(r, 40));
            continue;
          }

          const blob = await res.blob();
          const tReceived = performance.now();
          const latencyMs = Math.round(tReceived - tStart);

          // Hardware accelerated decoding off the main thread
          const bitmap = await createImageBitmap(blob);

          if (canvas.width !== bitmap.width || canvas.height !== bitmap.height) {
            canvas.width = bitmap.width;
            canvas.height = bitmap.height;
          }

          ctx.drawImage(bitmap, 0, 0);
          bitmap.close();

          frameCount++;
          hudLatency.innerText = latencyMs + ' ms PING';

          // Frame rate counter
          const now = performance.now();
          if (now - lastFpsTime >= 1000) {
            const fps = Math.round((frameCount * 1000) / (now - lastFpsTime));
            hudFps.innerText = fps + ' FPS';
            frameCount = 0;
            lastFpsTime = now;
          }

          // Dynamic throttle: no delay needed if network is smooth, tiny yield for browser rendering
          await new Promise(r => requestAnimationFrame(r));
        } catch (e) {
          if (!isStreaming) break;
          await new Promise(r => setTimeout(r, 60));
        }
      }
    }

    function setEngineMode(mode) {
      currentMode = mode;
      document.getElementById('tab-canvas').classList.toggle('active', mode === 'canvas');
      document.getElementById('tab-mjpeg').classList.toggle('active', mode === 'mjpeg');

      if (mode === 'canvas') {
        hudMode.innerText = 'ZERO-LAG CANVAS';
        hudMode.classList.add('highlight');
        imgEl.style.display = 'none';
        imgEl.src = '';
        canvas.style.display = 'block';
        if (isStreaming) runCanvasLoop();
      } else {
        hudMode.innerText = 'MJPEG PORT 81';
        hudMode.classList.remove('highlight');
        hudLatency.innerText = 'STREAMING';
        if (abortController) abortController.abort();
        canvas.style.display = 'none';
        imgEl.style.display = 'block';
        if (isStreaming) {
          imgEl.src = 'http://' + window.location.hostname + ':81/stream?t=' + Date.now();
        }
      }
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
        .catch(e => console.warn(e));
    }

    function toggleStream() {
      const btn = document.getElementById('toggle-stream-btn');
      if (isStreaming) {
        isStreaming = false;
        if (abortController) abortController.abort();
        imgEl.src = '';
        btn.innerText = 'Resume Stream';
        statusText.innerText = 'STREAM PAUSED';
        statusText.parentElement.style.color = '#ef4444';
      } else {
        isStreaming = true;
        btn.innerText = 'Pause Stream';
        statusText.innerText = 'LIVE (< 60ms LAG)';
        statusText.parentElement.style.color = '#10b981';
        if (currentMode === 'canvas') {
          runCanvasLoop();
        } else {
          imgEl.src = 'http://' + window.location.hostname + ':81/stream?t=' + Date.now();
        }
      }
    }

    function captureSnapshot() {
      if (currentMode === 'canvas' && canvas.width > 0) {
        canvas.toBlob(blob => {
          const link = document.createElement('a');
          link.href = URL.createObjectURL(blob);
          link.download = `esp32s3_snap_${Date.now()}.jpg`;
          document.body.appendChild(link);
          link.click();
          document.body.removeChild(link);
          setTimeout(() => URL.revokeObjectURL(link.href), 2000);
        }, 'image/jpeg', 0.95);
      } else {
        const link = document.createElement('a');
        link.href = '/capture?t=' + Date.now();
        link.download = `esp32s3_snap_${Date.now()}.jpg`;
        document.body.appendChild(link);
        link.click();
        document.body.removeChild(link);
      }
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

    window.addEventListener('DOMContentLoaded', () => {
      setEngineMode('canvas');
      fetchDiagnostics();
    });
  </script>
</body>
</html>
)rawliteral";
