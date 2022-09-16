const int waterSens = A0;//define water sensor to pin A0
const int speaker = 8;//define speaker to pin 8
int SensorValue;//create sensor data variable

void setup() {
  Serial.begin(9600);

pinMode(speaker, OUTPUT);//set speaker as an output

pinMode(waterSens, INPUT); //set water sensor as an input         
    
}

void loop() {
 
  int sensorValue = analogRead(waterSens);//read the water sensor value
if (sensorValue >= 50) {
      Serial.println('Rain Alert');
      tone(speaker, 800, 800);
      delay(200);
      tone(speaker, 600, 800);
      delay(200);
     }//if the sensor senses water then play an alarm
}

 
