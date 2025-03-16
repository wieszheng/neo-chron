#include "ButtonManager.h"
#include "DisplayManager.h"
#include <Ticker.h>
#include "Song.h"

#define BTN_UP D3
#define BTN_MID D5
#define BTN_DOWN D6
#define BUZZER_PIN D7

OneButton btnMid(BTN_MID, true);
OneButton btnUp(BTN_UP, true);
OneButton btnDown(BTN_DOWN, true);

enum State
{
    NORMAL,
    MAIN_MENU,
    ALARM_SET_TIME,
    VOLUME_SET
};
volatile State currentState = NORMAL;

volatile int mainMenuSelection = 0;
volatile bool timeFieldSelected = 0; // 0:小时 1:分钟
volatile int alarmHours = 4;
volatile int alarmMinutes = 0;
volatile int volumeLevel = 50;

bool alarmTriggered = false;
unsigned long alarmTriggerTime = 0;
unsigned long alarmTriggerDuration = 0;

Ticker alarm_ticker, buzzer_ticker;

unsigned long lastInputTime = 0;
const long TIMEOUT = 10000;

void playTone()
{
    tone(BUZZER_PIN, 587);
    delay(250);
    tone(BUZZER_PIN, 523);
    delay(250);
    noTone(BUZZER_PIN);
}

void checkAlarm()
{
    time_t now = time(nullptr);
    struct tm *timeInfo = localtime(&now);
    if (timeInfo->tm_hour == alarmHours && timeInfo->tm_min == alarmMinutes && timeInfo->tm_sec == 0)
    {
        Serial.println("Alarm triggered");
        alarmTriggered = true;
        alarmTriggerTime = millis();
        alarmTriggerDuration = 10000 * 3;
        buzzer_ticker.attach(1, playTone);
    }
}

void up_button_pressed()
{
    Serial.println("Left button pressed");
    lastInputTime = millis();
    if (currentState == ALARM_SET_TIME)
    {
        timeFieldSelected ? alarmMinutes++ : alarmHours++;
        alarmHours = (alarmHours + 24) % 24;
        alarmMinutes = (alarmMinutes + 60) % 60;
    }
    else if (currentState == MAIN_MENU)
    {
        mainMenuSelection = (mainMenuSelection + 1) % 2;
    }
    else if (currentState == VOLUME_SET)
    {
        volumeLevel = min(100, volumeLevel + 5);
    }
}

void mid_button_pressed()
{
    Serial.println("middle button pressed");
    lastInputTime = millis();
    switch (currentState)
    {
    case NORMAL:
        currentState = MAIN_MENU;
        mainMenuSelection = 0;
        break;
    case MAIN_MENU:
        if (mainMenuSelection == 0)
            currentState = ALARM_SET_TIME;
        else
            currentState = VOLUME_SET;
        break;
    case ALARM_SET_TIME:
        timeFieldSelected = !timeFieldSelected; // 切换小时/分钟选择
        break;
    case VOLUME_SET:
        currentState = MAIN_MENU;
        break;
    }
}

void mid_button_long_pressed()
{
    if (currentState == ALARM_SET_TIME)
    {
        currentState = MAIN_MENU;
        ALARM_H = alarmHours;
        ALARM_M = alarmMinutes;
        saveConfig();
        // 保存闹钟时间
    }
    else if (currentState == MAIN_MENU)
    {
        currentState = NORMAL;
    }
}

void down_button_pressed()
{
    Serial.println("Right button pressed");
    lastInputTime = millis();
    if (currentState == ALARM_SET_TIME)
    {
        timeFieldSelected ? alarmMinutes-- : alarmHours--;
        alarmHours = (alarmHours + 24) % 24;
        alarmMinutes = (alarmMinutes + 60) % 60;
    }
    else if (currentState == MAIN_MENU)
    {
        mainMenuSelection = (mainMenuSelection - 1 + 2) % 2;
    }
    else if (currentState == VOLUME_SET)
    {
        volumeLevel = max(0, volumeLevel - 5);
    }
}

ButtonManager_ &ButtonManager_::getInstance()
{
    static ButtonManager_ instance;
    return instance;
}

ButtonManager_ &ButtonManager = ButtonManager.getInstance();

void ButtonManager_::setup()
{
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
    btnUp.attachClick(up_button_pressed);
    btnMid.attachClick(mid_button_pressed);
    btnDown.attachClick(down_button_pressed);
    btnMid.attachLongPressStart(mid_button_long_pressed);

    alarm_ticker.attach(1, checkAlarm);
}
void ButtonManager_::tick()
{

    btnMid.tick();
    btnUp.tick();
    btnDown.tick();
    
    if (millis() - lastInputTime > TIMEOUT && currentState != NORMAL)
    {
        currentState = NORMAL;
    }
    switch (currentState)
    {
    case NORMAL:
        DisplayManager.deactivateSettingsMenu();
        break;

    case MAIN_MENU:
        DisplayManager.activateSettingsMenu();
        DisplayManager.showOption(mainMenuSelection);
        break;

    case ALARM_SET_TIME:
        DisplayManager.drawTimeSetting(alarmHours, alarmMinutes, timeFieldSelected);
        break;

    case VOLUME_SET:
        // drawVolume(); // 音量显示
        Serial.println("Volume set mode");
        break;
    }

    if (alarmTriggered && millis() - alarmTriggerTime >= alarmTriggerDuration)
    {
        alarmTriggered = false;
        buzzer_ticker.detach();
    }
}