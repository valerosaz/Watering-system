#include <SoftwareSerial.h>
int en1 = 10;
int in1 = 5;
int in2 = 6;
SoftwareSerial BT(11, 12); //TX, RX respetively
void setup() {
  BT.begin(9600);
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(en1, OUTPUT);

}

void loop() {

//  if (Serial.available() >= 2 )//2byte number
//  {
    unsigned int a = BT.read();
    unsigned int b = BT.read();
    unsigned int val = (b * 256) + a;
    if (val >= 0 && val <= 255)
    {

      int motorspeed = map(val, 0, 255, 0, 255);
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(en1, motorspeed);
      
    }
//  }
}
