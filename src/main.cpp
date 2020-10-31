// Based on https://github.com/lakshanthad/Wio_Terminal_Classroom_Arduino/blob/main/Classroom%2012/Smart_Garden/Smart_Garden.ino

#include <Arduino.h>
#include "SHT31.h"

//Libraries
#include "TFT_eSPI.h" //TFT LCD library
//Initializations
SHT31 sht31 = SHT31();
TFT_eSPI tft; //Initializing TFT LCD
TFT_eSprite spr = TFT_eSprite(&tft); //Initializing buffer

//Soil Moisture Sensor definitions
int sensorPin = A0; //Define variable to store soil moisture sensor pin
int sensorValue = 0; //Define variable to store soil moisture sensor value
int waterThreshold = 20;

void setup() {
  Serial.begin(9600); //Start serial communication

  pinMode(sensorPin, INPUT);
  pinMode(WIO_LIGHT, INPUT); //Set light sensor pin as INPUT
  pinMode(WIO_BUZZER, OUTPUT); //Set buzzer pin as OUTPUT

  sht31.begin(); //Start SHT sensor
  tft.begin(); //Start TFT LCD
  tft.setRotation(3); //Set TFT LCD rotation
  spr.createSprite(TFT_HEIGHT,TFT_WIDTH); //Create buffer
}

void loop() {
  //Setting the title header
  spr.fillSprite(TFT_WHITE); //Fill background with white color
  spr.fillRect(0,0,320,50,TFT_DARKGREEN); //Rectangle fill with dark green
  spr.setTextColor(TFT_WHITE); //Setting text color
  spr.setTextSize(3); //Setting text size
  spr.drawString("Smart Garden",50,15); //Drawing a text string

  spr.drawFastVLine(150,50,190,TFT_DARKGREEN); //Drawing verticle line
  spr.drawFastHLine(0,140,320,TFT_DARKGREEN); //Drawing horizontal line

  //Setting temperature
  int t = sht31.getTemperature(); //Assign variable to store temperature
  spr.setTextColor(TFT_BLACK);
  spr.setTextSize(2);
  spr.drawString("Temperature",10,65);
  spr.setTextSize(3);
  spr.drawNumber(t,50,95); //Display temperature values
  spr.drawString("C",90,95);

  //Setting humidity
  int h = sht31.getHumidity(); //Assign variable to store humidity
  spr.setTextSize(2);
  spr.drawString("Humidity",25,160);
  spr.setTextSize(3);
  spr.drawNumber(h,30,190); //Display humidity values
  spr.drawString("%RH",70,190);

  //Setting soil moisture
  sensorValue = analogRead(sensorPin); //Store sensor values
  sensorValue = map(sensorValue,650,250,0,100); //Map sensor values
  spr.setTextSize(2);
  spr.drawString("Soil Moisture",160,65);
  spr.setTextSize(3);
  spr.drawNumber(sensorValue,200,95); //Display sensor values as percentage
  spr.drawString("%",240,95);

  //Setting light
  int light = analogRead(WIO_LIGHT); //Assign variable to store light sensor values
  spr.setTextSize(2);
  spr.drawString("Light",200,160);
  spr.setTextSize(3);
  light = map(light,0,1023,0,100); //Map sensor values
  spr.drawNumber(light,205,190); //Display sensor values as percentage
  spr.drawString("%",245,190);

  //Condition for low soil moisture
  if(sensorValue < waterThreshold){
    spr.fillSprite(TFT_RED);
    spr.drawString("Time to water!",35,100);
    if (light > 1) {    //Don't beep at night
      analogWrite(WIO_BUZZER, 150); //beep the buzzer
      delay(1000);
      analogWrite(WIO_BUZZER, 0); //Silence the buzzer
      delay(1000);
    }
  }

  spr.pushSprite(0,0); //Push to LCD
  delay(1000);


}
