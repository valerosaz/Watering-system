
#include <HCSR04.h>
#include <SoftwareSerial.h>
#include <Wire.h> // Library for I2C communication
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
// OLED display TWI address
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


SoftwareSerial BT(10, 11); //TX, RX respetively
UltraSonicDistanceSensor distanceSensor(9, 8);  // Initialize sensor that uses digital pins 9 and 10.
int moisture = A1;  /* Soil moisture sensor O/P pin */
void setup () {
  Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
  BT.begin(9600);// We initialize bluetooth module.
  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();

}
//E-innovators
void loop () {
  float moisture_percentage;
  float sensor_analog;
  sensor_analog = analogRead(moisture);
  moisture_percentage = ( 100 - ((sensor_analog / 1023.00) * 100 ));

  //Every 1 SECOND, do a measurement using the sensor and print the distance in centimeters.
  float distance = distanceSensor.measureDistanceCm();
  if (distance < 0) {
    distance = 0;
  }
  // display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15, 20);
  display.print("Moisture: ");
  display.print(moisture_percentage);
  display.print("%");
  display.setCursor(10, 40);
  display.print("Water Level: ");
  display.print(distance);
  display.print("cm");
  display.display();
  //delay(1000);
  display.clearDisplay();
  //Serial.println(distance);
  BT.print(distance);
  BT.print("|");
  BT.print(moisture_percentage);
  BT.println();
  delay(1000);

}
