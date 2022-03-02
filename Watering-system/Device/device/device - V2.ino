// Phuc Le
// 456061
// Exhbition - Watering system
// Hardware part (device code)


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


SoftwareSerial BT(11, 12); //TX, RX respetively
UltraSonicDistanceSensor distanceSensor(9, 8);  // Initialize sensor that uses digital pins 9 and 10.
int moisture = A1;  /* Soil moisture sensor O/P pin */
int greenLed = 2;
int yellowLed = 3;
int redLed = 4;
int in1 = 5;  // IN1
int in2 = 6;  // IN2
int en1 = 10;
unsigned int a, b, val;
void setup () {
  Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
  BT.begin(9600);// We initialize bluetooth module.
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(en1, OUTPUT);
  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();

}

void loop () {
  //======================================Moisture=================================//
  float moisture_percentage;
  float sensor_analog;
  sensor_analog = analogRead(moisture);
  moisture_percentage = ( 100 - ((sensor_analog / 1023.00) * 100 ));
  //======================================Water Level=================================//
  //Every 1 SECOND, do a measurement using the sensor and print the distance in centimeters.
  float distance = distanceSensor.measureDistanceCm();
  if (distance < 0) {
    distance = 0;
  }
  float distance_percentage = (distance / 18) * 100;

  //======================================Water Pumper=================================//
  if (BT.available() >= 2)//2byte number
  {
    a = BT.read();
    b = BT.read();
    val = (b * 256) + a;
    if (val >= 0 && val <= 255)// slider value
    { // Manually mode

      int motorspeed = map(val, 0, 255, 0, 255);
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(en1, motorspeed);
      //BT.println();
      //Serial.println(val);
    }

  }
  //Auto mode
  if ((moisture_percentage < 60) && (distance_percentage < 80)) {
    analogWrite(en1, 100);
    digitalWrite(in2, 1);
  }
  if ((moisture_percentage < 60) && (distance_percentage > 80)) {
    analogWrite(en1, 0);
    digitalWrite(in2, 0);
  }
  if ((moisture_percentage > 60) && (distance_percentage > 80)) {
    analogWrite(en1, 0);
    digitalWrite(in2, 0);
  }
  if ((moisture_percentage > 60) && (distance_percentage < 80)) {
    analogWrite(en1, 0);
    digitalWrite(in2, 0);
  }

  //Data stransfering to Android app
  BT.print(distance_percentage);
  BT.print("|");
  BT.print(moisture_percentage);
  BT.print("|");
  BT.println();
  delay(1000);


  // display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15, 20);
  display.print("Moisture: ");
  display.print(moisture_percentage);
  display.print("%");
  display.setCursor(10, 30);
  display.print("Water Level");
  display.setCursor(20, 40);
  display.print(distance);
  display.print("cm");
  display.print(" | ");
  display.print(distance_percentage);
  display.print("%");
  display.display();
  display.clearDisplay();
  //Serial.println(distance);
  // Check water tank level + LED notification
  if (distance >= 13 && distance <= 18) {
    //Serial.print("High");
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, HIGH);
  }
  if (distance >= 7 && distance <= 12) {
    //Serial.print("Moderate");
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, HIGH);
    digitalWrite(redLed, LOW);
  }
  if (distance >= 1 && distance <= 6) {
    //Serial.print("Low");
    digitalWrite(greenLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
  }
}
