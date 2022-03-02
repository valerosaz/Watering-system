#define ledPin 13
#include <SoftwareSerial.h>
SoftwareSerial MyBlue(2, 3); // RX | TX
int state = 0;
void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  MyBlue.begin(9600);
  Serial.begin(9600); // Default communication rate of the Bluetooth module
}
void loop() {
  if(MyBlue.available() > 0){ // Checks whether data is comming from the serial port
    state = MyBlue.read(); // Reads the data from the serial port
 }
 if (state == '0') {
  digitalWrite(ledPin, LOW); // Turn LED OFF
  Serial.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
  state = 0;
 }
 else if (state == '1') {
  digitalWrite(ledPin, HIGH);
  Serial.println("LED: ON");;
  state = 0;
 } 
}
