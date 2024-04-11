#include <LedControl.h>
#include <IRremote.h>
#include <Wire.h> 

const int moveSensor =7;
IRrecv recv(3);                 //IR Receiver Object
int DIN = 12;
int CS = 11;
int CLK = 10;
LedControl lc(DIN, CLK, CS, 1); //8x8 LED Matrix Object

int lastSensorValue = LOW;
byte lastImage[8] ;

//Facial Expressions
byte pacman3[8]=   {0x1c,0x3E,0x49,0x5B,0x7F,0x7F,0x7F,0x55};
byte pacman1[8]=   {0x3c,0x66,0xEF,0xF0,0xF0,0xFF,0x7E,0x3C};
byte pacman2[8]=   {0x3C,0x66,0xEE,0xFF,0xF0,0xFF,0x7E,0x3C};
byte heart[8]=   {0x0,0x66,0x99,0x99,0x81,0x42,0x24,0x18};
byte smile[8]=   {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};
byte neutral[8]= {0x3C,0x42,0xA5,0x81,0xBD,0x81,0x42,0x3C};
byte sad[8]=   {0x3C,0x42,0xA5,0x81,0x99,0xA5,0x42,0x3C};

void setup() 
{
  pinMode(buzzer,OUTPUT);
 // put your setup code here
   for (int i = 0; i < 8; ++i) 
      {
        lastImage[i] = smile[i];
      }
  pinMode(moveSensor,INPUT);

  lc.shutdown(0, false);
  lc.setIntensity(0, 5);
  lc.clearDisplay(0) ;
  recv.enableIRIn();
  
  Serial.begin(9600);
  
}
void loop() {
  // put your main code here
  int sensorValue = digitalRead(moveSensor);
  if(recv.decode())
  {
    Serial.println(recv.decodedIRData.decodedRawData, HEX);
    //Check for next button 1
    if(recv.decodedIRData.decodedRawData == 0xF30CFF00)
    {
      drawImage(smile); 
      for (int i = 0; i < 8; ++i) 
      {
        lastImage[i] = smile[i];
      }
    }
    //Check for next button 2
    if(recv.decodedIRData.decodedRawData == 0xE718FF00)
    {
      drawImage(sad);   
      for (int i = 0; i < 8; ++i) 
      {
        lastImage[i] = sad[i];
      }
    }
    //Check for next button 3
    if(recv.decodedIRData.decodedRawData == 0xA15EFF00)
    {
      drawImage(neutral);   
      for (int i = 0; i < 8; ++i) 
      {
        lastImage[i] = neutral[i];
      }
    }
    //Check for next button 4
    if(recv.decodedIRData.decodedRawData == 0xF708FF00)
    {
      drawImage(pacman1);   
      for (int i = 0; i < 8; ++i) 
      {
        lastImage[i] = pacman1[i];
      }
    }
    //Check for next button 5
    if(recv.decodedIRData.decodedRawData == 0xE31CFF00)
    {
      drawImage(pacman2);   
      for (int i = 0; i < 8; ++i) 
      {
        lastImage[i] = pacman2[i];
      }
    }
    //Check for next button 6
    if(recv.decodedIRData.decodedRawData == 0xA55AFF00)
    {
      drawImage(pacman3);   
      for (int i = 0; i < 8; ++i) 
      {
        lastImage[i] = pacman3[i];
      }
    }
        //Check for next button 7
    if(recv.decodedIRData.decodedRawData == 0xBD42FF00)
    {
      drawImage(heart);   
      for (int i = 0; i < 8; ++i) 
      {
        lastImage[i] = heart[i];
      }
    }
    recv.resume();
  }
  //check if matrix is tilted
  if(sensorValue == 0)
  {
    
    drawImageUpsideDown(lastImage);
  }
  else
  {
      drawImage(lastImage);
  }

}

void drawImageUpsideDown(byte image[]) {
 for(int i =0; i<=7; i++){
    lc.setColumn(0, 7-i, image[i]); // Reverse the order of rows
  }
}
void drawImage(byte image[]) {
 for(int i =0; i<=7; i++){
    lc.setColumn(0, i, image[i]); 
  }
}
