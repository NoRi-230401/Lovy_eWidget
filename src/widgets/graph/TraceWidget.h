/***************************************************************************************

***************************************************************************************/
#ifndef _TraceWidgetH_
#define _TraceWidgetH_

// Standard support
#include <Arduino.h>
#include <LovyanGFX.hpp>
#include "GraphWidget.h"

class TraceWidget : public LGFX_Device
{

public:
  TraceWidget(LGFX_Sprite* tft, GraphWidget *gw);
  [[deprecated("Use TraceWidget(LGFX_Sprite*, GraphWidget*) instead")]] TraceWidget(GraphWidget *gw);
  void startTrace(uint16_t ptColor);
  bool addPoint(float xval, float yval);

  uint16_t getLastPointX(void);
  uint16_t getLastPointY(void);

private:
  // Map a float to a new range
  float mapFloat(float ip, float ipmin, float ipmax, float tomin, float tomax)
  {
    return tomin + (((tomax - tomin) * (ip - ipmin)) / (ipmax - ipmin));
  }

  uint16_t regionCode(float x, float y);
  bool clipTrace(float *xs, float *ys, float *xe, float *ye);

  // trace
  bool _newTrace = true;
  uint16_t _ptColor = TFT_WHITE;
  uint16_t _xpt = 0;
  uint16_t _ypt = 0;
  float _xval = 0;
  float _yval = 0;

  LGFX_Sprite *_tft;
  GraphWidget *_gw;
};


#endif