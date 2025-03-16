#ifndef HEFENG_H
#define HEFENG_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoUZlib.h>

struct WeatherData
{
    String temp;      // 温度
    String humidity;  // 湿度
    String windScale; // 风力等级
    String text;      // 天气现象（如"晴"）
};

class HeFeng
{
public:
    HeFeng(String userKey, String location, String unit, String lang);
    WeatherData getWeatherData();

private:
    String _requserKey;
    String _reqLocation;
    String _reqUnit;
    String _reqLang;

    std::unique_ptr<BearSSL::WiFiClientSecure> client;
    HTTPClient https;

};

#endif // HEFENG_H