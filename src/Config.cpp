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
    json["ntp_server"] = NTP_SERVER;
    json["ntp_tz"] = NTP_TZ;
    json["time_format"] = TIME_FORMAT;
    json["date_format"] = DATE_FORMAT;
    json["time_show_s"] = TIME_SHOW_S;
    json["date_show_y"] = DATE_SHOW_Y;
    json["time_icon"] = TIME_ICON;
    json["date_icon"] = DATE_ICON;
    json["temp_color"] = TEMP_COLOR;
    json["hum_color"] = HUM_COLOR;
    json["debug_mode"] = DEBUG_MODE;
    json["show_date"] = SHOW_DATE;

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
        NIGHT_START = json["night_start"].as<String>();
    }
    if (json.containsKey("night_end"))
    {
        NIGHT_END = json["night_end"].as<String>();
    }
    if (json.containsKey("wdc_active"))
    {
        WDC_ACTIVE = json["wdc_active"].as<String>();
    }
    if (json.containsKey("wdc_inactive"))
    {
        WDC_INACTIVE = json["wdc_inactive"].as<String>();
    }
    if (json.containsKey("text_color"))
    {
        TEXTCOLOR = json["text_color"].as<String>();
    }
    if (json.containsKey("ntp_server"))
    {
        NTP_SERVER = json["ntp_server"].as<String>();
    }
    if (json.containsKey("ntp_tz"))
    {
        NTP_TZ = json["ntp_tz"].as<String>();
    }
    if (json.containsKey("time_format"))
    {
        TIME_FORMAT = json["time_format"].as<String>();
    }
    if (json.containsKey("date_format"))
    {
        DATE_FORMAT = json["date_format"].as<String>();
    }
    if (json.containsKey("time_show_s"))
    {
        TIME_SHOW_S = json["time_show_s"].as<bool>();
    }
    if (json.containsKey("date_show_y"))
    {
        DATE_SHOW_Y = json["date_show_y"].as<bool>();
    }
    if (json.containsKey("time_icon"))
    {
        TIME_ICON = json["time_icon"].as<String>();
    }
    if (json.containsKey("date_icon"))
    {
        DATE_ICON = json["date_icon"].as<String>();
    }
    if (json.containsKey("temp_color"))
    {
        TEMP_COLOR = json["temp_color"].as<String>();
    }
    if (json.containsKey("hum_color"))
    {
        HUM_COLOR = json["hum_color"].as<String>();
    }
    if (json.containsKey("show_date"))
    {
        SHOW_DATE = json["show_date"].as<bool>();
    }
    if (json.containsKey("debug_mode"))
    {
        DEBUG_MODE = json["debug_mode"].as<bool>();
    }
    saveConfig();
}

String getConfig()
{
    File configFile = LittleFS.open("/config.json", "r");
    if (configFile)
    {
        if (DEBUG_MODE)
            DEBUG_PRINTLN(F("Opened config file!"));
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject &root = jsonBuffer.parseObject(buf.get());

        String json;
        root.printTo(json);

        return json;
    }
    return "";
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
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("MATRIX_LAYOUT: " + String(MATRIX_LAYOUT));
                }
                if (json.containsKey("matrix_temp_correction"))
                {
                    MATRIX_TEMP_CORRECTION = json["matrix_temp_correction"].as<int>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("MATRIX_TEMP_CORRECTION: " + String(MATRIX_TEMP_CORRECTION));
                }
                // 亮度配置
                if (json.containsKey("min_brightness"))
                {
                    MIN_BRIGHTNESS = json["min_brightness"].as<int>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("MIN_BRIGHTNESS: " + String(MIN_BRIGHTNESS));
                }
                if (json.containsKey("max_brightness"))
                {
                    MAX_BRIGHTNESS = json["max_brightness"].as<int>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("MAX_BRIGHTNESS: " + String(MAX_BRIGHTNESS));
                }
                if (json.containsKey("min_brightness_night"))
                {
                    MIN_BRIGHTNESS_NIGHT = json["min_brightness_night"].as<int>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("MIN_BRIGHTNESS_NIGHT: " + String(MIN_BRIGHTNESS_NIGHT));
                }
                if (json.containsKey("max_brightness_night"))
                {
                    MAX_BRIGHTNESS_NIGHT = json["max_brightness_night"].as<int>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("MAX_BRIGHTNESS_NIGHT: " + String(MAX_BRIGHTNESS_NIGHT));
                }
                if (json.containsKey("night_end"))
                {
                    NIGHT_END = json["night_end"].as<String>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("NIGHT_END: " + NIGHT_END);
                }
                if (json.containsKey("night_start"))
                {
                    NIGHT_START = json["night_start"].as<String>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("NIGHT_START: " + NIGHT_START);
                }
                if (json.containsKey("wdc_active"))
                {
                    WDC_ACTIVE = json["wdc_active"].as<String>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("WDC_ACTIVE: " + WDC_ACTIVE);
                }
                if (json.containsKey("wdc_inactive"))
                {
                    WDC_INACTIVE = json["wdc_inactive"].as<String>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("WDC_INACTIVE: " + WDC_INACTIVE);
                }
                if (json.containsKey("text_color"))
                {
                    TEXTCOLOR = json["text_color"].as<String>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("TEXTCOLOR: " + TEXTCOLOR);
                }
                if (json.containsKey("ntp_server"))
                {
                    NTP_SERVER = json["ntp_server"].as<String>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("NTP_SERVER: " + NTP_SERVER);
                }
                if (json.containsKey("ntp_tz"))
                {
                    NTP_TZ = json["ntp_tz"].as<String>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("NTP_TZ: " + NTP_TZ);
                }
                if (json.containsKey("time_format"))
                {
                    TIME_FORMAT = json["time_format"].as<String>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("TIME_FORMAT: " + TIME_FORMAT);
                }
                if (json.containsKey("date_format"))
                {
                    DATE_FORMAT = json["date_format"].as<String>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("DATE_FORMAT: " + DATE_FORMAT);
                }
                if (json.containsKey("time_show_s"))
                {
                    TIME_SHOW_S = json["time_show_s"].as<bool>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("TIME_SHOW_S: " + String(TIME_SHOW_S));
                }
                if (json.containsKey("date_show_y"))
                {
                    DATE_SHOW_Y = json["date_show_y"].as<bool>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("DATE_SHOW_Y: " + String(DATE_SHOW_Y));
                }
                if (json.containsKey("time_icon"))
                {
                    TIME_ICON = json["time_icon"].as<String>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("TIME_ICON: " + TIME_ICON);
                }
                if (json.containsKey("date_icon"))
                {
                    DATE_ICON = json["date_icon"].as<String>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("DATE_ICON: " + DATE_ICON);
                }
                if (json.containsKey("temp_color"))
                {
                    TEMP_COLOR = json["temp_color"].as<String>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("TEMP_COLOR: " + TEMP_COLOR);
                }
                if (json.containsKey("hum_color"))
                {
                    HUM_COLOR = json["hum_color"].as<String>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("HUM_COLOR: " + HUM_COLOR);
                }
                if (json.containsKey("show_date"))
                {
                    SHOW_DATE = json["show_date"].as<bool>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("DEBUG_MODE: " + String(DEBUG_MODE));
                }
                if (json.containsKey("debug_mode"))
                {
                    DEBUG_MODE = json["debug_mode"].as<bool>();
                    if (DEBUG_MODE)
                        DEBUG_PRINTLN("DEBUG_MODE: " + String(DEBUG_MODE));
                }
                if (DEBUG_MODE)
                    DEBUG_PRINTLN(F("LoadConfig Loaded!"));
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

int MATRIX_LAYOUT = 1;
int MATRIX_TEMP_CORRECTION = 0;

String WDC_ACTIVE = "#f273e1";
String WDC_INACTIVE = "#00bfff";
String TEXTCOLOR = "#FFFFFF";

uint8_t MIN_BRIGHTNESS = 10;
uint8_t MAX_BRIGHTNESS = 255;
uint8_t MIN_BRIGHTNESS_NIGHT = 10;
uint8_t MAX_BRIGHTNESS_NIGHT = 255;
String NIGHT_START = "22:10";
String NIGHT_END = "7:30";

String NTP_SERVER = "de.pool.ntp.org";
String NTP_TZ = "CST-8";

String TIME_FORMAT = "%H:%M";
String DATE_FORMAT = "%d.%m.%y";
bool TIME_SHOW_S = false;
bool DATE_SHOW_Y = false;
String TIME_ICON = "none";
String DATE_ICON = "none";

String TEMP_COLOR = "#FF0000";
String HUM_COLOR = "#0000FF";

bool SHOW_DATE = true;

bool DEBUG_MODE = true;