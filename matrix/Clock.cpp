#include "Animation.h"

class Rainbow : public Animation
{
protected:
  uint8_t hue = 0;

public:
  Rainbow(CRGB *leds) : Animation(leds)
  {
  }

  void start()
  {
    for (int j = 0; j < 255; j++)
    {
      for (int i = 0; i < amount; i++)
      {
        leds[i] = CHSV(i - j, 255, 255);
      }

      FastLED.show();
      delay(5);
    }
  }
};
