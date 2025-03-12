#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINTLN(x)    \
  {                         \
    Serial.print("[");      \
    Serial.print(millis()); \
    Serial.print("] [");    \
    Serial.print(__func__); \
    Serial.print("]: ");    \
    Serial.println(x);      \
  }
#define DEBUG_PRINTF(format, ...)                                                        \
  {                                                                                      \
    String formattedMessage = "[" + String(millis()) + "] [" + String(__func__) + "]: "; \
    Serial.print(formattedMessage);                                                      \
    Serial.printf(format, ##__VA_ARGS__);                                                \
    Serial.println();                                                                    \
  }
#else
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINTF(format, ...)
#endif


extern const char *uniqueID;
extern const char *VERSION;
extern IPAddress local_IP;
extern IPAddress gateway;
extern IPAddress subnet;
extern IPAddress primaryDNS;
extern IPAddress secondaryDNS;
extern String HOSTNAME;
extern int MATRIX_LAYOUT;
extern int MATRIX_TEMP_CORRECTION;

extern uint8_t MIN_BRIGHTNESS;
extern uint8_t MAX_BRIGHTNESS;
extern uint8_t MIN_BRIGHTNESS_NIGHT;
extern uint8_t MAX_BRIGHTNESS_NIGHT;
extern String NIGHT_START;
extern String NIGHT_END;
extern String WDC_ACTIVE;
extern String WDC_INACTIVE;
extern String TEXTCOLOR;
extern String HUM_COLOR;
extern String TEMP_COLOR;

extern bool DEBUG_MODE;

extern String NTP_SERVER;
extern String NTP_TZ;

extern String TIME_FORMAT;
extern String DATE_FORMAT;
extern bool TIME_SHOW_S;
extern bool DATE_SHOW_Y ;
extern String TIME_ICON;
extern String DATE_ICON;

extern bool SHOW_DATE;

void loadConfig();
void setConfig(JsonObject &json);
String getConfig();
void saveConfig();

#endif // CONFIG_H