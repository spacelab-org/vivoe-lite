#ifndef GVA_H
#define GVA_H
#include "logGva.hpp"
#include "debug.hpp"
#include "gvaVideoRtpYuv.hpp"

#define MAJOR 0
#define MINOR 1
#define PATCH 180

#define MIN_HEIGHT 480
#define MIN_WIDTH 640

enum gvaFunctionEnum 
{
  SA = 0,
  WPN,
  DEF,
  SYS,
  DRV,
  STR,
  COM,
  BMS,
  ALARMSX,
};

enum gvaFunctionGroupEnum 
{
  TOP,
  BOTTOM,
  LEFT,
  RIGHT,
  ALARM_TABLE,
  KEYBOARD
};

enum gvaKeyEnum 
{
  /* These are physical GVA keys around the display */
  KEY_SA = 1,
  KEY_WPN,
  KEY_DEF,
  KEY_SYS,
  KEY_DRV,
  KEY_STR,
  KEY_COM,
  KEY_BMS,
  KEY_F1,
  KEY_F2,
  KEY_F3,
  KEY_F4,
  KEY_F5,
  KEY_F6,
  KEY_F7,
  KEY_F8,
  KEY_F9,
  KEY_F10,
  KEY_F11,
  KEY_F12,
  KEY_F13,
  KEY_F14,
  KEY_F15,
  KEY_F16,
  KEY_F17,
  KEY_F18,
  KEY_F19,
  KEY_F20,
  KEY_F21,
  KEY_F22,
  KEY_BLACKOUT,
  KEY_POWER,
  KEY_BRIGHTNESS_UP,
  KEY_BRIGHTNESS_DOWN,
  /* These are fake keys that only exist in the software (emulated world) */
  KEY_ESC,
  KEY_FULLSCREEN,
  KEY_PLUS,
  KEY_MINUS,
  KEY_GREATER,
  KEY_LESS,
  KEY_KEYBOARD
};

enum gvaStatusTypes {
  GVA_SUCCESS = 0,
  GVA_ERROR,
  GVA_NETWORK_ERROR,
  GVA_DDS_ERROR,
  GVA_XML_ERROR,
  GVA_RTP_ERROR
};

#endif
