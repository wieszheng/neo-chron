#include "Apps.h"


void TimeApp(FastLED_NeoMatrix *matrix, int16_t x, int16_t y)
{
    time_t now = time(nullptr);
    struct tm *timeInfo;
    timeInfo = localtime(&now);

    uint8_t LINE_WIDTH = 1 > 0 ? 2 : 3;
    uint8_t LINE_SPACING = 1;
    uint8_t LINE_START = 1 > 0 ? 10 : 2;
    int dayOffset = 1;
  
    for (int i = 0; i <= 6; i++)
    {
      int lineStart = LINE_START + i * (LINE_WIDTH + LINE_SPACING);
      int lineEnd = lineStart + LINE_WIDTH - 1;
      uint32_t color;
      if (i == (timeInfo->tm_wday + 6 + dayOffset) % 7)
        color = WDC_ACTIVE;
      else
        color = WDC_INACTIVE;
  
      matrix->drawLine(lineStart + x, 1 + y, lineEnd + x, 1 + y, color);
    }
}