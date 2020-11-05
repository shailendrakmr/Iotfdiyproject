#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#define temp 8
const int buzzerPin = 13;
const int flamePin = 10;

const int lm35_pin = A0;  // LM35 O/P pin
int Flame = HIGH;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(buzzerPin, OUTPUT);
  pinMode(temp,OUTPUT);
  pinMode(flamePin, INPUT);
}

void loop() {

  // temperature sensor
  tempSensor();
  delay(1000);

  // flame/fire sensor
  flameSensor();
  delay(1000);

  // PIR motion detector

 
}

void flameSensor() {
  Flame = digitalRead(flamePin);
  if (Flame == LOW)
  {
    Serial.println("        ALERT !    Fire In the House  !");
    lcd.println("Fire Alert !");
    digitalWrite(buzzerPin, HIGH);
    delay(1000);
    lcd.clear();
  }
  else
  {
    Serial.println("NO fire");
    lcd.println("No worries");
    digitalWrite(buzzerPin, LOW);
    delay(1000);
    lcd.clear();
  }
}

void tempSensor() {
  int temp_adc_val;
  float temp_val;
  temp_adc_val = analogRead(lm35_pin);  // Read Temperature
  temp_val = (temp_adc_val * 4.88); // Convert adc value to equivalent voltage
  temp_val = (temp_val / 10); // LM35 gives output of 10mv/°C

  Serial.print("Temperature = ");
  Serial.print(temp_val);
  Serial.print(" °C\n");
  if(temp_val >27){
    digitalWrite(buzzerPin, HIGH);
    lcd.println("Fire !!");
    delay(1000);
    lcd.clear();
    
    }

  lcd.print("Temp. = ");
  lcd.print(temp_val);
  lcd.setCursor(0, 1);
  lcd.print("°C");
  delay(1000);
  lcd.clear();

}
