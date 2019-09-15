/*
 * This code reads the QR code from the SD card and transfers it to to the main Arduino
 */


#include <SPI.h>
#include <SD.h>

//delay time, for QR Code send (microSeconds)
#define dlt 60

//sd card reader object
File myFile;
int buffer;

//arduino communication pins
int clockPin = 2;
int dataPin = 3;
int enablePin = 5;
int sendPin = 6;


void setup() 
{
  //pin initializazion
  pinMode(clockPin,INPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(enablePin,INPUT);
  pinMode(sendPin,OUTPUT);

  //serial sd begin
  Serial.begin(9600);
  if (!SD.begin(4)) 
  {
    Serial.println("initialization failed!");
    while (1);
  }
}

void loop() 
{
  //only sends data if enablePin is activated
  if(digitalRead(enablePin))
  {
    myFile = SD.open("qr.txt"); //filename for specific QR code (can be changed)
    //reading the whole file
    while (myFile.available()) 
    {
      while(!digitalRead(clockPin))
      { 
        delayMicroseconds(dlt/10);
      } //sync
      buffer = myFile.read(); //read next charachter
      if(buffer == 48) //read 0 --> send 0 on dataPin
      {
         digitalWrite(dataPin,0);
         delayMicroseconds(dlt);   
         digitalWrite(sendPin,1); //data is sent
         delayMicroseconds(dlt); 
      }
      if(buffer == 49) //read 1 --> send 1 on dataPin
      {
         digitalWrite(dataPin,1);
         delayMicroseconds(dlt);
         digitalWrite(sendPin,1); //data is sent
         delayMicroseconds(dlt); 
      }
      digitalWrite(sendPin,0); //reset sendPin
    }//end of file reading
    //closing file and resetting
    myFile.close();
    digitalWrite(dataPin,0);
    delay(2000);
  } //end of if enabled
}
