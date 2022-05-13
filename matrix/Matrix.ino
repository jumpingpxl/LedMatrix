#include <FastLED.h>
#include <SD.h>

#include "Rainbow.cpp"
#include "Snake.cpp"
#include "Noise.cpp"
#include "Matrix.cpp"
//#include "FileAnimation.cpp"

#define WIDTH 16
#define HEIGHT 16
#define NUM_LEDS WIDTH *HEIGHT

#define DATA_PIN 3
#define SD_PIN BUILTIN_SDCARD

CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);

  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_PIN))
  {
    Serial.println("SD Card initialization failed!");
    return;
  }

  Serial.println("SD CARD initialization done.");
  Matrix matrix(leds);
  matrix.start();
}

void loop()
{

  //Rainbow rainbow(leds);
  //rainbow.start();

  // Noise noise(leds);
  // noise.start();

  // Snake snake(leds);
  // snake.start();
}
