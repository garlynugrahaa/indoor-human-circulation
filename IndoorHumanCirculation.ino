/*
Project Name	: Indoor Human Circulation
Author        : Garly Nugraha
Major         : Computer and Informatics Engineering
College       : Bandung State Polytechnic
Date			    : May 11, 2023
*/

#include <LiquidCrystal_I2C.h>

#define TriggerPin1 10 // Pin 10
#define EchoPin1 11 // Pin 11
#define TriggerPin2 8 // Pin 8
#define EchoPin2 9 // Pin 9
#define BuzzerPin 12 // Pin 12

LiquidCrystal_I2C lcd(0x27, 16, 2);

bool isInside = false;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(TriggerPin1, OUTPUT);
  pinMode(EchoPin1, INPUT);
  pinMode(TriggerPin2, OUTPUT);
  pinMode(EchoPin2, INPUT);
  pinMode(BuzzerPin, OUTPUT);
  
  lcd.init();                     
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("Posisi Bayi");
}

void loop() {
  long Duration1, Distance1, Duration2, Distance2;

  // Measure the Distance with the Ultrasonic Sensor 1
  digitalWrite(TriggerPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin1, LOW);
  Duration1 = pulseIn(EchoPin1, HIGH);
  Distance1 = Duration1 / 29 / 2;

  // Measure the Distance with the Ultrasonic Sensor 2
  digitalWrite(TriggerPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin2, LOW);
  Duration2 = pulseIn(EchoPin2, HIGH);
  Distance2 = Duration2 / 29 / 2;

  // Prints the Distance Measured from Ultrasonic Sensor 1 to Serial Monitor
  Serial.print("Distance 1: ");
  Serial.print(Distance1);
  Serial.println(" cm");

  // Prints the Distance Measured from Ultrasonic Sensor 2 to Serial Monitor
  Serial.print("Distance 2: ");
  Serial.print(Distance2);
  Serial.println(" cm");

  if (Distance2 >= 15 && Distance2 <= 20 && Distance1 >= 15 && Distance1 <= 20) {
    lcd.setCursor(0, 1);
    lcd.print("Depan Pintu");

    digitalWrite(BuzzerPin, HIGH);
    delay(80);
    digitalWrite(BuzzerPin, LOW);
  } else if (!isInside && Distance2 >= 15 && Distance2 <= 20) {
    lcd.setCursor(0, 1);
    lcd.print("Luar Ruangan");

    digitalWrite(BuzzerPin, HIGH);
    delay(100);
    digitalWrite(BuzzerPin, LOW);

    isInside = true;
  } else if (isInside && Distance1 >= 15 && Distance1 <= 20) {
    lcd.setCursor(0, 1);
    lcd.print("Dalam Ruangan");

    isInside = false;
  }

  delay(100);
}