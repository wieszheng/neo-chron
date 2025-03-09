#include "Config.h"

char *getID()
{
    uint8_t mac[6];
    WiFi.macAddress(mac);
    char *macStr = new char[24];
    snprintf(macStr, 24, "Neo Chron-%02x%02x%02x", mac[3], mac[4], mac[5]);
    if (DEBUG_MODE)
        DEBUG_PRINTLN(F("Starting filesystem"));
    return macStr;
}

void saveConfig()
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &json = jsonBuffer.createObject();

    json["version"] = VERSION;
    json["matrix_layout"] = MATRIX_LAYOUT;
    json["matrix_temp_correction"] = MATRIX_TEMP_CORRECTION;
    json["min_brightness"] = MIN_BRIGHTNESS;
    json["max_brightness"] = MAX_BRIGHTNESS;
    json["min_brightness_night"] = MIN_BRIGHTNESS_NIGHT;
    json["max_brightness_night"] = MAX_BRIGHTNESS_NIGHT;
    json["night_start"] = NIGHT_START;
    json["night_end"] = NIGHT_END;
    json["wdc_active"] = WDC_ACTIVE;
    json["wdc_inactive"] = WDC_INACTIVE;
    json["text_color"] = TEXTCOLOR;
    json["debug_mode"] = DEBUG_MODE;

    File configFile = LittleFS.open("/config.json", "w");
    json.printTo(configFile);
    configFile.close();
    if (DEBUG_MODE)
        DEBUG_PRINTLN(F("SaveConfig Saved!"));
}

void setConfig(JsonObject &json)
{
    if (json.containsKey("matrix_layout"))
    {
        MATRIX_LAYOUT = json["matrix_layout"].as<int>();
    }
    if (json.containsKey("matrix_temp_correction"))
    {
        MATRIX_TEMP_CORRECTION = json["matrix_temp_correction"].as<int>();
    }
    if (json.containsKey("min_brightness"))
    {
        MIN_BRIGHTNESS = json["min_brightness"].as<int>();
    }
    if (json.containsKey("max_brightness"))
    {
        MAX_BRIGHTNESS = json["max_brightness"].as<int>();
    }
    if (json.containsKey("min_brightness_night"))
    {
        MIN_BRIGHTNESS_NIGHT = json["min_brightness_night"].as<int>();
    }
    if (json.containsKey("max_brightness_night"))
    {
        MAX_BRIGHTNESS_NIGHT = json["max_brightness_night"].as<int>();
    }
    if (json.containsKey("night_start"))
    {
        NIGHT_START = json["night_start"].as<int>();
    }
    if (json.containsKey("night_end"))
    {
        NIGHT_END = json["night_end"].as<int>();
    }
    if (json.containsKey("wdc_active"))
    {
        WDC_ACTIVE = json["wdc_active"].as<int>();
    }
    if (json.containsKey("wdc_inactive"))
    {
        WDC_INACTIVE = json["wdc_inactive"].as<int>();
    }
    if (json.containsKey("text_color"))
    {
        TEXTCOLOR = json["text_color"].as<int>();
    }
    if (json.containsKey("debug_mode"))
    {
        DEBUG_MODE = json["debug_mode"].as<bool>();
    }
    saveConfig();
}

void loadConfig()
{
    if (LittleFS.exists("/config.json"))
    {
        File configFile = LittleFS.open("/config.json", "r");
        if (configFile)
        {
            DynamicJsonBuffer jsonBuffer;
            JsonObject &json = jsonBuffer.parseObject(configFile);

            if (json.success())
            {
                if (json.containsKey("version"))
                {
                    json["version"].as<String>();
                }
                if (json.containsKey("matrix_layout"))
                {
                    MATRIX_LAYOUT = json["matrix_layout"].as<int>();
                }
                if (json.containsKey("matrix_temp_correction"))
                {
                    MATRIX_TEMP_CORRECTION = json["matrix_temp_correction"].as<int>();
                }
                // 亮度配置
                if (json.containsKey("min_brightness"))
                {
                    MIN_BRIGHTNESS = json["min_brightness"].as<int>();
                }
                if (json.containsKey("max_brightness"))
                {
                    MAX_BRIGHTNESS = json["max_brightness"].as<int>();
                }
                if (json.containsKey("min_brightness_night"))
                {
                    MIN_BRIGHTNESS_NIGHT = json["min_brightness_night"].as<int>();
                }
                if (json.containsKey("max_brightness_night"))
                {
                    MAX_BRIGHTNESS_NIGHT = json["max_brightness_night"].as<int>();
                }
                if (json.containsKey("night_end"))
                {
                    NIGHT_END = json["night_end"].as<int>();
                }
                if (json.containsKey("night_start"))
                {
                    NIGHT_START = json["night_start"].as<int>();
                }
                if (json.containsKey("wdc_active"))
                {
                    WDC_ACTIVE = json["wdc_active"];
                }
                if (json.containsKey("wdc_inactive"))
                {
                    WDC_INACTIVE = json["wdc_inactive"];
                }
                if (json.containsKey("text_color"))
                {
                    TEXTCOLOR = json["text_color"];
                }

                if (json.containsKey("debug_mode"))
                {
                    DEBUG_MODE = json["debug_mode"].as<bool>();
                }
                if (DEBUG_MODE)
                    DEBUG_PRINTLN(F("LoadConfig Loaded!"));
                DEBUG_PRINTLN(MAX_BRIGHTNESS);
            }
        }
    }
    else
    {
        if (DEBUG_MODE)
            DEBUG_PRINTLN(F("LoadConfig No Configfile, init new file"));
        saveConfig();
    }
    uniqueID = getID();
    HOSTNAME = String(uniqueID);
}

const char *uniqueID;
const char *VERSION = "1.1";
IPAddress local_IP;
IPAddress gateway;
IPAddress subnet;
IPAddress primaryDNS;
IPAddress secondaryDNS;
String HOSTNAME = "";

int MATRIX_LAYOUT = 0;
int MATRIX_TEMP_CORRECTION = 0;

uint32_t WDC_ACTIVE = 0xFFFFFF;
uint32_t WDC_INACTIVE = 0x666666;
uint32_t TEXTCOLOR = 0xFFFFFF;

uint8_t MIN_BRIGHTNESS = 10;
uint8_t MAX_BRIGHTNESS = 255;
uint8_t MIN_BRIGHTNESS_NIGHT = 10;
uint8_t MAX_BRIGHTNESS_NIGHT = 255;
uint8_t NIGHT_START = 22;
uint8_t NIGHT_END = 6;

bool DEBUG_MODE = true;