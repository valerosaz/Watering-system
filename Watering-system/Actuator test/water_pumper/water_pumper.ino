int motorPinOut = 10; //Pin starts water pump motor
const int buttonPin = 2;     // the number of the pushbutton pin
const int wateringLedPin =  13;      // the number of the LED pin
const double waterEveryMinutes=0.5;  // Time Interval pump starts watering process. In minutes.
const double wateringTimeInMinutes=0.2; // Time Watering Process takes. In minutes.
boolean isWatering = false; //
//"ALWAYS use unsigned long for timers, not int"
unsigned long lastWateringTime=millis()-(waterEveryMinutes*60*1000);   // Time of last watering. Milliseconds since Arduino program has started.
unsigned long wateringStartedTime=millis()-(wateringTimeInMinutes*60*1000);   //"ALWAYS use unsigned long for timers, not int"
boolean buttonState = false; //Button state, FALSE=unpressed, TRUE=pressed
int lastButtonState=buttonState; // Previous button state. Used to reduce state related signals spamming.
void setup() {
    Serial.begin(9600);
    pinMode(motorPinOut, OUTPUT);
    // initialize the LED pin as an output:
    pinMode(wateringLedPin, OUTPUT);
    // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT);
}

void loop() {
    
    if(isWatering){
        long timer=(wateringStartedTime+(wateringTimeInMinutes*60*1000))-millis();
        digitalWrite(motorPinOut, LOW);
        if(timer<=0){
            stopWatering();
            }else{
            printOuput("Watering starts in "+millisToTime(timer));
        }
        }else{
        digitalWrite(motorPinOut, HIGH);
        long timer=(lastWateringTime+(waterEveryMinutes*60*1000))-millis();
        if(timer<=0){
            startWatering();
            }else{
            printOuput("Watering ends in "+millisToTime(timer));
        }
    }
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH){
        // turn LED on:
        digitalWrite(wateringLedPin, HIGH);
        }else{
        // turn LED off:
        digitalWrite(wateringLedPin, LOW);
    }
    // check if the pushbutton is pressed (buttonState is HIGH) AND if previous pushbutton state was different start or stop watering
    if (buttonState == HIGH && lastButtonState == LOW && !isWatering) {
        startWatering();
        } else if(buttonState == HIGH && lastButtonState == LOW && isWatering){
        stopWatering();
    }
    lastButtonState=buttonState;
}
void startWatering(){
    isWatering=true;
    printOuput("Watering starts");
    // start motor
    digitalWrite(motorPinOut, LOW);
    wateringStartedTime=millis();
    lastWateringTime=millis();
}
void stopWatering(){
    isWatering=false;
    printOuput("Watering ends");
    // stop motor
    digitalWrite(motorPinOut, HIGH);
}

String millisToTime(unsigned long milliseconds){
    int seconds = (int) (milliseconds / 1000) % 60 ;
    int minutes = (int) ((milliseconds / (1000*60)) % 60);
    int hours   = (int) ((milliseconds / (1000*60*60)) % 24);
    String timeString="";
    timeString=timeString+hours+":"+minutes+":"+seconds;
    return timeString;
}
void printOuput(String msg){
    Serial.print(msg+"\n");
}
