#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11); //TX, RX respetively
// Connection pins:
int in1 = 5;  // IN1
int in2 = 6;  // IN2
int pot = A0; // potentiometer middle pin to control speed of the DC motor
String state;
String mode;
int flag = 0;        //makes sure that the serial only prints once the state
int stateStop = 0;
int moisture = A1;  /* Soil moisture sensor O/P pin */
void setup()
{
  Serial.begin(9600);
  BT.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void loop()
{
  float moisture_percentage;
  float sensor_analog;
  sensor_analog = analogRead(moisture);
  moisture_percentage = ( 100 - ((sensor_analog / 1023.00) * 100 ));
  if (BT.available() > 0) {
    state = BT.read();
    mode = BT.read();
    flag = 0;
  }
  //  if (mode == "AUTO") {
  //    // MANUALLY CONTROL MOTOR
  //    int potvalue = analogRead(pot);  // Potentiometer connected to Pin A1
  //    int motorspeed = map(potvalue, 0, 1023, 0, 255);
  //    float speedInPercentage = 100 - ((motorspeed * 100) / 254) ;
  //    analogWrite(in1, motorspeed);  // set speed of motor (0-255)
  //    //Condition to trigger the motor automatically
  //    if (moisture_percentage <= 55) {
  //      analogWrite(in1, 100);
  //      digitalWrite(in2, 1);  // set rotation direction of motor (1 or 0)
  //      Serial.print(speedInPercentage);
  //      Serial.print("%");
  //      Serial.print("==");
  //      Serial.println(motorspeed);
  //    }
  //    if (moisture_percentage > 55) {
  //      //analogWrite(in1, motorspeed);  // set speed of motor (0-255)
  //      analogWrite(in1, 0);  // set speed of motor (0-255)
  //      digitalWrite(in2, 0);  // set rotation direction of motor (1 or 0)
  //    }
  //    if (flag == 0) {
  //      BT.println("AUTO");
  //      flag = 1;
  //    }
  //  }
  //  if (mode == "MANUAL") {
  int potvalue = analogRead(pot);  // Potentiometer connected to Pin A1
  int motorspeed = map(potvalue, 0, 1023, 0, 255);
  if (state == "0%") {
    analogWrite(in1, 0);  // set speed of motor (0-255)
    digitalWrite(in2, 0);  // set rotation direction of motor (1 or 0)
    if (flag == 0) {
      BT.println("0%");
      flag = 1;
    }
    stateStop = 0;
  }
  if (state == "20%") {
    analogWrite(in1, 50);  // set speed of motor (0-255)
    digitalWrite(in2, 1);  // set rotation direction of motor (1 or 0)
    if (flag == 0) {
      BT.println("20%");
      flag = 1;
    }
  }
  if (state == "40%") {
    analogWrite(in1, 100);  // set speed of motor (0-255)
    digitalWrite(in2, 1);  // set rotation direction of motor (1 or 0)
    if (flag == 0) {
      BT.println("40%");
      flag = 1;
    }
  }
  if (state == "60%") {
    analogWrite(in1, 150);  // set speed of motor (0-255)
    digitalWrite(in2, 1);  // set rotation direction of motor (1 or 0)
    if (flag == 0) {
      BT.println("60%");
      flag = 1;
    }
  }
  if (state == "80%") {
    analogWrite(in1, 200);  // set speed of motor (0-255)
    digitalWrite(in2, 1);  // set rotation direction of motor (1 or 0)
    if (flag == 0) {
      BT.println("80%");
      flag = 1;
    }
  }
  if (state == "100%") {
    analogWrite(in1, 254);  // set speed of motor (0-255)
    digitalWrite(in2, 1);  // set rotation direction of motor (1 or 0)
    if (flag == 0) {
      BT.println("100%");
      flag = 1;
    }
  }
  //    if (flag == 0) {
  //      BT.println("MANUAL");
  //      flag = 1;
  //    }
  //  }
}
