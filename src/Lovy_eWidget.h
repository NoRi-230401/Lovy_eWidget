/***************************************************************************************

  TFT display Widget library comprising following classes:
    1. ButtonWidget - button library
    2. SliderWidget - control sliders

***************************************************************************************/
#ifndef _Lovy_eWidgetH_
#define _Lovy_eWidgetH_

//Standard support
#include <Arduino.h>

// LittleFS is required for touch calibration in TFT_eSPI sketches
#if defined (ESP8266) || defined (ESP32)
  #include <pgmspace.h>
  #include <FS.h>
  #include <LittleFS.h>
#endif

#include <LovyanGFX.hpp>

#include "widgets/meter/Meter.h"

#endif