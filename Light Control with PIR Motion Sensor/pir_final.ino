int buzzerPin = 8;                          //BUZZER INPUT PIN.
int ledPin = 13;                            //LED PIN.
int pirPin = A0;                            //MOTION SENSOR INPUT PIN.
int sensorValue = LOW;                      //DEFAULT SENSOR STATE.

void setup() {                              //INITIAL SETTINGS/ASSIGNMETN.
  pinMode(buzzerPin, OUTPUT);               //SET BUZZER AS OUTPUT.
  pinMode(ledPin, OUTPUT);                  //SET LED AS OUTPUT.
  pinMode(pirPin, INPUT);                   //SET PIR AS INPUT.
}
void loop() {                               //COMMAND TO BE REPEATED.
  sensorValue = digitalRead(pirPin);        //READ PIR INPUT PIN.
  if ( sensorValue == HIGH) {               //IF MOTION IS DETECTED.
//    tone(buzzerPin, 200);                  //BUZZ THE BUZZER. 
    digitalWrite(ledPin, LOW);             //ON LED.
//    delay(3000);                             //TIME DIFFERENCE BETWEEN HIGH(ON)& LOW(OFF).
//    noTone(buzzerPin);                      //SILENT BUZZER.
//    digitalWrite(ledPin, HIGH);              //OFF LED.
//    delay(100);                             //TIME DIFFERENCE BETWEEN HIGH(ON)& LOW(OFF).
  }
  else {                                    //IF NO MOTION IS DETECTED.
//    noTone(buzzerPin);                      //SILENT THE BUZZER.
    digitalWrite(ledPin, HIGH);              //OFF LED.
  }
}
