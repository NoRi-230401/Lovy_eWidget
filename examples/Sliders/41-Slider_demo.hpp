// LovyanGFX Migration:   The migration from TFT_eSPI to LovyanGFX was performed 
//   by NoRi-230401 and AndroidCrypto.
// The source code is available on GitHub: https://github.com/NoRi-230401/Lovy_eWidget


// Slider widget demo, requires display with touch screen

// Requires widget library here:
// https://github.com/Bodmer/TFT_eWidget

#include "FS.h"
#include "Free_Fonts.h" // Include the header file attached to this sketch

// #define LGFX_AUTODETECT
#include <LovyanGFX.hpp>
#include "LovyanGFX_ILI9341_XPT2046_Config.hpp"
static LGFX lcd;
static LGFX_Sprite sprite(&lcd);

#include <Lovy_eWidget.h>
SliderWidget s1H = SliderWidget(&sprite); // Slider1H widget
SliderWidget s2V = SliderWidget(&sprite); // Slider2V widget

void setup()
{
  Serial.begin(115200);
  lcd.init();
  lcd.setRotation(0);
  sprite.createSprite(lcd.width(), lcd.height());
  sprite.fillScreen(TFT_BLACK);
  sprite.setFont(FF18);

  // Create a parameter set for the slider
  slider_t param;

  // Slider slot parameters
  param.slotWidth = 9;           // Note: ends of slot will be rounded and anti-aliased
  param.slotLength = 200;        // Length includes rounded ends
  param.slotColor = TFT_YELLOW;  // Slot colour
  param.slotBgColor = TFT_BLACK; // Slot background colour for anti-aliasing
  param.orientation = H_SLIDER;  // sets it "true" for horizontal

  // Slider control knob parameters (smooth rounded rectangle)
  param.knobWidth = 15;          // Always along x axis
  param.knobHeight = 25;         // Always along y axis
  param.knobRadius = 5;          // Corner radius
  param.knobColor = TFT_WHITE;   // Anti-aliased with slot backgound colour
  param.knobLineColor = TFT_RED; // Colour of marker line (set to same as knobColor for no line)

  // Slider range and movement speed
  param.sliderLT = 0;       // Left side for horizontal, top for vertical slider
  param.sliderRB = 100;     // Right side for horizontal, bottom for vertical slider
  param.startPosition = 50; // Start position for control knob
  param.sliderDelay = 0;    // Microseconds per pixel movement delay (0 = no delay)

  // Create slider using parameters and plot at 0,0
  s1H.drawSlider(0, 0, param);

  // Show bounding box (1 pixel outside slider working area)
  int16_t x, y;                              // x and y can be negative
  uint16_t w, h;                             // Width and height
  s1H.getBoundingRect(&x, &y, &w, &h);        // Update x,y,w,h with bounding box
  sprite.drawRect(x, y, w, h, TFT_DARKGREY); // Draw rectangle outline

  /*
  // Alternative discrete fns to create/modify same slider - but fn sequence is important...
  s1H.createSlider(9, 200, TFT_BLUE, TFT_BLACK, H_SLIDER);
  s1H.createKnob(15, 25, 5, TFT_WHITE, TFT_RED);
  s1H.setSliderScale(0, 100);
  s1H.drawSlider(0, 0);
*/
  sprite.pushSprite(0, 0);
  delay(1000);
  s1H.setSliderPosition(100);
  sprite.pushSprite(0, 0);
  delay(1000);
  s1H.setSliderPosition(50);
  sprite.pushSprite(0, 0);

  // Update any parameters that are different for slider 2
  param.slotWidth = 4;
  param.orientation = V_SLIDER; // sets it "false" for vertical
  param.slotColor = TFT_BLUE;   // Slot colour

  param.knobWidth = 19;
  param.knobHeight = 19;
  param.knobRadius = 19 / 2; // Half w and h so creates a circle

  param.sliderLT = 0;       // Top for vertical slider
  param.sliderRB = 100;     // Bottom for vertical slider
  param.sliderDelay = 2000; // 2ms per pixel movement delay (movement is blocking until complete)

  s2V.drawSlider(0, 50, param);
  s2V.getBoundingRect(&x, &y, &w, &h);
  sprite.drawRect(x, y, w, h, TFT_DARKGREY);

  /*
  // Alternative discrete fns to create/modify same slider - but fn sequence is important...
  s2V.createSlider(4, 200, TFT_BLUE, TFT_BLACK, V_SLIDER);
  s2V.createKnob(19, 19, 9, TFT_WHITE, TFT_RED);
  s2V.setSliderScale(200, 0, 2000);
  s2V.drawSlider(0, 50);
*/
  // Move slider under software control
  sprite.pushSprite(0, 0);
  delay(1000);
  s2V.setSliderPosition(100);
  sprite.pushSprite(0, 0);
  delay(1000);
  s2V.setSliderPosition(50);
  sprite.pushSprite(0, 0);
}

void loop()
{
  static uint32_t scanTime = millis();
  uint16_t t_x = 9999, t_y = 9999; // To store the touch coordinates

  // Scan for touch every 50ms
  if (millis() - scanTime >= 20)
  {
    // Pressed will be set true if there is a valid touch on the screen
    if (lcd.getTouch(&t_x, &t_y)) // TFT_eSPI's getTouch had a 3rd parameter for pressure threshold.
    {
      if (s1H.checkTouch(t_x, t_y))
      {
        Serial.print("Slider1H = ");
        Serial.println(s1H.getSliderPosition());
      }
      if (s2V.checkTouch(t_x, t_y))
      {
        Serial.print("Slider2V = ");
        Serial.println(s2V.getSliderPosition());
      }
      sprite.pushSprite(0, 0);
    }
    scanTime = millis();
  }
}
