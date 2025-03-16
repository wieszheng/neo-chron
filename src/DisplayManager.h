#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <Arduino.h>
#include <FastLED_NeoMatrix.h>
#include "Config.h"

struct Animation
{
  const uint16_t (*frames)[8 * 8];
  int frameCount;
};


class DisplayManager_
{
private:
    DisplayManager_() = default;
    bool settingsMenuActive = false;

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
    void drawGif(int16_t x, int16_t y, Animation animation);
    void gradationText(int16_t x, int16_t y, const char *text, bool clear);
    void printText(int16_t x, int16_t y, const char *text, bool centered, bool ignoreUppercase);
    void drawWifi(int x, int y, int state);
    
    void showOption(int optionIndex);
    void activateSettingsMenu();
    void deactivateSettingsMenu();
    void drawTimeSetting(int h, int m, bool selected);
};

extern DisplayManager_ &DisplayManager;

#endif