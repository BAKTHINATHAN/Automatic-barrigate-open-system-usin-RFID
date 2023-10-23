#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define trigPin1 6
#define echoPin1 7
#define trigPin2 4
#define echoPin2 5
#define A ("Gate close off")
String UID = "07 DA 60 52";
byte lock = 0;


Servo servo1;
Servo servo2;
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rfid(SS_PIN, RST_PIN);
long duration1, duration2;
int distance1, distance2;


void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  Serial.begin(9600);
  servo1.write(1);
  servo2.write(89);
  lcd.init();
  lcd.backlight();
  servo1.attach(3);
  servo2.attach(2);
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
  lcd.setCursor(4, 0);
  lcd.print("Advance");
  lcd.setCursor(0, 1);
  lcd.print("Barricade system");

  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning");
  Serial.print("NUID tag is :");
  String ID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    lcd.print(".");
    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
    delay(0);
  }
  ID.toUpperCase();
  if (ID.substring(1) == UID) {
      distance1 = measureDistance(trigPin1, echoPin1);

      // Measure distance using the second ultrasonic sensor
      distance2 = measureDistance(trigPin2, echoPin2);

      // Print distances to Serial Monitor
      Serial.print("Distance 1: ");
      Serial.print(distance1);
      Serial.print(" cm | Distance 2: ");
      Serial.print(distance2);
      Serial.println(" cm");

      if (distance1 > 8 and distance2 > 8) {
        servo1.write(92);
        servo2.write(1);
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("Ambulance is");
        lcd.setCursor(4,1);
        lcd.print("comming");
        delay(1000);
        lcd.clear();
        for (int B = 5; B >= 1; B--) {
          lcd.setCursor(0,0);
          lcd.print(A);
          lcd.setCursor(7,1);
          lcd.print(B);
          delay(1000);
          lcd.clear();
        }
          servo1.write(1);
          servo2.write(89);
      }
  } 
  else {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" ");
      delay(0);
      lcd.clear();
  }
  
}
int measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  return pulseIn(echoPin, HIGH) * 0.0343 / 2;
}