#include "Animation.h"
#include "MatrixFile.cpp"
#include <SD.h>

class Matrix : public Animation
{
protected:
  MatrixFile *files;
  int gifs;
  int runsPerGif = 5;
  
public:
  Matrix(CRGB *leds) : Animation(leds)
  {
    Serial.println("init...");
    getMatrixFiles();
    Serial.println("init completed");
  }

  void start()
  {
    clearLeds();
    
    for(int ii = 0; ii < 1000; ii++) {
    for(int g = 0; g < gifs; g++) {
      MatrixFile file = files[g];
      Serial.println("start start lol " + String(file.file.name()));
      file.read();
    
      Serial.println("start " + String(file.file.name()));
      for(int r = 0; r < runsPerGif; r++) {
        Serial.println("start run " + String(r) + " of Matrix " + String(file.file.name()));
        for (int f = 0; f < file.frames ; f++) {
          MatrixFile::MatrixFrame frame = file.matrixFrames[f];
          Serial.println("Start Frame " + String(frame.id) + " (" + frame.duration + "ms) of Matrix " + String(file.file.name()));
          
          for(int posY = 0; posY < height; posY++) {
            boolean revert = posY % 2 == 0;
            for(int posX = 0; posX < width; posX++) {
              pixel(posX, posY) = pixels(frame.pixels, (revert ? width - 1 - posX : posX), posY);
            }
          }
        
          FastLED.show();
          delay(frame.duration);
        }
      }
    }
    }
  }

private:
  void getMatrixFiles()
  {
    files = new MatrixFile[500];
    
    File rootDir = SD.open("/");
    int i = 0;
    while (true)
    {
      File entry = rootDir.openNextFile();
      if (!entry)
      {
        Serial.println("end");
        break;
      }

      if (entry.isDirectory())
      {
        entry = rootDir.openNextFile();
      }

      String name = entry.name();
      int length = strlen(entry.name());
      if (length > 7)
      {
        if (name.endsWith(".matrix"))
        {
          Serial.println(name + " is a Matrix File");
          MatrixFile file;
          file.file = entry;
          files[i] = file;
          i++;
        }
      }
    }


   for(int i = 0; i < sizeof files; i++) {
    MatrixFile matrixFile = files[i];
    if(!matrixFile.file) {
      gifs = i;
      break;
    }
   }

   Serial.println("There are " + String(gifs) + " Matrix files.");
  }
};
