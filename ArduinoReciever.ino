#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#define MAX_LEN 64

#define TFT_RST 8 
#define TFT_DC 9              
#define TFT_CS 10    
#define TFT_MOSI 11               
#define TFT_MISO 12           
#define TFT_CLK 13     

//char myString[MAX_LEN];
String myString;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO); // Init tft struct 

/*
can try this to also send audio data in buffer 
struct mydata {
  byte x, y;
} myStruct;

void receiveEvent(int howMany) {
  if (howMany == sizeof(myStruct)) {
    for (int i = 0; i < howMany;)
      ((byte*) &myStruct)[i++] = Wire.read();
    i2cDataReceived = true;
  }
}
*/

void setup() {

  Wire.begin(4); // Join I2C bus with address 4
  tft.begin(); // Initialize ILI9341 Display
  tft.fillScreen(ILI9341_BLACK); // Fill screen with black 
  tft.setTextColor(ILI9341_WHITE);  
  tft.setTextSize(2);

  Serial.begin(9600); // Set baud rate for serial output 

}

void loop() {
  Wire.onReceive(receiveEvent); // Register Event
  delay(500);

}

void receiveEvent(int numEvents){
  while (0 < Wire.available()) // Loop through all but last
  {
    char c = Wire.read(); // Recieve byte as a character
    Serial.print(c);
    Serial.print("\n");
    myString.concat(c);
  }
  writeText();

}

void writeText() {
  //unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.println(myString);
  // TODO: Add draw frequency bins from buffer call function here 
  //return micros() - start;
}



