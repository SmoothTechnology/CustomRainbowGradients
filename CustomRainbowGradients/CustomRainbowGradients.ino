#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define LED_PIN1  5
#define LED_PIN2  6

#define NUMPIXELS 112
#define NUMRAINBOWS 3

Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUMPIXELS, LED_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, LED_PIN2, NEO_GRB + NEO_KHZ800);


int LOWERCOLOR = 10;
int UPPERCOLOR = 95;
int shifter1 = 0;
int shifter2 = 1;
bool toggler = 0;
int toggletime = 200;

void setup() 
{
  pixels1.begin(); 
  pixels2.begin(); 
}

void loop() 
{
  LOWERCOLOR = map(analogRead(0), 0, 1023, 0, 255);
  UPPERCOLOR = map(analogRead(1), 0, 1023, 0, 255);

  //makeItRainbow();

  makeGradients();

  makeCheckerboard();

  pixels1.show(); 
  pixels2.show();
  shifter1++;
  shifter2++;
  shifter1%=NUMPIXELS;
  shifter2%=NUMPIXELS;
}



uint32_t Wheel1(byte WheelPos) 
{
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) 
  {
    return pixels1.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) 
  {
    WheelPos -= 85;
    return pixels1.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels1.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

uint32_t Wheel2(byte WheelPos) 
{
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) 
  {
    return pixels2.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) 
  {
    WheelPos -= 85;
    return pixels2.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels2.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void makeItRainbow()
{
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels1.setPixelColor((i+shifter1)%NUMPIXELS, Wheel1(map(i, 0, NUMPIXELS/NUMRAINBOWS, 0, 255)%255));      //Full Rainbow
    pixels2.setPixelColor((i+shifter2)%NUMPIXELS, Wheel2(map(i, 0, NUMPIXELS/NUMRAINBOWS, 0, 255)%255));      //Full Rainbow
  }
}

void makeGradients()
{
  for(int i=0;i<NUMPIXELS;i++)
  {
    if (i%(NUMPIXELS/NUMRAINBOWS) < (NUMPIXELS/NUMRAINBOWS)/2)
    {
      pixels1.setPixelColor((i+shifter1)%NUMPIXELS, Wheel1(map(i%(NUMPIXELS/NUMRAINBOWS), 0, NUMPIXELS/(NUMRAINBOWS*2), LOWERCOLOR, UPPERCOLOR)));  
    }
    else
    {
      pixels1.setPixelColor((i+shifter1)%NUMPIXELS, Wheel1(map(i%(NUMPIXELS/NUMRAINBOWS), NUMPIXELS/(NUMRAINBOWS*2), NUMPIXELS/NUMRAINBOWS, UPPERCOLOR, LOWERCOLOR)));  
    }

    if (i%(NUMPIXELS/NUMRAINBOWS) < (NUMPIXELS/NUMRAINBOWS)/2)
    {
      pixels2.setPixelColor((i+shifter2)%NUMPIXELS, Wheel2(map(i%(NUMPIXELS/NUMRAINBOWS), 0, NUMPIXELS/(NUMRAINBOWS*2), LOWERCOLOR, UPPERCOLOR)));  
    }
    else
    {
      pixels2.setPixelColor((i+shifter2)%NUMPIXELS, Wheel2(map(i%(NUMPIXELS/NUMRAINBOWS), NUMPIXELS/(NUMRAINBOWS*2), NUMPIXELS/NUMRAINBOWS, UPPERCOLOR, LOWERCOLOR)));  
    }
  }
}

void makeCheckerboard()
{
  for(int i=0;i<NUMPIXELS;i++)
  {
    if(millis()%toggletime > toggletime/2)
    {
      if ((i%2)+toggler == 0)
      {
      pixels1.setPixelColor(i,0,0,0);  
      }
      if ((i%2)+toggler == 1)
      {
        pixels2.setPixelColor(i,0,0,0);
      } 
    }
    else
    {
      if ((i%2)+toggler == 1)
      {
        pixels1.setPixelColor(i,0,0,0);  
      }
      if ((i%2)+toggler == 0)
      {
        pixels2.setPixelColor(i,0,0,0);
      }
    }    
  }
}


