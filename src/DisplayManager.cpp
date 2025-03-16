#include <DisplayManager.h>
#include "AwtrixFont.h"
#include "Apps.h"
#include "Tools.h"
#include "Icons.h"

#define MATRIX_WIDTH 32
#define MATRIX_HEIGHT 8
#define MATRIX_PIN D2

CRGB leds[MATRIX_WIDTH * MATRIX_HEIGHT];
FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(leds, 8, 8, 4, 1, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE);

int colorLoop = 0;
int color_index = 2;
struct ColorRGB
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
};
ColorRGB RGBColorPalette[][2] = {
    {{255, 255, 0}, {255, 0, 77}},
    {{0, 255, 0}, {148, 0, 211}},
    {{0, 255, 255}, {255, 0, 255}},
};

typedef void (*AppCallback)(FastLED_NeoMatrix *matrix, int16_t x, int16_t y);
AppCallback *AppFunctions;
std::vector<std::pair<uint16_t, AppCallback>> Apps;

uint8_t AppCount = 0;
uint8_t currentFrame = 0;
int currentAnimationFrame = 0;
unsigned long lastAnimationFrameTime = 0;
const unsigned long switchInterval = 10000;
unsigned long lastSwitchTime = 0;
int slideOffset = 0;
const int slideSpeed = 1;

DisplayManager_ &DisplayManager_::getInstance()
{
  static DisplayManager_ instance;
  return instance;
}

DisplayManager_ &DisplayManager = DisplayManager.getInstance();

void DisplayManager_::setup()
{
  FastLED.addLeds<NEOPIXEL, MATRIX_PIN>(leds, MATRIX_WIDTH * MATRIX_HEIGHT);
  switch (MATRIX_LAYOUT)
  {
  case 1:
    matrix = new FastLED_NeoMatrix(leds, 32, 8, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG);
    break;
  case 2:
    matrix = new FastLED_NeoMatrix(leds, 32, 8, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG);
    break;
  case 3:
    matrix = new FastLED_NeoMatrix(leds, 32, 8, NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE);
    break;
  case 4:
    matrix = new FastLED_NeoMatrix(leds, 8, 8, 4, 1, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG);
    break;
  case 5:
    matrix = new FastLED_NeoMatrix(leds, 8, 8, 4, 1, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE);
    break;
  }

  switch (MATRIX_TEMP_CORRECTION)
  {
  case 0:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setCorrection(TypicalLEDStrip);
    break;
  case 1:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setTemperature(Candle);
    break;
  case 2:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setTemperature(Tungsten40W);
    break;
  case 3:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setTemperature(Tungsten100W);
    break;
  case 4:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setTemperature(Halogen);
    break;
  case 5:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setTemperature(CarbonArc);
    break;
  case 6:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setTemperature(HighNoonSun);
    break;
  case 7:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setTemperature(DirectSunlight);
    break;
  case 8:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setTemperature(OvercastSky);
    break;
  case 9:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setTemperature(ClearBlueSky);
    break;
  case 10:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setTemperature(WarmFluorescent);
    break;
  case 11:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setTemperature(StandardFluorescent);
    break;
  case 12:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setTemperature(CoolWhiteFluorescent);
    break;
  case 13:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setTemperature(FullSpectrumFluorescent);
    break;
  case 14:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setTemperature(GrowLightFluorescent);
    break;
  case 15:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setTemperature(BlackLightFluorescent);
    break;
  case 16:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setTemperature(MercuryVapor);
    break;
  case 17:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setTemperature(SodiumVapor);
    break;
  case 18:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setTemperature(MetalHalide);
    break;
  case 19:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setTemperature(HighPressureSodium);
    break;
  case 20:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setTemperature(UncorrectedTemperature);
    break;
  default:
    FastLED.addLeds<NEOPIXEL, D2>(leds, 256).setCorrection(TypicalLEDStrip);
    break;
  }
  matrix->begin();
  matrix->setTextWrap(false);
  matrix->setBrightness(30);
  matrix->setFont(&AwtrixFont);
}

void DisplayManager_::setTextColor(uint16_t color)
{
  matrix->setTextColor(color);
}

void DisplayManager_::drawBMP(int16_t x, int16_t y, const uint16_t bitmap[], int16_t w, int16_t h)
{
  matrix->drawRGBBitmap(y, x, bitmap, w, h);
}

void DisplayManager_::gradationText(int16_t x, int16_t y, const char *text, bool clear)
{
  if (clear)
    matrix->clear();
  matrix->setCursor(x, y);

  for (int i = 0; text[i] != '\0'; i++)
  {
    ColorRGB start = RGBColorPalette[color_index][0];
    ColorRGB end = RGBColorPalette[color_index][1];
    int n = 0;
    if (colorLoop < 31)
    {
      if (x + y > colorLoop)
      {
        n = x + y - colorLoop;
      }
      else
      {
        n = colorLoop - x - y;
      }
    }
    else
    {
      if (x + y > (colorLoop - 30))
      {
        n = 30 - (x + y - colorLoop + 30);
      }
      else
      {
        n = 30 - (colorLoop - 30 - x - y);
      }
    }
    int r = (end.r - start.r) / 30 * n + start.r;
    int g = (end.g - start.g) / 30 * n + start.g;
    int b = (end.b - start.b) / 30 * n + start.b;

    matrix->setTextColor(matrix->Color(r, g, b));
    matrix->print(text[i]);
    x += 3;
  }

  if (clear)
    matrix->show();
}

void DisplayManager_::printText(int16_t x, int16_t y, const char *text, bool centered, bool ignoreUppercase)
{
  if (centered)
  {
    uint16_t textWidth = getTextWidth(text, ignoreUppercase);
    int16_t textX = ((32 - textWidth) / 2);
    matrix->setCursor(textX, y);
  }
  else
  {
    matrix->setCursor(x, y);
  }

  if (!ignoreUppercase)
  {
    size_t length = strlen(text);
    char upperText[length + 1];

    for (size_t i = 0; i < length; ++i)
    {
      upperText[i] = toupper(text[i]);
    }

    upperText[length] = '\0';
    matrix->print(upperText);
  }
  else
  {
    matrix->print(text);
  }
}

void DisplayManager_::show()
{
  matrix->show();
}

void DisplayManager_::clear()
{
  matrix->clear();
}

void DisplayManager_::setBrightness(uint8_t brightness)
{
  matrix->setBrightness(brightness);
}

void DisplayManager_::loadNativeApps()
{
  Apps.clear();
  if (true)
    Apps.push_back(std::make_pair(0, TimeApp));
  if (SHOW_DATE)
    Apps.push_back(std::make_pair(1, DateApp));
  // if (true)
  //   Apps.push_back(std::make_pair(2, WeatherApp));
  if (true)
    Apps.push_back(std::make_pair(3, TempApp));
  if (true)
    Apps.push_back(std::make_pair(4, HumApp));
  if (true)
    Apps.push_back(std::make_pair(5, WindApp));
  delete[] AppFunctions;
  AppCount = Apps.size();
  AppFunctions = new AppCallback[AppCount];

  for (size_t i = 0; i < AppCount; ++i)
  {
    AppFunctions[i] = Apps[i].second;
  }
}

void DisplayManager_::nightBrightness()
{
  time_t now = time(nullptr);
  struct tm *timeInfo = localtime(&now);
  int currentMinutes = timeInfo->tm_hour * 60 + timeInfo->tm_min;

  int nightStartMinutes = timeToMinutes(NIGHT_START);
  int nightEndMinutes = timeToMinutes(NIGHT_END);

  if ((nightStartMinutes <= nightEndMinutes && currentMinutes >= nightStartMinutes && currentMinutes < nightEndMinutes) || (nightStartMinutes > nightEndMinutes && (currentMinutes >= nightStartMinutes || currentMinutes < nightEndMinutes)))
  {
    matrix->setBrightness(MIN_BRIGHTNESS_NIGHT);
  }
  else
  {
    matrix->setBrightness(MIN_BRIGHTNESS);
  }
}

void DisplayManager_::tick()
{
  if (settingsMenuActive)
  {
    return;
  }
  StartWeatherUpdater();
  clear();
  int16_t y = 6;
  if (millis() - lastSwitchTime >= switchInterval)
  {
    currentFrame = (currentFrame + 1) % AppCount;
    lastSwitchTime = millis();
    slideOffset = -8;
    nightBrightness();
  }
  if (slideOffset != 0)
  {
    y += slideOffset; // 根据滑动方向调整 Y 坐标
    if (slideOffset < 0)
    {
      slideOffset += slideSpeed; // 向上滑动
      if (slideOffset >= 0)
        slideOffset = 0; // 停止滑动
    }
    else
    {
      slideOffset -= slideSpeed; // 向下滑动
      if (slideOffset <= 0)
        slideOffset = 0; // 停止滑动
    }
    delay(25);
  }

  int nextFrame = (currentFrame + 1) % AppCount;
  (AppFunctions[currentFrame])(matrix, 0, y);
  (AppFunctions[nextFrame])(matrix, 0, y + (slideOffset < 0 ? 8 : -8));

  show();
}

void DisplayManager_::drawWifi(int x, int y, int state)
{
  matrix->clear();
  switch (state)
  {
  case 0: // wifi连接 24, 0, 0
  {
    for (int i = 0; i < 4; i++)
    {
      matrix->setTextColor(matrix->Color(255, 255, 255));
      matrix->setCursor(7, 6);
      matrix->print("WiFi");
      switch (i)
      {
      case 3:
        matrix->drawPixel(x, y, matrix->Color(2, 2, 255));
        matrix->drawPixel(x + 1, y + 1, matrix->Color(2, 2, 255));
        matrix->drawPixel(x + 2, y + 2, matrix->Color(2, 2, 255));
        matrix->drawPixel(x + 3, y + 3, matrix->Color(2, 2, 255));
        matrix->drawPixel(x + 2, y + 4, matrix->Color(2, 2, 255));
        matrix->drawPixel(x + 1, y + 5, matrix->Color(2, 2, 255));
        matrix->drawPixel(x, y + 6, matrix->Color(2, 2, 255));
      case 2:
        matrix->drawPixel(x - 1, y + 2, matrix->Color(2, 2, 255));
        matrix->drawPixel(x, y + 3, matrix->Color(2, 2, 255));
        matrix->drawPixel(x - 1, y + 4, matrix->Color(2, 2, 255));
      case 1:
        matrix->drawPixel(x - 3, y + 3, matrix->Color(2, 2, 255));
      case 0:
        break;
      }
      delay(200);
      matrix->show();
    }
    break;
  }
  case 1: // 连接失败 8, 6, 1
  {
    matrix->setTextColor(matrix->Color(255, 0, 0));
    matrix->setCursor(7, 6);
    matrix->print("Fail!");
    delay(200);
    break;
  }
  case 2: // 连接配网中 26, 0, 2
  {
    for (int i = 0; i < 4; i++)
    {
      matrix->setTextColor(matrix->Color(255, 255, 255));
      matrix->setCursor(7, 6);
      matrix->print("Wait");
      switch (i)
      {
      case 3:
        matrix->drawPixel(x + 1, y + 5, matrix->Color(255, 0, 0));
      case 2:
        matrix->drawPixel(x - 1, y + 5, matrix->Color(255, 0, 0));
      case 1:
        matrix->drawPixel(x - 3, y + 5, matrix->Color(255, 0, 0));
      case 0:
        break;
      }
      delay(200);
      matrix->show();
    }
    break;
  }
  case 3: // 连接失败
  {
    float x = 4;
    while (x >= -85)
    {
      // HSVtext(
      //     x, 6, ("Matrix   " + ip.toString()).c_str(), true);
      // x -= 0.18;
    }
  }
  default:
    break;
  }

  matrix->show();
}

void DisplayManager_::showOption(int optionIndex)
{
  clear();
  setTextColor(HEXtoColor(TEXTCOLOR));
  printText(2, 6, "<", false, false);
  printText(27, 6, ">", false, false);
  switch (optionIndex)
  {
  case 0:
    drawBMP(0, 12, icon_lingdang, 8, 8);
    break;
  case 1:
    drawBMP(0, 12, icon_11, 8, 8);
    break;
  case 2:
    drawBMP(0, 11, icon_1158, 8, 8);
    break;
  }
  show();
}

void DisplayManager_::activateSettingsMenu()
{
  settingsMenuActive = true;
}

void DisplayManager_::deactivateSettingsMenu()
{
  settingsMenuActive = false;
}

void drawNumber(int num, int xOffset)
{
  int tens = num / 10;
  int ones = num % 10;
  matrix->setTextColor(HEXtoColor(TEXTCOLOR));
  matrix->setCursor(xOffset, 6);
  matrix->print(tens);
  matrix->setCursor(xOffset + 4, 6);
  matrix->print(ones);
}

void DisplayManager_::drawTimeSetting(int h, int m, bool selected)
{
  clear();
  drawBMP(0, 1, icon_lingdang2, 8, 8);
  drawNumber(h, 12);
  printText(20, 6, ":", false, false);
  drawNumber(m, 22);
  int x = selected ? 22 : 12;
  gradationText(x, 7, "__", false);
  show();
}

void DisplayManager_::drawGif(int16_t x, int16_t y, Animation animation)
{
  uint8_t FRAME_INTERVAL = 100;
  if (millis() - lastAnimationFrameTime >= FRAME_INTERVAL)
  {
    currentAnimationFrame = (currentAnimationFrame + 1) % animation.frameCount; // 循环帧
    lastAnimationFrameTime = millis();
  }
  matrix->drawRGBBitmap(x, y, animation.frames[currentAnimationFrame], 8, 8);
}