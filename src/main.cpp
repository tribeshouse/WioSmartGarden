// Based on https://github.com/lakshanthad/Wio_Terminal_Classroom_Arduino/blob/main/Classroom%2012/Smart_Garden/Smart_Garden.ino

#include "blynk.h"
#include "SHT31.h"

//Libraries
#include "TFT_eSPI.h" //TFT LCD library
//Initializations
SHT31 sht31 = SHT31();
TFT_eSPI tft; //Initializing TFT LCD
#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD
#define LCD_TIMEOUT 10000L
#define UPDATE_FEQUENCY 30000L

#include <Button.h>

Button button_press(WIO_5S_PRESS); 

// Soil Moisture Sensor definitions
int sensorPin = A0; //Define variable to store soil moisture sensor pin
int sensorValue = 0; //Define variable to store soil moisture sensor value

void update()
{
  // Setting temperature
  int t = sht31.getTemperature();         // Assign variable to store temperature
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // Setting text color
  tft.setTextSize(2);
  tft.drawString("Temperature", 10, 65);
  tft.setTextSize(3);
  tft.drawNumber(t, 50, 95); // Display temperature values
  tft.drawString("°C", 90, 95);

  // Setting humidity
  int h = sht31.getHumidity(); // Assign variable to store humidity
  tft.setTextSize(2);
  tft.drawString("Humidity", 25, 160);
  tft.setTextSize(3);
  tft.drawNumber(h, 30, 190); // Display humidity values
  tft.drawString("%RH", 70, 190);

  // Setting soil moisture
  sensorValue = analogRead(sensorPin); // Store sensor values
  sensorValue = map(sensorValue,430,350,0,100); //Map sensor values
  tft.setTextSize(2);
  tft.drawString("Soil Moisture", 160, 65);
  tft.setTextSize(3);
  tft.drawNumber(sensorValue, 200, 95); // Display sensor values as percentage
  tft.drawString("%",260,95);

  // Setting light
  int light = analogRead(WIO_LIGHT); // Assign variable to store light sensor values
  tft.setTextSize(2);
  tft.drawString("Light", 200, 160);
  tft.setTextSize(3);
  light = map(light, 0, 1023, 0, 100); // Map sensor values
  tft.drawNumber(light, 205, 190);     // Display sensor values as percentage
  tft.drawString("%", 260, 190);

  // //Condition for low soil moisture
  // if(sensorValue < waterThreshold){
  //   tft.fillSprite(TFT_RED);
  //   tft.drawString("Time to water!",35,100);
  //   if (light > 1) {    //Don't beep at night
  //     analogWrite(WIO_BUZZER, 150); //beep the buzzer
  //     delay(1000);
  //     analogWrite(WIO_BUZZER, 0); //Silence the buzzer
  //     delay(1000);
  //   }
  // }


  Blynk.virtualWrite(V1, sensorValue);
  Blynk.virtualWrite(V2, h);
  Blynk.virtualWrite(V3, t);
  Blynk.virtualWrite(V4, light);
}

void idle_lcd()
{
  digitalWrite(LCD_BACKLIGHT, LOW);
}

void setup() {
#if defined(SERIAL_DEBUG)
  Serial.begin(TERMINAL_BAUD);
#endif

  pinMode(sensorPin, INPUT);
  pinMode(WIO_LIGHT, INPUT); //Set light sensor pin as INPUT
  pinMode(WIO_BUZZER, OUTPUT); //Set buzzer pin as OUTPUT

  button_press.begin();

  sht31.begin(); //Start SHT sensor
  tft.begin(); //Start TFT LCD
  tft.setRotation(3); //Set TFT LCD rotation
  tft.fillScreen(TFT_BLACK); // fills entire the screen with colour
  //Setting the title header
  tft.fillRect(0,0,320,50,TFT_DARKGREEN); //Rectangle fill with dark green
  tft.setTextColor(TFT_WHITE, TFT_DARKGREEN);       // Setting text color
  tft.setTextSize(3);                     // Setting text size
  tft.drawString("Smart Garden", 50, 15); // Drawing a text string
  tft.drawFastVLine(150, 50, 190, TFT_DARKGREEN); // Drawing verticle line
  tft.drawFastHLine(0, 140, 320, TFT_DARKGREEN);  // Drawing horizontal line

  edgentTimer.setInterval(UPDATE_FEQUENCY, update);
  edgentTimer.setTimeout(LCD_TIMEOUT, idle_lcd);
  BlynkEdgent.begin();
}

void loop()
{
  if (button_press.pressed())
  {
    digitalWrite(LCD_BACKLIGHT, HIGH);
    edgentTimer.setTimeout(LCD_TIMEOUT, idle_lcd);
  }
  BlynkEdgent.run();
}
