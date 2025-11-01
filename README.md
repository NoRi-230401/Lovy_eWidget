# Lovy_eWidget

`Lovy_eWidget` is a GUI widget library for the LovyanGFX library. It provides easy-to-use classes for buttons, sliders, meters, and graphs.

This library is a fork of Bodmer's original TFT_eWidget library, adapted to work seamlessly with LovyanGFX.

## Features

*   **ButtonWidget:** Create simple, pressable, and toggleable buttons with customizable actions.
*   **SliderWidget:** Implement horizontal or vertical sliders for value input.
*   **MeterWidget:** Display values on a classic analogue meter.
*   **GraphWidget & TraceWidget:** Plot data on a customizable graph with grid and scaling options.


## Basic Usage

Here are some basic examples of how to use each widget.

### Common Setup

All examples require the following basic setup for `LovyanGFX`.

```cpp
#include <LovyanGFX.hpp>
#include "LovyanGFX_ILI9341_XPT2046_Config.hpp" // Use your own LovyanGFX config
#include <Lovy_eWidget.h>

static LGFX lcd;
static LGFX_Sprite sprite(&lcd);

void setup() {
  lcd.init();
  sprite.createSprite(lcd.width(), lcd.height());
  sprite.fillScreen(TFT_BLACK);
  // ... widget initialization code here ...
  sprite.pushSprite(0, 0);
}

void loop() {
  // ... widget interaction code here ...
}
```

### ButtonWidget

```cpp
// In setup()
ButtonWidget myButton = ButtonWidget(&sprite);
myButton.initButtonUL(70, 95, 100, 50, TFT_WHITE, TFT_RED, TFT_WHITE, "Press", 1);
myButton.drawButton();

// In loop()
uint16_t t_x, t_y;
if (lcd.getTouch(&t_x, &t_y)) {
  if (myButton.contains(t_x, t_y)) {
    myButton.press(true);
  }
} else {
  myButton.press(false);
}

if (myButton.justPressed()) {
  myButton.drawButton(true); // Draw inverted
  sprite.pushSprite(0, 0);
}

if (myButton.justReleased()) {
  myButton.drawButton(false); // Draw normal
  sprite.pushSprite(0, 0);
}
```

### SliderWidget

```cpp
// In setup()
SliderWidget mySlider = SliderWidget(&sprite);
slider_t params;
params.orientation = H_SLIDER; // Horizontal
params.slotLength = 200;
params.sliderLT = 0;   // Min value
params.sliderRB = 100; // Max value
mySlider.drawSlider(20, 120, params);

// In loop()
uint16_t t_x, t_y;
if (lcd.getTouch(&t_x, &t_y)) {
  if (mySlider.checkTouch(t_x, t_y)) {
    // Slider value has changed
    int position = mySlider.getSliderPosition();
    Serial.printf("Slider position: %d\n", position);
    sprite.pushSprite(0, 0);
  }
}
```

### MeterWidget

```cpp
// In setup()
MeterWidget myMeter = MeterWidget(&sprite);
myMeter.analogMeter(0, 60, 10.0, "V", "0", "2.5", "5", "7.5", "10");

// In loop()
float voltage = analogRead(A0) * 10.0 / 4095.0; // Example value
myMeter.updateNeedle(voltage, 0);
sprite.pushSprite(0, 0);
delay(100);
```

### GraphWidget & TraceWidget

```cpp
// In setup()
GraphWidget myGraph = GraphWidget(&sprite);
TraceWidget myTrace = TraceWidget(&sprite, &myGraph);
myGraph.createGraph(200, 150, TFT_DARKGREY);
myGraph.setGraphScale(0, 100, -50, 50); // x-axis, y-axis scale
myGraph.drawGraph(20, 50);
myTrace.startTrace(TFT_GREEN);

// In loop()
static float x_val = 0;
if (x_val <= 100) {
  float y_val = 40 * sin(x_val * 0.1);
  myTrace.addPoint(x_val, y_val);
  x_val += 1.0;
  sprite.pushSprite(0, 0);
  delay(20);
}
```

*   **Original Author:** This library is based on the excellent work of Bodmer and his `TFT_eWidget` library.
*   **LovyanGFX Migration:** The migration from `TFT_eSPI` to `LovyanGFX` was performed by NoRi-230401 and AndroidCrypto.

## Repository
The source code is available on GitHub: 
https://github.com/NoRi-230401/Lovy_eWidget

Original TFT_eWidget library by Bodmer on GitHub: https://github.com/Bodmer/TFT_eWidget




Acknowledgements
----------------
Thanks to [Bodmer](https://github.com/Bodmer/), author of the [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) and ,[TFT_eWidget](https://github.com/Bodmer/TFT_eWidget) library.  

Thanks to [Lovyan03](https://github.com/lovyan03/) , author or the [LovyanGFX](https://github.com/adafruit/Adafruit-GFX-Library), which is special useful display library.

Thanks to [AndroidCrypto](https://github.com/AndroidCrypto/), first create `Lovy_eWidget` library on [ESP32 Tft_eSPI library to LovyanGFX library transition](https://github.com/AndroidCrypto/ESP32_Tft_eSPI_to_LovyanGFX_transition), for the inspiration to create this library for me.  


