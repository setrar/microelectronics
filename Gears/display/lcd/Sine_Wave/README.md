
```ino
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();                   // Invoke custom library with default width and height

#define TFT_GREY 0x7BEF

uint32_t runTime = 0;

void setup()
{
  randomSeed(analogRead(0));
  Serial.begin(38400);
// Setup the LCD
  tft.init();
  tft.setRotation(1);
}


void loop() {
  int buf[478];
  int x, x2;
  int y, y2;
  int r;

  runTime = millis();
// Clear the screen and draw the frame
  tft.fillScreen(TFT_BLACK);

    tft.fillRect(1,15,478-1,304-15,TFT_BLACK);
  tft.drawLine(239, 15, 239, 304,TFT_BLUE);
  tft.drawLine(1, 159, 478, 159,TFT_BLUE);

// Draw a moving sinewave
int col = 0;
  x=1;
  for (int i=1; i<(477*15); i++) 
  {
    x++;
    if (x==478)
      x=1;
    if (i>478)
    {
      if ((x==239)||(buf[x-1]==159))
        col = TFT_BLUE;
      else
        tft.drawPixel(x,buf[x-1],TFT_BLACK);
    }
    y=159+(sin(((i*0.7)*3.14)/180)*(90-(i / 100)));
    tft.drawPixel(x,y, TFT_BLUE);
    buf[x-1]=y;
  }


}
```

<img src=images/SineWave.png width=50% height=50% > </img>
