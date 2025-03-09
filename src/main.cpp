#include <Arduino.h>
#include "WebServer.h"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <FastLED_NeoMatrix.h>
#include <Fonts/TomThumb.h>

#include "Config.h"

ESP8266WebServer server(80);
WebServer mws(server);

IPAddress softLocal(192, 168, 4, 1);
IPAddress softGateway(192, 168, 4, 1);
IPAddress softSubnet(255, 255, 255, 0);

const int ledPin = LED_BUILTIN;
CRGB leds[256];
FastLED_NeoMatrix *matrix;

void setup()
{
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  if (LittleFS.begin())
  {
    if (DEBUG_MODE)
      DEBUG_PRINTLN(F("Filesystem mounted"));

    loadConfig();
  }
  else
  {
    if (DEBUG_MODE)
      DEBUG_PRINTLN(F("Error mounting filesystem"));
  }
  switch (MATRIX_LAYOUT)
  {
  case 0:
    matrix = new FastLED_NeoMatrix(leds, 32, 8, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG);
    break;
  case 1:
    matrix = new FastLED_NeoMatrix(leds, 8, 8, 4, 1, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE);
    break;
  case 2:
    matrix = new FastLED_NeoMatrix(leds, 32, 8, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG);
    break;
  default:
    matrix = new FastLED_NeoMatrix(leds, 32, 8, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG);
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
	matrix->setFont(&TomThumb);
  matrix->clear();

  matrix->fillScreen(matrix->Color(255, 0, 0));
	matrix->show();
  WiFi.hostname(HOSTNAME.c_str());
  WiFi.softAPConfig(softLocal, softGateway, softSubnet);
  mws.startWiFi(10000, HOSTNAME.c_str(), "12345678");
  mws.begin();
  if (!MDNS.begin(HOSTNAME))
  {
    if (DEBUG_MODE)
      DEBUG_PRINTLN(F("Error setting up MDNS responder!"));
  }
  else
  {
    MDNS.addService("http", "tcp", 80);
    MDNS.addServiceTxt("neo_chron", "tcp", "name", HOSTNAME.c_str());
  }
}

void loop()
{
  mws.run();
  MDNS.update();
}