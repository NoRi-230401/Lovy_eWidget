// --------------------------------------------------------
// "LovyanGFX_ILI9341_XPT2046_Config.hpp"
// --------------------------------------------------------
// LovyanGFX setup : by NoRi 2025-10-25 
//  esp32-s3-devkitc-1-n16r8v devkitc with Expansion Board
//   + 2.8inch LCD display (ILI9341) .. SPI bus
//   + touchScreen (XPT2046) .. SPI bus
// --------------------------------------------------------
#pragma once
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device
{
  lgfx::Panel_ILI9341 _panel_instance;
  lgfx::Bus_SPI _bus_instance;
  lgfx::Touch_XPT2046 _touch_instance;
  
public:
  LGFX(void)
  {
    {
      auto cfg = _bus_instance.config();
      
      // SPIバスの設定
      cfg.spi_host = SPI3_HOST;
      cfg.spi_mode = 0;
      cfg.freq_write = 40000000;
      cfg.freq_read  = 16000000;
      cfg.spi_3wire = true;
      cfg.use_lock   = true;
      cfg.dma_channel = SPI_DMA_CH_AUTO;
      cfg.pin_sclk = 3;
      cfg.pin_mosi = 45;
      cfg.pin_miso = 46;
      cfg.pin_dc = 47;

      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }
    
    {
      auto cfg = _panel_instance.config();
      
      cfg.pin_cs = 14;
      cfg.pin_rst = 21;
      cfg.pin_busy = -1;

      cfg.panel_width = 240;
      cfg.panel_height = 320;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      cfg.offset_rotation = 0;
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits = 1;
      cfg.readable = true;
      cfg.invert = false;
      cfg.rgb_order = false;
      cfg.dlen_16bit = false;
      cfg.bus_shared = false;
      
      _panel_instance.config(cfg);
    }
        
    {
        auto cfg = _touch_instance.config();

        cfg.x_min      =  356;
        cfg.x_max      = 3823;
        cfg.y_min      = 3816;
        cfg.y_max      =  225;
        cfg.pin_int    = -1;
        cfg.bus_shared = false;
        cfg.offset_rotation = 0;

        cfg.spi_host = SPI2_HOST;
        cfg.freq = 1000000;
        cfg.pin_sclk = 42;
        cfg.pin_mosi = 2;
        cfg.pin_miso = 41;
        cfg.pin_cs   = 1;

        _touch_instance.config(cfg);
        _panel_instance.setTouch(&_touch_instance);
      }
        
    setPanel(&_panel_instance);
  }
};

