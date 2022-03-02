// Phuc Le
// 456061
// Exhbition - Watering system
// Hardware part (device code)



int motorPinOut = 10; //Pin starts water pump motor
const int buttonPin = 2;     // the number of the pushbutton pin
const int wateringLedPin =  13;      // the number of the LED pin
//const double waterEveryMinutes = 0.5; // Time Interval pump starts watering process. In minutes.
//const double wateringTimeInMinutes = 0.2; // Time Watering Process takes. In minutes.
boolean isWatering = false; //
//"ALWAYS use unsigned long for timers, not int"
//unsigned long lastWateringTime = millis() - (waterEveryMinutes * 60 * 1000); // Time of last watering. Milliseconds since Arduino program has started.
//unsigned long wateringStartedTime = millis() - (wateringTimeInMinutes * 60 * 1000); //"ALWAYS use unsigned long for timers, not int"
boolean buttonState = false; //Button state, FALSE=unpressed, TRUE=pressed
int lastButtonState = buttonState; // Previous button state. Used to reduce state related signals spamming.

const int sensor_pin_1 = A1;  /* Soil moisture sensor O/P pin */
const int sensor_pin_2 = A2;  /* Soil moisture sensor O/P pin */
int trigPin = 11;    // Trigger
int echoPin = 12;    // Echo
long duration, cm, inches;
int greenLed = 2;
int yellowLed = 3;
int redLed = 4;

void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  pinMode(motorPinOut, OUTPUT);
  // initialize the LED pin as an output:
  pinMode(wateringLedPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  //=====================================soil's moisture================================//

  float moisture_percentage_A1;
  //float moisture_percentage_A2;
  int sensor_analog_A1;
  //int sensor_analog_A2;
  sensor_analog_A1 = analogRead(sensor_pin_1);
  //sensor_analog_A2 = analogRead(sensor_pin_2);
  moisture_percentage_A1 = ( 100 - ((sensor_analog_A1 / 1023.00) * 100 ));
  //moisture_percentage_A2 = ( 100 - ((sensor_analog_A2 / 1023.00) * 100 ));
  Serial.print("Moisture Percentage A1 = ");
  Serial.print(moisture_percentage_A1);
  //Serial.print("=====");
  //Serial.print("Moisture Percentage A2 = ");
  //Serial.print(moisture_percentage_A2);
  //Serial.print("%\n\n");
  delay(250);

  //=====================================water level detector===============================//
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // Convert the time into a distance
  cm = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
  inches = (duration / 2) / 74; // Divide by 74 or multiply by 0.0135

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();


  //If water tank is about 12cm height
  if (cm >= 8 && cm <= 12) {
    digitalWrite(greenLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
  }
  if (cm >= 4 && cm <= 8) {
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, HIGH);
    digitalWrite(redLed, LOW);
  }
  if (cm >= 1 && cm <= 4) {
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, HIGH);
  }
  delay(50);
  //======================================Water Pumper=================================//
  if (moisture_percentage_A1 < 55) {
    if (isWatering) {
      //long timer = (wateringStartedTime + (wateringTimeInMinutes * 60 * 1000)) - millis();
      digitalWrite(motorPinOut, LOW);
      if (timer <= 0) {
        stopWatering();
      } else {
        //printOuput("Watering starts in " + millisToTime(timer));
        printOuput("Watering ended!");
      }
    }
  }
  else {
    if (moisture_percentage_A1 >= 55) {
      digitalWrite(motorPinOut, HIGH);
      //long timer = (lastWateringTime + (waterEveryMinutes * 60 * 1000)) - millis();
      if (timer <= 0) {
        startWatering();
      } else {
        //printOuput("Watering ends in " + millisToTime(timer));
        printOuput("Watering started!");
      }
    }
  }

  //button state allow manually turn on/off motor ~ interfering the watering procedure
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(wateringLedPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(wateringLedPin, LOW);
  }
  // check if the pushbutton is pressed (buttonState is HIGH) AND if previous pushbutton state was different start or stop watering
  if (buttonState == HIGH && lastButtonState == LOW && !isWatering) {
    startWatering();
  } else if (buttonState == HIGH && lastButtonState == LOW && isWatering) {
    stopWatering();
  }
  lastButtonState = buttonState;
}


void startWatering() {
  isWatering = true;
  printOuput("Watering starts");
  // start motor
  digitalWrite(motorPinOut, LOW);
  //wateringStartedTime = millis();
  //lastWateringTime = millis();
}
void stopWatering() {
  isWatering = false;
  printOuput("Watering ends");
  // stop motor
  digitalWrite(motorPinOut, HIGH);
}

String millisToTime(unsigned long milliseconds) {
  int seconds = (int) (milliseconds / 1000) % 60 ;
  int minutes = (int) ((milliseconds / (1000 * 60)) % 60);
  int hours   = (int) ((milliseconds / (1000 * 60 * 60)) % 24);
  String timeString = "";
  timeString = timeString + hours + ":" + minutes + ":" + seconds;
  return timeString;
}
void printOuput(String msg) {
  Serial.print(msg + "\n");
}
