#include <FastLED.h>
#include <SD.h>

class MatrixFile
{
public:
  struct MatrixFrame
  {
    int id = -1;
    int duration = 0;
    CRGB *pixels = new CRGB[256];
  };
  
  File file;
  MatrixFrame *matrixFrames;
  int frames;  
  int initialized;

  MatrixFile() {
      initialized = 0;
    }

  void read() {
    if(initialized == 0) {
      initialized = 1;
      readLedValues(file);
    }
  }
  
private:
  int toInt(String string)
  {
    int length = string.length();
    int num = 0;
    for (int i = 0; i < length; i++)
    {
      int digit = int(string[i]);
      if (digit >= 48)
      {
        num = num * 10 + (digit - 48);
      }
    }

    return num;
  }

  String readValue(File file)
  {
    unsigned int rawValue = file.read();
    char character = char(rawValue);
    String value = "";

    while (character != ';' && character != ',' && rawValue != 10)
    {
      value += character;
      rawValue = file.read();
      character = char(rawValue);
    }

    return value;
  }

  void readLedValues(File file)
  {
    if(!file.available()) {
      return;
    }
    
    frames = toInt(readValue(file));
    Serial.println(String(file.name()) + " has " + String(frames) + " frames");
    matrixFrames = new MatrixFrame[frames];

    struct MatrixFrame frame;
    int currentPixel = 0;
    String red = "";
    String green = "";
    String blue = "";
    while (file.available())
    {
      String value = readValue(file);
      if (frame.id == -1)
      {
        frame.id = toInt(value);
      }
      else if (frame.duration == 0)
      {
        frame.duration = toInt(value);
      }
      else
      {
        if (red == "")
        {
          red = value;
        }
        else if (green == "")
        {
          green = value;
        }
        else if (blue == "")
        {
          blue = value;
        }

        if (red != "" && green != "" && blue != "")
        {
          frame.pixels[currentPixel] = CRGB(toInt(red), toInt(green), toInt(blue));

          red = "";
          green = "";
          blue = "";

          if (currentPixel == 255)
          {
            matrixFrames[frame.id] = frame;
            frame = MatrixFrame();
            currentPixel = 0;
          }
          else
          {
            currentPixel++;
          }
        }
      }
    }

   // file.close();
  }
};
