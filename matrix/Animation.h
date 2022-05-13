/*
   The Effect abstract class for the GauntletII project.
*/

#ifndef Animation_h
#define Animation_h

#include <FastLED.h>

class Animation
{
protected:
  uint8_t width = 16;
  uint8_t height = 16;
  uint8_t centerX = width / 2 - 1;
  uint8_t centerY = height / 2 - 1;

  int amount = width * height;
  CRGB *leds;

  struct CRGB &pixel(int x, int y);
  struct CRGB &pixels(CRGB *pixels, int x, int y);
  bool inXRange(int x);
  bool inYRange(int y);

  void clearLeds();

public:
  Animation(CRGB *leds);

  virtual void start(){};
};

#endif
