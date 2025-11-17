// LovyanGFX Migration:   The migration from TFT_eSPI to LovyanGFX was performed
//   by NoRi-230401 and AndroidCrypto.
// The source code is available on GitHub: https://github.com/NoRi-230401/Lovy_eWidget

#include <LovyanGFX.hpp>
#include "LovyanGFX_ILI9341_XPT2046_Config.hpp"

LGFX display;
static uint16_t calibrateData[8];

bool touchCal_do()
{
  display.setTextSize((std::max(display.width(), display.height()) + 255) >> 8);

  if (display.touch() && true)
  {
    if (display.width() < display.height())
      display.setRotation(display.getRotation() ^ 1);

    display.setTextDatum(textdatum_t::middle_center);
    display.drawString("touch the arrow marker.", display.width() >> 1, display.height() >> 1);
    display.setTextDatum(textdatum_t::top_left);

    std::uint16_t fg = TFT_WHITE;
    std::uint16_t bg = TFT_BLACK;
    if (display.isEPD())
      std::swap(fg, bg);

    display.calibrateTouch(calibrateData, fg, bg, std::max(display.width(), display.height()) >> 3);
    Serial.printf("[0] x_min = %d\n", calibrateData[0]);
    Serial.printf("[1] y_min = %d\n", calibrateData[1]);
    Serial.printf("[2] x_min = %d\n", calibrateData[2]);
    Serial.printf("[3] y_max = %d\n", calibrateData[3]);
    Serial.printf("[4] x_max = %d\n", calibrateData[4]);
    Serial.printf("[5] y_min = %d\n", calibrateData[5]);
    Serial.printf("[6] x_max = %d\n", calibrateData[6]);
    Serial.printf("[7] y_max = %d\n", calibrateData[7]);
    Serial.printf("x_min = %d\n", (calibrateData[0] + calibrateData[2]) / 2);
    Serial.printf("x_max = %d\n", (calibrateData[4] + calibrateData[6]) / 2);
    Serial.printf("y_min = %d\n", (calibrateData[1] + calibrateData[5]) / 2);
    Serial.printf("y_max = %d\n", (calibrateData[3] + calibrateData[3]) / 2);
    return true;
  }
  return false;
}

void setup(void)
{
  Serial.begin(115200);
  display.init();

  if(touchCal_do())
    display.setTouchCalibrate(calibrateData);  // calibrateData enable 

  display.fillScreen(TFT_BLACK);
}

uint32_t count = ~0;
void loop(void)
{
  display.startWrite();
  display.setRotation(++count & 7);
  display.setColorDepth((count & 8) ? 16 : 24);

  display.setTextColor(TFT_WHITE);
  display.drawNumber(display.getRotation(), 16, 0);

  display.setTextColor(0xFF0000U);
  display.drawString("R", 30, 16);
  display.setTextColor(0x00FF00U);
  display.drawString("G", 40, 16);
  display.setTextColor(0x0000FFU);
  display.drawString("B", 50, 16);

  display.drawRect(30, 30, display.width() - 60, display.height() - 60, count * 7);
  display.drawFastHLine(0, 0, 10);

  display.endWrite();

  int32_t x, y;
  if (display.getTouch(&x, &y))
  {
    lgfx::touch_point_t tp;
    display.getTouchRaw(&tp);
    Serial.printf("raw_x = %d, raw_y = %d\n", tp.x, tp.y);

    display.fillRect(x - 2, y - 2, 5, 5, count * 7);
  }
}

