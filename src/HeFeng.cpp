#include "HeFeng.h"

HeFeng::HeFeng(String userKey, String location, String unit, String lang)
    : _requserKey(userKey), _reqLocation(location), _reqUnit(unit), _reqLang(lang)
{
    client.reset(new BearSSL::WiFiClientSecure);
    client->setInsecure();
}

WeatherData HeFeng::getWeatherData()
{
    WeatherData data = {"?", "?", "?", "?"};
    if (!client)
    {
        Serial.println("Client not initialized.");
        return data;
    }

    Serial.print("[HTTPS] begin...\n");
    String url = "https://devapi.qweather.com/v7/weather/now?location=" + _reqLocation + "&key=" + _requserKey + "&unit=" + _reqUnit + "&lang=" + _reqLang + "&gzip=n";
    Serial.print("[HTTPS] url: ");
    Serial.println(url);

    if (https.begin(*client, url))
    {
        https.setTimeout(3000);
        https.addHeader("Accept-Encoding", "gzip");
        Serial.print("[HTTPS] GET...\n");
        int httpCode = https.GET();
        if (httpCode > 0)
        {
            Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
            if (httpCode == HTTP_CODE_OK)
            {
                String payload = https.getString();
                uint8_t *outbuf = nullptr;
                uint32_t outsize = 0;
                if (ArduinoUZlib::decompress((uint8_t *)payload.c_str(), payload.length(), outbuf, outsize) != 0)
                {
                    StaticJsonBuffer<1024> jsonBuffer;
                    JsonObject &root = jsonBuffer.parseObject(outbuf);
                    if (root.success())
                    {
                        data.temp = root["now"]["temp"].as<String>();
                        data.humidity = root["now"]["humidity"].as<String>();
                        data.windScale = root["now"]["windScale"].as<String>();
                        data.text = root["now"]["text"].as<String>();
                        Serial.println("====== Weather Info ======");
                        Serial.printf("Temperature: %s℃\n", data.temp.c_str());
                        Serial.printf("Humidity: %s%%\n", data.humidity.c_str());
                        Serial.printf("Conditions: %s\n", data.text.c_str());
                        Serial.printf("Wind Scale: %s\n", data.windScale.c_str());
                        Serial.println("==========================");
                    }
                }

                free(outbuf);
            }
        }
        else
        {
            Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        }
        https.end();
    }

    return data;
}