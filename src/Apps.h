#ifndef APPS_H
#define APPS_H

#include "DisplayManager.h"
#include "HeFeng.h"
#include "Icons.h"
#include "Tools.h"

String Key = "4a157caf810240fc982186893fc8f8af"; // 私钥
String Location = "101010700";                   // 城市代码
String Unit = "m";                               // 公制-m/英制-i
String Lang = "zh";
unsigned long previousMillis = 0;
const long interval = 1000 * 100;

HeFeng hf(Key, Location, Unit, Lang);
WeatherData data;

const char *getTimeFormat()
{
    if (TIME_SHOW_S)
    {
        return "%H:%M:%S";
    }
    else
    {
        return TIME_FORMAT.c_str();
    }
}

const char *getDateFormat()
{
    if (DATE_SHOW_Y)
    {
        return DATE_FORMAT.c_str();
    }
    else
    {
        return "%m.%d.";
    }
}

void TimeApp(FastLED_NeoMatrix *matrix, int16_t x, int16_t y)
{
    uint16_t color = HEXtoColor(TEXTCOLOR.c_str());
    DisplayManager.setTextColor(color);

    time_t now = time(nullptr);
    struct tm *timeInfo;
    timeInfo = localtime(&now);
    const char *timeformat = getTimeFormat();
    char t[20];
    char t2[20];
    if (timeformat[2] == ' ')
    {
        strcpy(t2, timeformat);
        if (now % 2)
        {
            t2[2] = ' ';
        }
        else
        {
            t2[2] = ':';
        }
        strftime(t, sizeof(t), t2, localtime(&now));
    }
    else
    {
        strftime(t, sizeof(t), timeformat, localtime(&now));
    }
    int16_t wdPosX = 0;
    if (TIME_ICON.length() > 0 && !TIME_SHOW_S)
    {
        if (TIME_ICON == "none")
        {
            DisplayManager.printText(0 + x, y, t, true, false);
            wdPosX = -4;
        }
        else
        {
            DisplayManager.drawBMP(x, y - 6, getIcon(TIME_ICON.toInt()), 8, 8);
            // Animation icon_ = {icon_laoren, sizeof(icon_laoren) / sizeof(icon_laoren[0])};
            // DisplayManager.drawGif(x, y - 6, icon_);
            DisplayManager.printText(12 + x, y, t, false, false);
        }
    }
    else
    {
        DisplayManager.printText(0 + x, y, t, true, false);
    }

    uint8_t LINE_WIDTH = !TIME_SHOW_S > 0 ? 2 : 3;
    uint8_t LINE_SPACING = 1;
    uint8_t LINE_START = !TIME_SHOW_S > 0 ? 10 : 2;
    int dayOffset = 0; // 周日偏移量

    for (int i = 0; i <= 6; i++)
    {
        int lineStart = LINE_START + i * (LINE_WIDTH + LINE_SPACING);
        int lineEnd = lineStart + LINE_WIDTH - 1;
        if (i == (timeInfo->tm_wday + 6 + dayOffset) % 7)
            color = HEXtoColor(WDC_ACTIVE.c_str());
        else
            color = HEXtoColor(WDC_INACTIVE.c_str());

        matrix->drawLine(lineStart + x + wdPosX, 1 + y, lineEnd + x + wdPosX, 1 + y, color);
    }
}

void DateApp(FastLED_NeoMatrix *matrix, int16_t x, int16_t y)
{
    uint16_t color = HEXtoColor(TEXTCOLOR.c_str());
    DisplayManager.setTextColor(color);

    time_t now = time(nullptr);
    struct tm *timeInfo;
    timeInfo = localtime(&now);
    const char *dateformat = getDateFormat();
    char d[20];
    strftime(d, sizeof(d), dateformat, localtime(&now));

    int16_t wdPosX = 0;

    if (DATE_ICON.length() > 0 && !DATE_SHOW_Y)
    {
        if (TIME_ICON == "none")
        {
            DisplayManager.printText(x, y, d, true, false);
            wdPosX = -4;
        }
        else
        {
            DisplayManager.drawBMP(x, y - 6, getIcon(DATE_ICON.toInt()), 8, 8);
            DisplayManager.printText(11 + x, y, d, false, false);
        }
    }
    else
    {
        DisplayManager.printText(x, y, d, true, false);
    }

    uint8_t LINE_WIDTH = !DATE_SHOW_Y > 0 ? 2 : 3;
    uint8_t LINE_SPACING = 1;
    uint8_t LINE_START = !DATE_SHOW_Y > 0 ? 10 : 2;
    int dayOffset = 0; // 周日偏移量

    for (int i = 0; i <= 6; i++)
    {
        int lineStart = LINE_START + i * (LINE_WIDTH + LINE_SPACING);
        int lineEnd = lineStart + LINE_WIDTH - 1;
        if (i == (timeInfo->tm_wday + 6 + dayOffset) % 7)
            color = HEXtoColor(WDC_ACTIVE.c_str());
        else
            color = HEXtoColor(WDC_INACTIVE.c_str());

        matrix->drawLine(lineStart + x + wdPosX, 1 + y, lineEnd + x + wdPosX, 1 + y, color);
    }
}

void TempApp(FastLED_NeoMatrix *matrix, int16_t x, int16_t y)
{
    DisplayManager.setTextColor(HEXtoColor(TEXTCOLOR.c_str()));
    DisplayManager.drawBMP(x, y - 6, icon_432, 8, 8);
    // Animation _icon = {icon_temps, sizeof(icon_temps) / sizeof(icon_temps[0])};
    // DisplayManager.drawGif(x, y - 6, _icon);

    String text = String(data.temp) + "°C";
    uint16_t textWidth = getTextWidth(text.c_str(), true);
    int16_t textX = ((23 - textWidth) / 2);

    DisplayManager.printText(textX + 11, y, utf8ascii(text).c_str(), false, false);
}

void HumApp(FastLED_NeoMatrix *matrix, int16_t x, int16_t y)
{
    DisplayManager.setTextColor(HEXtoColor(TEXTCOLOR.c_str()));
    DisplayManager.drawBMP(x, y - 6, icon_693, 8, 8);

    String text = data.humidity + "%";
    uint16_t textWidth = getTextWidth(text.c_str(), true);
    int16_t textX = ((23 - textWidth) / 2);

    DisplayManager.printText(textX + 9, y, utf8ascii(text).c_str(), false, false);
}

void WindApp(FastLED_NeoMatrix *matrix, int16_t x, int16_t y)
{
    DisplayManager.setTextColor(HEXtoColor(TEXTCOLOR.c_str()));
    Animation _icon = {icon_feng, sizeof(icon_feng) / sizeof(icon_feng[0])};
    DisplayManager.drawGif(x, y - 6, _icon);

    String text = "lv" + data.windScale;
    uint16_t textWidth = getTextWidth(text.c_str(), true);
    int16_t textX = ((23 - textWidth) / 2);

    DisplayManager.printText(textX + 10, y, utf8ascii(text).c_str(), false, true);
}

void StartWeatherUpdater()
{
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;
        data = hf.getWeatherData();
    }
}

#endif // APPS_H