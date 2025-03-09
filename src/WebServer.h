#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <LittleFS.h>


class WebServer
{
public:
    WebServer(ESP8266WebServer &serve);
    bool begin(int port = 80);
    void run();

    IPAddress startWiFi(uint32_t timeout, const char *apSSID, const char *apPsw);
    bool startCaptivePortal(const char *ssid, const char *pass);

private:
    ESP8266WebServer *webserver;
    DNSServer m_dnsServer;
    unsigned long previousMillis = 0;
    unsigned long interval = 10000;
    bool m_apmode = false;
    uint32_t m_timeout = 10000;
   

    void handleRoot();
    void handleReset();
    void handleScanNetworks();
    void handleSetConfig();
    void doWifiConnection();
    void handleNotFound();

};
#endif // WEBSERVER_H