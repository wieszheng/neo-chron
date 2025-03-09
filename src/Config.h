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
extern uint8_t NIGHT_START;
extern uint8_t NIGHT_END;
extern uint32_t WDC_ACTIVE;
extern uint32_t WDC_INACTIVE;
extern uint32_t TEXTCOLOR;

extern bool DEBUG_MODE;

void loadConfig();
void setConfig(JsonObject &json);
void saveConfig();

#endif // CONFIG_H