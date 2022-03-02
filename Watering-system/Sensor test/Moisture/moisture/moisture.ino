const int sensor_pin_1 = A1;  /* Soil moisture sensor O/P pin */
const int sensor_pin_2 = A2;  /* Soil moisture sensor O/P pin */

void setup() {
  Serial.begin(9600); /* Define baud rate for serial communication */
}

void loop() {
  float moisture_percentage_A1;
  float moisture_percentage_A2;
  int sensor_analog_A1;
  int sensor_analog_A2;
  sensor_analog_A1 = analogRead(sensor_pin_1);
  sensor_analog_A2 = analogRead(sensor_pin_2);
  moisture_percentage_A1 = ( 100 - ((sensor_analog_A1/1023.00) * 100 ));
  moisture_percentage_A2 = ( 100 - ((sensor_analog_A2/1023.00) * 100 ));
  Serial.print("Moisture Percentage A1 = ");
  Serial.print(moisture_percentage_A1);
  Serial.print("=====");
  Serial.print("Moisture Percentage A2 = ");
  Serial.print(moisture_percentage_A2);
  Serial.print("%\n\n");
  delay(1000);
}
