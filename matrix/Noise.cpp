#include "Animation.h"

class Noise : public Animation
{
private:
  uint8_t layer;
  uint16_t noiseData;
  uint32_t offsetX;
  uint32_t offsetY;

  uint32_t x[1];
  uint32_t y[1];
  uint32_t z[1];
  uint32_t scale_x[1];
  uint32_t scale_y[1];
  uint8_t noise[1][16][16];

  void adjustGamma()
  {
    for (uint16_t i = 0; i < amount; i++)
    {
      leds[i].r = dim8_video(leds[i].r);
      leds[i].g = dim8_video(leds[i].g);
      leds[i].b = dim8_video(leds[i].b);
    }
  }

public:
  Noise(CRGB *leds) : Animation(leds)
  {
    FastLED.setBrightness(128);
  }

  void start()
  {
    CRGBPalette16 Pal(0, 3, 3, 3, 64, 13, 13, 255, 128, 3, 3, 3, 192, 255, 130, 3);

    while (true)
    {
      x[0] = x[0] + (2 * noise[0][0][0]) - 255;
      y[0] = y[0] + (2 * noise[0][width - 1][0]) - 255;
      z[0] += 1 + ((noise[0][0][height - 1]) / 4);
      scale_x[0] = 8000 + (noise[0][0][centerY] * 16);
      scale_y[0] = 8000 + (noise[0][width - 1][centerY] * 16);

      layer = 0;
      for (uint8_t posX = 0; posX < width; posX++)
      {
        offsetX = scale_x[layer] * (posX - centerX);
        for (uint8_t posY = 0; posY < height; posY++)
        {
          offsetY = scale_y[layer] * (posY - centerY);
          noiseData = inoise16(x[layer] + offsetX, y[layer] + offsetY, z[layer]);
          noiseData -= 11000;
          if (noiseData < 0)
          {
            noiseData = 0;
          }
          else if (noiseData > 40000)
          {
            noiseData = 40000;
          }

          noiseData /= 161;
          noise[layer][posX][posY] = noiseData;

          CRGB noiseOverlay = CHSV(noise[layer][posY][posX], 255, noise[layer][posX][posY]);
          pixel(posX, posY) = ColorFromPalette(Pal, noise[layer][width - 1][height - 1] + noise[layer][posX][posY]) + noiseOverlay;
        }
      }

      adjustGamma();
      FastLED.show();
      delay(3);
    }
  }
};
