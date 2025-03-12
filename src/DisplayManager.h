#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <Arduino.h>
#include <FastLED_NeoMatrix.h>
#include "Config.h"

class DisplayManager_
{
private:
    DisplayManager_() = default;

public:
    static DisplayManager_ &getInstance();
    void setup();

    void clear();
    void show();
    void tick();
    void loadNativeApps();
    
    void setBrightness(uint8_t brightness);
    void setTextColor(uint16_t color);
    void nightBrightness();

    void drawBMP(int16_t x, int16_t y, const uint16_t bitmap[], int16_t w, int16_t h);
    void gradationText(int16_t x, int16_t y, const char *text, bool clear);
    void printText(int16_t x, int16_t y, const char *text, bool centered, bool ignoreUppercase);
    void drawWifi(int x, int y, int state);

    uint16_t gradation(int x, int y);
    
};

extern DisplayManager_ &DisplayManager;

#endif