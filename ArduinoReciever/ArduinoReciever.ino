#include <Wire.h>

void setup() {

  Wire.begin(4); // Join I2C bus with address 4

  

  Serial.begin(9600); // Set baud rate for serial output 

}

void loop() {
  Wire.onReceive(receiveEvent); // Register Event
  delay(100);

}

void receiveEvent(int howMany){
  while (0 < Wire.available()) // Loop through all but last
  {
    char c = Wire.read(); // Recieve byte as a character
    Serial.print(c);
  }

  Serial.print('\n');
}