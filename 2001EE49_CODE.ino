#include <Servo.h>
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 0;
const int colorG = 0;
const int colorB = 255;
#define echoPin 4
#define trigPin 5
Servo Myservo;
Servo myservo;
#define sensor 6
int pos;
long duration;
int distance;
int LDR[] = {A0, A1, A2};
int laser[] = {8, 9, 10};
void setup()
{
  Myservo.attach(3);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin(16, 2);

  lcd.setRGB(colorR, colorG, colorB);

  lcd.print("Count: ");
  lcd.setCursor(8, 0);
  lcd.print('0');
  lcd.setCursor(0, 1);
  lcd.print("Slots: ");

  delay(1000);
  for (int i = 0; i < 3; i++)
  {
    pinMode(LDR[i], INPUT);
  }

  for (int i = 0; i < 3; i++)
  {
    pinMode(laser[i], OUTPUT);
  }

  pinMode(sensor, INPUT);
  myservo.attach(11);
  Myservo.write(0);
  myservo.write(0);
  delay(1000);
}
int threshold = 100;
int count = 0;
void loop()
{

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  if (distance < 11 and count < 3)
  {
    count = count + 1;
    delay(100);
    Myservo.write(100);
    delay(1000);
    Myservo.write(0);
    lcd.setCursor(8, 0);
    lcd.print(count);
  }
  for (int j = 0; j < count; j++)
  {
    digitalWrite(laser[j], HIGH);
    int photores_val = analogRead(LDR[j]);
    if (photores_val < threshold)
    {
      lcd.setCursor(8 + 2 * j, 1);
      lcd.print(j + 1);
    }
    else
    {
      lcd.setCursor(8 + 2 * j, 1);
      lcd.print(' ');
    }
  }
  if (digitalRead(sensor) == HIGH)
  {
    if (count > 0)
    {
      myservo.write(100);
      delay(2000);
      myservo.write(0);
      count = count - 1;
      lcd.setCursor(8, 0);
      lcd.print(count);
      Serial.println(count);
      digitalWrite(laser[count], LOW);
      lcd.setCursor(8 + 2 * count, 1);
      lcd.print(' ');
    }
  }
  delay(100);
}
