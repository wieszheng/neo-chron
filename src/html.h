const char *root_html = R"(
<!DOCTYPE html><html lang="zh-CN"><head><meta charset="UTF-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>Neo Chron</title><style>:root{--primary-color:#4a6cf7;--primary-dark:#3a5ce5;--secondary-color:#f5f5f5;--text-color:#333;--light-text:#666;--border-color:#ddd;--success-color:#4caf50;--error-color:#f44336;--warning-color:#ff9800;--card-shadow:0 4px 12px rgba(0,0,0,0.1);--transition:all 0.3s ease}*{margin:0;padding:0;box-sizing:border-box;font-family:"Segoe UI",Tahoma,Geneva,Verdana,sans-serif}body{background-color:#f0f2f5;color:var(--text-color);line-height:1.6;padding:20px 0}.container{max-width:500px;margin:0 auto;padding:20px}.setup-card{background-color:#fff;border-radius:10px;padding:25px;box-shadow:var(--card-shadow);position:relative}.title-container{display:flex;align-items:center;justify-content:center;margin-bottom:25px}.version-badge{position:absolute;top:-10px;right:-10px;background-color:var(--primary-color);color:#fff;font-size:.7rem;font-weight:500;padding:4px 8px;border-radius:12px;box-shadow:0 2px 4px rgba(0,0,0,.2);z-index:1}h1{text-align:center;font-size:1.8rem}h2{font-size:1.3rem;color:var(--text-color)}.tabs{display:flex;border-bottom:1px solid var(--border-color);margin-bottom:20px}.tab-btn{flex:1;padding:12px;background:0 0;border:none;border-bottom:2px solid transparent;cursor:pointer;font-size:1rem;font-weight:500;color:var(--light-text);transition:var(--transition)}.tab-btn.active{color:var(--primary-color);border-bottom-color:var(--primary-color)}.tab-btn:hover:not(.active){color:var(--text-color);background-color:rgba(0,0,0,.02)}.tab-content{display:none}.tab-content.active{display:block}.section{margin-bottom:30px;padding-bottom:20px;border-bottom:1px solid var(--border-color)}.section:last-child{margin-bottom:0;padding-bottom:0;border-bottom:none}.section-header{display:flex;justify-content:space-between;align-items:center;margin-bottom:15px}.primary-btn,.secondary-btn{padding:10px 20px;border:none;border-radius:5px;cursor:pointer;font-size:1rem;font-weight:500;transition:var(--transition);width:100%}.primary-btn{background-color:var(--primary-color);color:#fff}.primary-btn:hover:not(:disabled){background-color:var(--primary-dark)}.primary-btn:disabled{background-color:#ccc;cursor:not-allowed}.secondary-btn{background-color:var(--secondary-color);color:var(--text-color);margin-top:10px}.secondary-btn:hover{background-color:#e5e5e5}.icon-btn{background:0 0;border:none;cursor:pointer;display:flex;align-items:center;justify-content:center;color:var(--primary-color);transition:var(--transition);padding:8px;border-radius:50%}.icon-btn:hover{background-color:rgba(74,108,247,.1)}.loader{border:3px solid #f3f3f3;border-top:3px solid var(--primary-color);border-radius:50%;width:30px;height:30px;animation:spin 1s linear infinite;margin:20px auto;display:none}@keyframes spin{0%{transform:rotate(0)}100%{transform:rotate(360deg)}}.network-list{max-height:200px;overflow-y:auto;margin:15px 0;border:1px solid var(--border-color);border-radius:5px;display:none}.network-item{padding:12px 15px;border-bottom:1px solid var(--border-color);cursor:pointer;transition:var(--transition);display:flex;justify-content:space-between;align-items:center;font-size:.9rem}.network-item:last-child{border-bottom:none}.network-item:hover{background-color:#f9f9f9}.network-item.selected{background-color:#e8f0fe;position:relative}.network-name{font-weight:500;flex:1;margin:0 10px}.signal-strength{display:inline-block;width:24px;height:24px;position:relative}.signal-high::before,.signal-low::before,.signal-medium::before{content:"";position:absolute;top:50%;left:50%;transform:translate(-50%,-50%);width:18px;height:18px;background-repeat:no-repeat;background-position:center;background-size:contain}.signal-high::before{background-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' width='24' height='24' stroke='%234caf50' stroke-width='2' fill='none' stroke-linecap='round' stroke-linejoin='round'%3E%3Cpath d='M12 2C6.5 2 2 6.5 2 12s4.5 10 10 10 10-4.5 10-10S17.5 2 12 2'/%3E%3Cpath d='M12 5c-3.9 0-7 3.1-7 7s3.1 7 7 7 7-3.1 7-7-3.1-7-7-7'/%3E%3Cpath d='M12 8c-2.2 0-4 1.8-4 4s1.8 4 4 4 4-1.8 4-4-1.8-4-4-4'/%3E%3Ccircle cx='12' cy='12' r='1'/%3E%3C/svg%3E")}.signal-medium::before{background-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' width='24' height='24' stroke='%23ff9800' stroke-width='2' fill='none' stroke-linecap='round' stroke-linejoin='round'%3E%3Cpath d='M12 2C6.5 2 2 6.5 2 12s4.5 10 10 10 10-4.5 10-10S17.5 2 12 2'/%3E%3Cpath d='M12 5c-3.9 0-7 3.1-7 7s3.1 7 7 7 7-3.1 7-7-3.1-7-7-7'/%3E%3Cpath d='M12 8c-2.2 0-4 1.8-4 4s1.8 4 4 4 4-1.8 4-4-1.8-4-4-4' stroke-dasharray='15,30' stroke-dashoffset='15'/%3E%3Ccircle cx='12' cy='12' r='1'/%3E%3C/svg%3E")}.signal-low::before{background-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' width='24' height='24' stroke='%23f44336' stroke-width='2' fill='none' stroke-linecap='round' stroke-linejoin='round'%3E%3Cpath d='M12 2C6.5 2 2 6.5 2 12s4.5 10 10 10 10-4.5 10-10S17.5 2 12 2'/%3E%3Cpath d='M12 5c-3.9 0-7 3.1-7 7s3.1 7 7 7 7-3.1 7-7-3.1-7-7-7' stroke-dasharray='15,30' stroke-dashoffset='15'/%3E%3Cpath d='M12 8c-2.2 0-4 1.8-4 4s1.8 4 4 4 4-1.8 4-4-1.8-4-4-4' stroke-dasharray='15,30' stroke-dashoffset='15'/%3E%3Ccircle cx='12' cy='12' r='1'/%3E%3C/svg%3E")}.lock-icon{display:inline-block;width:16px;height:16px;margin-left:4px;background-repeat:no-repeat;background-position:center;background-size:contain;background-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' width='18' height='18' stroke='%23666' stroke-width='2' fill='none' stroke-linecap='round' stroke-linejoin='round'%3E%3Crect x='3' y='11' width='18' height='11' rx='2' ry='2'/%3E%3Cpath d='M7 11V7a5 5 0 0 1 10 0v4'/%3E%3C/svg%3E")}.signal-dbm{font-size:.75rem;color:var(--light-text);margin-left:5px;min-width:45px;text-align:right}.ssid-input-container{position:relative;display:flex}.form-group{margin-bottom:20px}label{display:block;margin-bottom:8px;font-weight:500}.password-input{position:relative;display:flex}input,select{width:100%;padding:8px 12px;border:1px solid var(--border-color);border-radius:5px;font-size:.95rem;transition:var(--transition);height:38px}.password-input input{padding-right:70px}.ssid-input-container input{padding-right:12px}input:focus,select:focus{outline:0;border-color:var(--primary-color);box-shadow:0 0 0 2px rgba(74,108,247,.2)}.password-input .icon-btn{position:absolute;right:10px;top:50%;transform:translateY(-50%)}.status-message{padding:12px;border-radius:5px;margin-bottom:15px;background-color:#f5f5f5;text-align:center}.connection-progress{display:none;text-align:center;padding:15px 0}.success-message{display:none;text-align:center;padding:15px 0}.success-icon{font-size:3rem;color:var(--success-color);text-align:center;margin:10px 0}.ip-address{margin-top:15px;padding:10px;background-color:#f5f5f5;border-radius:5px;font-family:monospace;display:inline-block}.toggle-container{display:flex;justify-content:space-between;align-items:center}.switch{position:relative;display:inline-block;width:50px;height:24px}.switch input{opacity:0;width:0;height:0}.slider{position:absolute;cursor:pointer;top:0;left:0;right:0;bottom:0;background-color:#ccc;transition:.4s}.slider:before{position:absolute;content:"";height:16px;width:16px;left:4px;bottom:4px;background-color:#fff;transition:.4s}input:checked+.slider{background-color:var(--primary-color)}input:focus+.slider{box-shadow:0 0 1px var(--primary-color)}input:checked+.slider:before{transform:translateX(26px)}.slider.round{border-radius:34px}.slider.round:before{border-radius:50%}.form-hint{font-size:.85rem;color:var(--light-text);margin-top:5px}.hidden{display:none}.range-container{display:flex;align-items:center;margin-top:8px}.range-input{flex:1;height:6px;border-radius:3px;background:#e0e0e0;outline:0;-webkit-appearance:none;max-width:80%;margin-right:15px}.range-input::-webkit-slider-thumb{-webkit-appearance:none;appearance:none;width:18px;height:18px;border-radius:50%;background:var(--primary-color);cursor:pointer;box-shadow:0 1px 3px rgba(0,0,0,.2);transition:all .2s ease}.range-input::-webkit-slider-thumb:hover{transform:scale(1.1);box-shadow:0 2px 5px rgba(0,0,0,.3)}.range-input::-moz-range-thumb{width:18px;height:18px;border-radius:50%;background:var(--primary-color);cursor:pointer;border:none;box-shadow:0 1px 3px rgba(0,0,0,.2);transition:all .2s ease}.range-input::-moz-range-thumb:hover{transform:scale(1.1);box-shadow:0 2px 5px rgba(0,0,0,.3)}.range-input::-moz-range-progress{background-color:var(--primary-color);height:6px;border-radius:3px}.range-value{width:40px;text-align:center;font-weight:500;color:var(--text-color);padding:4px 8px;border-radius:4px;font-size:.9rem}.date-input,.time-input{padding:8px 10px;height:38px}.time-range{display:flex;align-items:center}.time-separator{margin:0 10px;color:var(--light-text)}.checkbox-group{margin-top:10px}.checkbox-container{display:block;position:relative;padding-left:35px;margin-bottom:12px;cursor:pointer;font-size:1rem;user-select:none}.checkbox-container input{position:absolute;opacity:0;cursor:pointer;height:0;width:0}.checkmark{position:absolute;top:0;left:0;height:20px;width:20px;background-color:#eee;border-radius:4px}.checkbox-container:hover input~.checkmark{background-color:#ccc}.checkbox-container input:checked~.checkmark{background-color:var(--primary-color)}.checkmark:after{content:"";position:absolute;display:none}.checkbox-container input:checked~.checkmark:after{display:block}.checkbox-container .checkmark:after{left:7px;top:3px;width:5px;height:10px;border:solid #fff;border-width:0 2px 2px 0;transform:rotate(45deg)}.number-input{width:100%;padding:8px 12px;border:1px solid var(--border-color);border-radius:5px;font-size:.95rem;transition:var(--transition);height:38px}.number-input:focus{outline:0;border-color:var(--primary-color);box-shadow:0 0 0 2px rgba(74,108,247,.2)}.colors-row{display:flex;flex-wrap:wrap;gap:10px;margin-top:10px}.color-item{flex:1;min-width:120px}.color-label{display:block;font-size:.95rem;margin-bottom:5px;color:var(--light-text)}.color-picker-container{display:flex;align-items:center}.color-picker{width:50px;height:35px;border:1px solid var(--border-color);border-radius:5px;cursor:pointer;padding:0;background:0 0}.color-value{margin-left:8px;font-family:monospace;font-size:.9rem;color:var(--light-text)}@media (max-width:480px){.container{padding:10px}.setup-card{padding:15px}h1{font-size:1.5rem}h2{font-size:1.1rem}.time-range{flex-direction:column;align-items:flex-start}.time-separator{margin:5px 0}.time-input{width:100%}.colors-row{flex-direction:column;gap:15px}.color-item{width:100%}}</style></head><body><div class="container"><div class="setup-card"><div class="title-container"><h1>Neo Chron</h1></div><div class="version-badge">1.1.0</div><div class="tabs"><button class="tab-btn active" data-tab="wifi-tab">WiFi设置</button> <button class="tab-btn" data-tab="clock-tab">时间设置</button> <button class="tab-btn" data-tab="advanced-tab">高级设置</button></div><div class="tab-content active" id="wifi-tab"><div class="section" id="scan-section"><div class="section-header"><h2>可用网络</h2><button id="scan-btn" class="icon-btn" title="扫描网络"><svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M21 12a9 9 0 0 1-9 9m9-9a9 9 0 0 0-9-9m9 9H3m9 9a9 9 0 0 1-9-9m9 9c1.66 0 3-4.03 3-9s-1.34-9-3-9m0 18c-1.66 0-3-4.03-3-9s1.34-9 3-9"></path></svg></button></div><div class="loader" id="scan-loader"></div><div class="network-list" id="network-list"></div></div><div class="section" id="password-section"><div class="form-group"><label for="ssid-input">Network Name (SSID)</label><div class="ssid-input-container"><input type="text" id="ssid-input" placeholder="从上方选择或手动输入"></div></div><div class="form-group"><label for="password">WiFi Password</label><div class="password-input"><input type="password" id="password" placeholder="输入密码"> <button id="toggle-password" class="icon-btn"><svg xmlns="http://www.w3.org/2000/svg" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M1 12s4-8 11-8 11 8 11 8-4 8-11 8-11-8-11-8z"></path><circle cx="12" cy="12" r="3"></circle></svg></button></div></div><button id="connect-btn" class="primary-btn">连接</button></div><div class="section" id="status-section"><h2>连接状态</h2><div id="connection-status" class="status-message">未连接</div><div class="connection-progress" id="connection-progress"><div class="loader"></div><p id="connection-message">等待连接...</p></div><div class="success-message" id="success-message"><div class="success-icon">✓</div><p>已连接到: <span id="connected-network">-</span></p><div class="ip-address"><span>IP地址: </span><span id="ip-address">-</span></div></div></div></div><div class="tab-content" id="clock-tab"><div class="section"><h2>时间设置</h2><div class="form-group"><label for="timezone">时区</label> <select id="timezone" class="select-input"><option value="UTC+07:00">(UTC+07:00) 曼谷，河内，雅加达</option><option value="UTC+08:00" selected="selected">(UTC+08:00) 北京，香港，新加坡</option></select></div><div class="form-group"><div class="toggle-container"><label for="time-format">使用24小时制</label> <label class="switch"><input type="checkbox" id="time-format" checked="checked"> <span class="slider round"></span></label></div></div><div class="form-group"><label>显示选项</label><div class="checkbox-group"><label class="checkbox-container"><input type="checkbox" id="show-seconds" checked="checked"> <span class="checkmark"></span> 显示秒数</label> <label class="checkbox-container"><input type="checkbox" id="show-date" checked="checked"> <span class="checkmark"></span> 显示日期</label></div></div><div class="form-group"><label>颜色设置</label><div class="colors-row"><div class="color-item"><span class="color-label">文本</span><div class="color-picker-container"><input type="color" id="text-color" value="#ffffff" class="color-picker"> <span class="color-value" id="text-color-value">#ffffff</span></div></div><div class="color-item"><span class="color-label">当前日期</span><div class="color-picker-container"><input type="color" id="current-day-color" value="#ff5500" class="color-picker"> <span class="color-value" id="current-day-color-value">#ff5500</span></div></div><div class="color-item"><span class="color-label">其他日期</span><div class="color-picker-container"><input type="color" id="other-days-color" value="#888888" class="color-picker"> <span class="color-value" id="other-days-color-value">#888888</span></div></div></div></div><button id="save-clock-settings" class="primary-btn">保存设置</button></div></div><div class="tab-content" id="advanced-tab"><div class="section"><h2>显示设置</h2><div class="form-group"><label for="brightness">亮度</label><div class="range-container"><input type="range" id="brightness" min="1" max="100" value="70" class="range-input"><div class="range-value" id="brightness-value">70</div></div></div><div class="form-group"><div class="toggle-container"><label for="night-mode">夜间模式</label> <label class="switch"><input type="checkbox" id="night-mode"> <span class="slider round"></span></label></div><p class="form-hint">夜间时段自动调暗显示屏</p></div><div id="night-mode-settings" class="hidden"><div class="form-group"><label>夜间时段</label><div class="time-range"><input type="time" id="night-start" value="22:00" class="time-input"> <span class="time-separator">至</span> <input type="time" id="night-end" value="06:00" class="time-input"></div></div><div class="form-group"><label for="night-brightness">夜间亮度</label><div class="range-container"><input type="range" id="night-brightness" min="1" max="100" value="20" class="range-input"><div class="range-value" id="night-brightness-value">20</div></div></div></div></div><div><div class="form-group"><label for="matrix-layout">选择布局</label> <select id="matrix-layout" class="select-input"><option value="1" selected="selected">布局 1</option><option value="2">布局 2</option><option value="3">布局 3</option><option value="4">布局 4</option></select></div><div id="custom-layout-settings" class="hidden"><div class="form-group"><label for="matrix-width">矩阵宽度</label> <input type="number" id="matrix-width" min="8" max="128" value="32" class="number-input"></div><div class="form-group"><label for="matrix-height">矩阵高度</label> <input type="number" id="matrix-height" min="8" max="64" value="8" class="number-input"></div></div></div><div><div class="form-group"><label for="color-mode">选择色彩模式</label> <select id="color-mode" class="select-input"><option value="Tungsten40W" selected="selected">钨丝灯泡 (40W)</option><option value="Tungsten100W">钨丝灯泡 (100W)</option></select></div></div><button id="save-advanced-settings" class="primary-btn">保存高级设置</button></div></div></div><script>
    const scanBtn = document.getElementById("scan-btn");
    const scanLoader = document.getElementById("scan-loader");
    const networkList = document.getElementById("network-list");
    const ssidInput = document.getElementById("ssid-input");
    const passwordInput = document.getElementById("password");
    const togglePasswordBtn = document.getElementById("toggle-password");
    const connectBtn = document.getElementById("connect-btn");
    const connectionStatus = document.getElementById("connection-status");
    const connectionProgress = document.getElementById("connection-progress");
    const connectionMessage = document.getElementById("connection-message");
    const successMessage = document.getElementById("success-message");
    const connectedNetworkEl = document.getElementById("connected-network");
    const ipAddressEl = document.getElementById("ip-address");

    const timezoneSelect = document.getElementById("timezone");
    const timeFormatToggle = document.getElementById("time-format");
    const showSecondsCheckbox = document.getElementById("show-seconds");
    const showDateCheckbox = document.getElementById("show-date");
    const textColorPicker = document.getElementById("text-color");
    const textColorValue = document.getElementById("text-color-value");
    const currentDayColorPicker = document.getElementById("current-day-color");
    const currentDayColorValue = document.getElementById("current-day-color-value");
    const otherDaysColorPicker = document.getElementById("other-days-color");
    const otherDaysColorValue = document.getElementById("other-days-color-value");
    const saveClockSettingsBtn = document.getElementById("save-clock-settings");

    const brightnessSlider = document.getElementById("brightness");
    const brightnessValue = document.getElementById("brightness-value");
    const nightModeToggle = document.getElementById("night-mode");
    const nightModeSettings = document.getElementById("night-mode-settings");
    const nightStartInput = document.getElementById("night-start");
    const nightEndInput = document.getElementById("night-end");
    const nightBrightnessSlider = document.getElementById("night-brightness");
    const nightBrightnessValue = document.getElementById("night-brightness-value");
    const matrixLayoutSelect = document.getElementById("matrix-layout");
    const customLayoutSettings = document.getElementById("custom-layout-settings");
    const matrixWidthInput = document.getElementById("matrix-width");
    const matrixHeightInput = document.getElementById("matrix-height");
    const colorModeSelect = document.getElementById("color-mode");
    const saveAdvancedSettingsBtn = document.getElementById("save-advanced-settings");

    const tabButtons = document.querySelectorAll(".tab-btn");
    const tabContents = document.querySelectorAll(".tab-content");

    // State
    let networks = [];
    let selectedNetwork = null;
    let isManualEntry = false;
    let clockSettings = {
        timezone: "UTC+08:00",
        timeFormat24h: true,
        showSeconds: true,
        showDate: true,
        textColor: "#ffffff",
        currentDayColor: "#ff5500",
        otherDaysColor: "#888888",
        brightness: 70,
        nightMode: false,
        nightStart: "22:00",
        nightEnd: "06:00",
        nightBrightness: 20,
    };

    let advancedSettings = {
        matrixLayout: "1",
        customWidth: 32,
        customHeight: 8,
        colorMode: "Tungsten40W",
    };
    let port = location.port || (window.location.protocol === 'https:' ? '443' : '80');
    let esp = `${window.location.protocol}//${window.location.hostname}:${port}/`;

    // Tab Navigation
    function switchTab(tabId) {
        tabButtons.forEach((btn) => {
            btn.classList.remove("active");
        });

        const activeButton = document.querySelector(`.tab-btn[data-tab="${tabId}"]`);
        if (activeButton) {
            activeButton.classList.add("active");
        }

        tabContents.forEach((content) => {
            content.classList.remove("active");
        });

        const activeContent = document.getElementById(tabId);
        if (activeContent) {
            activeContent.classList.add("active");
        }
    }
    function scanNetworks() {
        connectionStatus.textContent = "未连接";
        connectionStatus.style.backgroundColor = "#f5f5f5";
        connectionStatus.style.color = "#333";
        connectionProgress.style.display = "none";
        successMessage.style.display = "none";

        scanBtn.disabled = true;
        scanLoader.style.display = "block";
        networkList.style.display = "none";

        fetch(esp + "scan")
            .then(response => response.json())
            .then(data => {
                networks = data.networks;
                renderNetworks()
                scanBtn.disabled = false
                scanLoader.style.display = "none"
                networkList.style.display = "block"
            });
    }
    function renderNetworks() {
        networkList.innerHTML = "";
        networks.sort((a, b) => {
            return b.signal - a.signal;
        });
        networks.forEach((network) => {
            const networkItem = document.createElement("div")
            networkItem.className = "network-item"
            if (selectedNetwork && selectedNetwork.ssid === network.ssid) {
                networkItem.classList.add("selected")
            }

            const signalClass = network.signal > -50 ? "signal-high" : network.signal > -70 ? "signal-medium" : "signal-low"
            const signalEl = document.createElement("span")
            signalEl.className = `signal-strength ${signalClass}`

            const nameEl = document.createElement("span")
            nameEl.className = "network-name"
            nameEl.textContent = network.ssid

            const dbmEl = document.createElement("span")
            dbmEl.className = "signal-dbm"
            dbmEl.textContent = `${network.signal} dBm`

            const lockEl = document.createElement("span")
            lockEl.className = "lock-icon"
            if (!network.secured) {
                lockEl.style.visibility = "hidden"
            }

            networkItem.append(signalEl, nameEl, dbmEl, lockEl)
            networkItem.addEventListener("click", () => selectNetwork(network))
            networkList.appendChild(networkItem)
        });
    }
    function selectNetwork(network) {
        selectedNetwork = network;
        isManualEntry = false;

        const networkItems = document.querySelectorAll(".network-item");
        networkItems.forEach((item) => {
            item.classList.remove("selected");
            if (item.querySelector(".network-name").textContent === network.ssid) {
                item.classList.add("selected");
            }
        });

        ssidInput.value = network.ssid;
        updatePasswordField(network.secured);
    }
    function handleSsidInput() {
        const ssid = ssidInput.value.trim()
        if (!ssid) return

        const matchedNetwork = networks.find((network) => network.ssid === ssid)
        if (matchedNetwork) {
            selectNetwork(matchedNetwork)
        } else {
            isManualEntry = true
            selectedNetwork = { ssid, secured: true }
            document.querySelectorAll(".network-item").forEach((item) => item.classList.remove("selected"))
            passwordInput.disabled = false
            passwordInput.placeholder = "输入密码"
        }
    }
    function updatePasswordField(isSecured) {
        passwordInput.disabled = !isSecured
        passwordInput.placeholder = isSecured ? "输入密码" : "无需密码"
        if (!isSecured) passwordInput.value = ""
    }
    function togglePasswordVisibility() {
        const isPassword = passwordInput.type === "password"
        passwordInput.type = isPassword ? "text" : "password"
        togglePasswordBtn.innerHTML = isPassword ? `
            <svg xmlns="http://www.w3.org/2000/svg" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                <path d="M17.94 17.94A10.07 10.07 0 0 1 12 20c-7 0-11-8-11-8a18.45 18.45 0 0 1 5.06-5.94M9.9 4.24A9.12 9.12 0 0 1 12 4c7 0 11 8 11 8a18.5 18.5 0 0 1-2.16 3.19m-6.72-1.07a3 3 0 1 1-4.24-4.24"></path>
                <line x1="1" y1="1" x2="23" y2="23"></line>
            </svg>` : `
            <svg xmlns="http://www.w3.org/2000/svg" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                <path d="M1 12s4-8 11-8 11 8 11 8-4 8-11 8-11-8-11-8z"></path>
                <circle cx="12" cy="12" r="3"></circle>
            </svg>`
    }
    function connectToWiFi() {
        const ssid = ssidInput.value.trim()
        if (!ssid) {
            alert("请选择网络或手动输入SSID")
            ssidInput.focus()
            return
        }
        if (!selectedNetwork || selectedNetwork.ssid !== ssid) {
            selectedNetwork = { ssid, secured: true }
            isManualEntry = true
        }
        if (selectedNetwork.secured && passwordInput.value.length < 8) {
            alert("请输入有效密码（至少8个字符）")
            passwordInput.focus()
            return
        }
        connectionStatus.textContent = `正在连接到 ${ssidInput.value}...`
        connectionStatus.style.backgroundColor = "#fff3cd"
        connectionStatus.style.color = "#856404"
        connectionProgress.style.display = "block"
        successMessage.style.display = "none"
        connectBtn.disabled = true

        let dots = ""
        const connectingInterval = setInterval(() => {
            dots = dots.length < 3 ? dots + "." : ""
            connectionMessage.textContent = `正在连接到 ${ssidInput.value}${dots}`
        }, 500)

        const formdata = new FormData()
        formdata.append("ssid", ssidInput.value)
        formdata.append("password", passwordInput.value)

        fetch('/connect', { method: 'POST', body: formdata, redirect: 'follow' })
            .then(res => res.json())
            .then(data => {
                clearInterval(connectingInterval)

                if (data.success) {
                    connectionStatus.textContent = `已连接到 ${ssidInput.value}`
                    connectionStatus.style.backgroundColor = "#d4edda"
                    connectionStatus.style.color = "#155724"
                    connectionProgress.style.display = "none"
                    successMessage.style.display = "block"
                    connectedNetworkEl.textContent = ssidInput.value
                    ipAddressEl.textContent = data.ipAddress
                    connectBtn.disabled = false
                } else {
                    connectionStatus.textContent = `连接到 ${ssidInput.value} 失败: ${data.message}`
                    connectionStatus.style.backgroundColor = "#f8d7da"
                    connectionStatus.style.color = "#721c24"
                    connectionProgress.style.display = "none"
                    connectBtn.disabled = false
                }
            })
            .catch(() => {
                clearInterval(connectingInterval)
                connectionStatus.textContent = `连接到 ${ssidInput.value} 失败: 网络错误`
                connectionStatus.style.backgroundColor = "#f8d7da"
                connectionStatus.style.color = "#721c24"
                connectionProgress.style.display = "none"
                connectBtn.disabled = false
            })
    }
    function updateColorValues() {
        textColorValue.textContent = textColorPicker.value;
        currentDayColorValue.textContent = currentDayColorPicker.value;
        otherDaysColorValue.textContent = otherDaysColorPicker.value;
    }
    function saveClockSettings() {
        clockSettings = {
            timezone: timezoneSelect.value,
            timeFormat24h: timeFormatToggle.checked,
            showSeconds: showSecondsCheckbox.checked,
            showDate: showDateCheckbox.checked,
            textColor: textColorPicker.value,
            currentDayColor: currentDayColorPicker.value,
            otherDaysColor: otherDaysColorPicker.value,
            brightness: parseInt(brightnessSlider.value),
            nightMode: nightModeToggle.checked,
            nightStart: nightStartInput.value,
            nightEnd: nightEndInput.value,
            nightBrightness: parseInt(nightBrightnessSlider.value),
        };
        alert("时钟设置保存成功！");
    }
    function initClockSettingsForm() {
        timezoneSelect.value = clockSettings.timezone;
        timeFormatToggle.checked = clockSettings.timeFormat24h;
        showSecondsCheckbox.checked = clockSettings.showSeconds;
        showDateCheckbox.checked = clockSettings.showDate;
        textColorPicker.value = clockSettings.textColor;
        textColorValue.textContent = clockSettings.textColor;
        currentDayColorPicker.value = clockSettings.currentDayColor;
        currentDayColorValue.textContent = clockSettings.currentDayColor;
        otherDaysColorPicker.value = clockSettings.otherDaysColor;
        otherDaysColorValue.textContent = clockSettings.otherDaysColor;
    }
    function toggleCustomLayoutSettings() {
        if (matrixLayoutSelect.value === "custom") {
            customLayoutSettings.classList.remove("hidden");
        } else {
            customLayoutSettings.classList.add("hidden");
        }
    }
    function toggleNightModeSettings() {
        if (nightModeToggle.checked) {
            nightModeSettings.classList.remove("hidden");
        } else {
            nightModeSettings.classList.add("hidden");
        }
    }
    function updateBrightnessDisplay() {
        brightnessValue.textContent = brightnessSlider.value;
    }
    function updateNightBrightnessDisplay() {
        nightBrightnessValue.textContent = nightBrightnessSlider.value;
    }
    function saveAdvancedSettings() {
        advancedSettings = {
            matrixLayout: matrixLayoutSelect.value,
            customWidth: parseInt(matrixWidthInput.value),
            customHeight: parseInt(matrixHeightInput.value),
            colorMode: colorModeSelect.value,
        };
        alert("高级设置保存成功！");
    }
    function initAdvancedSettingsForm() {
        brightnessSlider.value = clockSettings.brightness;
        brightnessValue.textContent = clockSettings.brightness;
        nightModeToggle.checked = clockSettings.nightMode;
        nightStartInput.value = clockSettings.nightStart;
        nightEndInput.value = clockSettings.nightEnd;
        nightBrightnessSlider.value = clockSettings.nightBrightness;
        nightBrightnessValue.textContent = clockSettings.nightBrightness;

        matrixLayoutSelect.value = advancedSettings.matrixLayout;
        matrixWidthInput.value = advancedSettings.customWidth;
        matrixHeightInput.value = advancedSettings.customHeight;
        colorModeSelect.value = advancedSettings.colorMode;

        toggleNightModeSettings();
        toggleCustomLayoutSettings();
    }
    scanBtn.addEventListener("click", scanNetworks);
    ssidInput.addEventListener("input", handleSsidInput);
    ssidInput.addEventListener("blur", handleSsidInput);
    togglePasswordBtn.addEventListener("click", togglePasswordVisibility);
    connectBtn.addEventListener("click", connectToWiFi);

    nightModeToggle.addEventListener("change", toggleNightModeSettings);
    brightnessSlider.addEventListener("input", updateBrightnessDisplay);
    nightBrightnessSlider.addEventListener("input", updateNightBrightnessDisplay);
    saveClockSettingsBtn.addEventListener("click", saveClockSettings);
    textColorPicker.addEventListener("input", updateColorValues);
    currentDayColorPicker.addEventListener("input", updateColorValues);
    otherDaysColorPicker.addEventListener("input", updateColorValues);
    matrixLayoutSelect.addEventListener("change", toggleCustomLayoutSettings);
    saveAdvancedSettingsBtn.addEventListener("click", saveAdvancedSettings);
    tabButtons.forEach((btn) => {
        btn.addEventListener("click", () => {
            const tabId = btn.getAttribute("data-tab");
            if (tabId) {
                switchTab(tabId);
            }
        });
    });
    scanNetworks();
    initClockSettingsForm();
    initAdvancedSettingsForm();</script></body></html>
)";