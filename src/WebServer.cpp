#include "WebServer.h"


IPAddress softLocal(192, 168, 4, 1);
IPAddress softGateway(192, 168, 4, 1);
IPAddress softSubnet(255, 255, 255, 0);


WebServer::WebServer(ESP8266WebServer &server)
{
    webserver = &server;
}

bool WebServer::begin(int port)
{
    webserver->on("/", HTTP_GET, std::bind(&WebServer::handleRoot, this));
    webserver->on("/connect", HTTP_POST, std::bind(&WebServer::doWifiConnection, this));
    webserver->on("/scan", HTTP_GET, std::bind(&WebServer::handleScanNetworks, this));
    webserver->on("/config", HTTP_POST, std::bind(&WebServer::handleSetConfig, this));
    webserver->on("/config", HTTP_GET, std::bind(&WebServer::handleGetConfig, this));
    webserver->on("/reset", HTTP_GET, std::bind(&WebServer::handleReset, this));

    webserver->onNotFound(std::bind(&WebServer::handleNotFound, this));
    webserver->begin(port);

    if (!MDNS.begin(HOSTNAME))
    {
      if (DEBUG_MODE)
        DEBUG_PRINTLN(F("Error setting up MDNS responder!"));
    }
    else
    {
      MDNS.addService("http", "tcp", 80);
      MDNS.addServiceTxt("neo_chron", "tcp", "name", HOSTNAME.c_str());
    }

    return true;
}

void WebServer::run()
{
    webserver->handleClient();
    if (m_apmode)
        m_dnsServer.processNextRequest();

    unsigned long currentMillis = millis();
    if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >= interval) && !m_apmode)
    {
        Serial.println("Reconnecting to WiFi...");
        WiFi.disconnect();
        WiFi.reconnect();
        previousMillis = currentMillis;
    }
}

void WebServer::handleRoot()
{
    // webserver->send(200, "text/html", root_html);
    if (LittleFS.exists("/index.html"))
    {
        File file = LittleFS.open("/index.html", "r");
        webserver->streamFile(file, "text/html");
        file.close();
    }
    else
    {
        webserver->send(200, "text/plain", "<h1>ESP8266 Web Server</h1><p>未发现index.html文件</p>");
    }
    return;
}

void WebServer::handleReset()
{
    webserver->send(200, "text/plain", WiFi.localIP().toString());
    delay(500);
    ESP.restart();
}
void WebServer::handleScanNetworks()
{
    Serial.println("Start scan WiFi networks...");
    int res = WiFi.scanComplete();
    if (res == -2)
    {
        WiFi.scanNetworks(true);
    }
    else if (res)
    {
        Serial.print("done!\nNumber of networks:");
        Serial.println(res);

        String json = "{\"networks\":[";

        for (int i = 0; i < res; ++i)
        {
            json += "{\"ssid\":\"" + String(WiFi.SSID(i)) + "\",\"signal\":" + String(WiFi.RSSI(i)) + ",\"secured\":" + (WiFi.encryptionType(i) == ENC_TYPE_NONE ? "false" : "true") + "}";
            if (i < res - 1)
            {
                json += ",";
            }
        }
        json += "]}";

        webserver->send(200, "application/json", json);
        WiFi.scanDelete();
        if (WiFi.scanComplete() == -2)
        {
            WiFi.scanNetworks(true);
        }
    }

    webserver->send(200, "application/json", "{\"networks\" : []}");
}

void WebServer::handleNotFound()
{
    webserver->send(404, "text/plain", "Not found");
}

void WebServer::doWifiConnection()
{
    String ssid, pass;
    if (webserver->hasArg("ssid"))
    {
        ssid = webserver->arg("ssid");
    }

    if (webserver->hasArg("password"))
    {
        pass = webserver->arg("password");
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        IPAddress ip = WiFi.localIP();
        String resp = "{\"success\": true, \"message\": \"ESP is currently connected to a WiFi network.\", \"ipAddress\": \"";
        resp += ip.toString();
        resp += "\"}";
        webserver->send(200, "application/json", resp);
        return;
    }

    if (true)
    {
        // Store current WiFi configuration in flash
        WiFi.persistent(true);
        struct station_config stationConf;
        wifi_station_get_config_default(&stationConf);
        // Clear previous configuration
        memset(&stationConf, 0, sizeof(stationConf));
        os_memcpy(&stationConf.ssid, ssid.c_str(), ssid.length());
        os_memcpy(&stationConf.password, pass.c_str(), pass.length());
        wifi_set_opmode(STATION_MODE);
        wifi_station_set_config(&stationConf);
    }
    if (ssid.length() && pass.length())
    {
        WiFi.mode(WIFI_AP_STA);
        Serial.printf("\n\nConnecting to %s\n", ssid.c_str());
        WiFi.begin(ssid.c_str(), pass.c_str());

        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println("Disconnect from current WiFi network");
            WiFi.disconnect();
            delay(10);
        }

        uint32_t beginTime = millis();
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(250);
            Serial.print("*");
            ESP.wdtFeed();
            if (millis() - beginTime > 10000)
            {
                webserver->send(200, "application/json", "{\"success\": false, \"message\": \"Connection timeout! Check password or try to restart ESP.\"}");
                delay(100);
                Serial.println("\nWiFi connect timeout!");
                return;
            }
        }
        if (WiFi.status() == WL_CONNECTED)
        {
            // WiFi.softAPdisconnect();
            IPAddress ip = WiFi.localIP();
            Serial.print(F("\nConnected to Wifi! IP address: "));
            Serial.println(ip);
            String resp = "{\"success\": true, \"ipAddress\": \"";
            resp += ip.toString();
            resp += "\"}";
            Serial.printf("%s", resp.c_str());
            webserver->send(200, "application/json", resp);
        }
    }
    webserver->send(200, "application/json", "{\"success\": false, \"message\": \"Wrong credentials provided\"}");
}

IPAddress WebServer::startWiFi(uint32_t timeout, const char *apSSID, const char *apPsw)
{
    
    WiFi.hostname(HOSTNAME.c_str());
    WiFi.softAPConfig(softLocal, softGateway, softSubnet);
    IPAddress ip;
    m_timeout = timeout;
    WiFi.mode(WIFI_STA);
    struct station_config conf;
    wifi_station_get_config_default(&conf);
    const char *_ssid = reinterpret_cast<const char *>(conf.ssid);
    const char *_pass = reinterpret_cast<const char *>(conf.password);
    if (strlen(_ssid))
    {
        WiFi.begin(_ssid, _pass);
        Serial.print("\nConnecting to ");
        Serial.println(_ssid);

        uint32_t startTime = millis();
        while (WiFi.status() != WL_CONNECTED)
        {
            // execute callback function during wifi connection
            // if (fn != nullptr)
            //     fn();
            delay(250);
            Serial.print(".");
            if (WiFi.status() == WL_CONNECTED)
            {
                ip = WiFi.localIP();
                Serial.print(F("\nServer IP address: "));
                Serial.println(ip);
                Serial.println();
                return ip;
            }
            if (millis() - startTime > m_timeout)
            {
                Serial.println("Timeout!");
                break;
            }
        }
    }

    startCaptivePortal(apSSID, apPsw);
    return ip;
}

bool WebServer::startCaptivePortal(const char *ssid, const char *pass)
{
    m_apmode = true;
    WiFi.mode(WIFI_AP_STA);
    delay(250);
    WiFi.softAP(ssid, pass);

    m_dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
    m_dnsServer.start(53, "*", WiFi.softAPIP());
    Serial.print(F("\nAP mode.\nServer IP address: "));
    Serial.println(WiFi.softAPIP());
    Serial.println();

    return true;
}

void WebServer::handleSetConfig()
{
    if (webserver->hasArg("plain"))
    {
        String jsonString = webserver->arg("plain");
        DynamicJsonBuffer jsonBuffer;
        JsonObject &json = jsonBuffer.parseObject(jsonString);

        Serial.println(String(json.measureLength()));

        if (json.success())
        {
            Serial.println("Incoming JSON length: " + String(json.measureLength()));
            setConfig(json);
            webserver->send(200, "application/json", "{\"success\": true, \"message\": \"Configuration saved\"}");
            delay(500);
            ESP.restart();
        }
        else
        {
            webserver->send(200, "application/json", "{\"success\": false, \"message\": \"Invalid JSON\"}");
        }
    }
    else
    {
        webserver->send(200, "application/json", "{\"success\": false, \"message\": \"No data received\"}");
    }
}

void WebServer::handleGetConfig()
{
    webserver->send(200, "application/json", getConfig());
}