#include <Arduino.h>
#include "WebServer.h"

#include "DisplayManager.h"
#include "ButtonManager.h"
#include "HeFeng.h"
#include "Config.h"


ESP8266WebServer server(80);
WebServer mws(server);

void setup()
{
  Serial.begin(115200);
  delay(2000);

  if (LittleFS.begin())
  {
    if (DEBUG_MODE)
      DEBUG_PRINTLN(F("Filesystem mounted"));

    loadConfig();
  }
  else
  {
    if (DEBUG_MODE)
      DEBUG_PRINTLN(F("Error mounting filesystem"));
  }
  DisplayManager.setup();
  ButtonManager.setup();
  delay(250);
  DisplayManager.gradationText(4, 6, "NChron", true);
  DisplayManager.show();
  mws.startWiFi(10000, HOSTNAME.c_str(), "12345678");
  mws.begin();
  DisplayManager.loadNativeApps();
  configTzTime(NTP_TZ.c_str(), NTP_SERVER.c_str());
  tm timeInfo;
  getLocalTime(&timeInfo);
}

void loop()
{
  mws.run();
  DisplayManager.tick();
  ButtonManager.tick();
}