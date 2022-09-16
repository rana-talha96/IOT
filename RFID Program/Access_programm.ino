#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define LED_G 4
#define LED_R 5
#define BUZZER 2
MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo myServo;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  myServo.attach(3);
  myServo.write(0);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  Serial.println("Put Your Card to the Reader....");
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  Serial.print("UID Tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " H6" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message: ");
  content.toUpperCase();
  if (content.substring(1) == "53 75 62 53")
  {
    Serial.println("Autherized Access");
    Serial.println();
    delay(1000);
    digitalWrite(LED_G, HIGH);
    tone(BUZZER, 500);
    delay(300);
    noTone(BUZZER);
    myServo.write(180);
    delay(5000);
    myServo.write(0);
    digitalWrite(LED_G, LOW);
  }
  else {
    Serial.println("Access Denied");
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 300);
    delay(1000);
    digitalWrite(LED_R, LOW);
    noTone(BUZZER);
  }
}
