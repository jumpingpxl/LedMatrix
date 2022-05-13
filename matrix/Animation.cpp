#include "Animation.h"

Animation::Animation(CRGB *leds) : leds(leds) {}

bool Animation::inXRange(int x)
{
  return x >= 0 && x < width;
}

bool Animation::inYRange(int y)
{
  return y >= 0 && y < height;
}

struct CRGB &Animation::pixel(int x, int y)
{
  return pixels(leds, x, y);
}

struct CRGB &Animation::pixels(CRGB *pixels, int x, int y) {
  if (y & 1)
  {
    return pixels[(y * width) + width - x - 1];
  }
  else
  {
    return pixels[(y * width) + x];
  }
}

void Animation::clearLeds()
{
  memset8(leds, 0, width * height * 3);
}
