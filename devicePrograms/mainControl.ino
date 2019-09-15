/*
 * This code is the code of the main control Arduino of the butt collecter
 * The device waits for a butt to cross between the LED and the sensor
 * The device then recieves the QR code from the QR holder device.
 */

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>

// Color definitions
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF

#define __CS 10
#define __DC 9
#define __A0 8

//delay between bits
#define dlt 60

//lcd screen object
TFT_ILI9163C tft = TFT_ILI9163C(__CS,__A0, __DC);

//pinouts
int enablePin = 5;
int clockPin = 2;
int dataPin = 3;
int recPin = 14;
int red = 16;
int green = 17;

//initial light
int base;

//measures and averages the light read by the sensor (n times)
int measureLight(int n = 100)
{
  long sum = 0;
  for(int i = 0;i<n;i++)
  {
    sum += analogRead(1);
    delay(1);
  }
  return int(sum/n);
}

void setup() 
{
  //begin of serial and screen
  Serial.begin(9600);
  tft.begin();
  tft.fillScreen(); //initial black screen

  //initialize data and output pins
  pinMode(clockPin,OUTPUT);
  pinMode(enablePin,OUTPUT);
  pinMode(dataPin,INPUT);
  pinMode(recPin,INPUT);
  pinMode(green,OUTPUT);
  pinMode(red,OUTPUT);
  digitalWrite(red,1);
  digitalWrite(green,0);
  
  //measure initial light
  base = measureLight(200);
}

void loop()
{
  if(measureLight(30) < base-30) //if the butt blocks the light
  {
    //reset colors
    digitalWrite(red,0);
    digitalWrite(green,1);

    //setting clock and enable to receive bits
    digitalWrite(clockPin,0);
    delay(1);
    digitalWrite(enablePin,1);
    delayMicroseconds(200);

  //receiving 128*128 bits from the other Arduino
  for(int i = 0; i < 128; i++)
  {
    for(int j = 0; j < 128; j++)
    {
      digitalWrite(clockPin,1);
      while(!digitalRead(recPin)); //wait until the dataPin is set.
      if(digitalRead(dataPin)) //read out dataPin
      {
          tft.drawPixel(i,j,WHITE); //if 1 is received outputs it on screen
      }
      digitalWrite(clockPin,0); 
      delayMicroseconds(dlt);
    }
  }

  //turn off data transfer and wait 30 seconds
  digitalWrite(enablePin,0);
  delay(30000);

  //reset LEDs and screen
  digitalWrite(red,1);
  digitalWrite(green,0);
  tft.fillScreen();
  }
}
