#include <DallasTemperature.h>
#include <OneWire.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define ONE_WIRE_BUS_1 5
#define ONE_WIRE_BUS_2 9
#define RELAY_PIN_BOILER 13
#define RELAY_PIN_CALDAIA 10
#define LED_PIN_BOILER_1 11
#define LED_PIN_BOILER_2 6
#define TEMPERATURE_TRIGGER_BOILER_1 80
#define HYSTERESIS 2

#define ARROW_ICON 0

// Define LCD properties
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

OneWire oneWire1(ONE_WIRE_BUS_1);
DallasTemperature sensors1(&oneWire1);
OneWire oneWire2(ONE_WIRE_BUS_2);
DallasTemperature sensors2(&oneWire2);

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

int luminosita = 0;  // valore del fotodiodo, più è alto meno luce rileva (scala 0, 1023)
int luce = 1017;     // valore a cui si accende LCD

byte freccia [8] = { // pixel modificato
  0B00011,
  0B00110,
  0B01100,
  0B11111,
  0B11111,
  0B01100,
  0B00110,
  0B00011
};

void setup() {
  pinMode(RELAY_PIN_BOILER, OUTPUT);
  pinMode(RELAY_PIN_CALDAIA, OUTPUT);
  pinMode(LED_PIN_BOILER_1, OUTPUT);
  pinMode(LED_PIN_BOILER_2, OUTPUT);
  
  digitalWrite(RELAY_PIN_BOILER, HIGH);
  digitalWrite(RELAY_PIN_CALDAIA, HIGH);
  
  lcd.begin(LCD_COLUMNS, LCD_ROWS);
  lcd.createChar(ARROW_ICON, freccia);
  lcd.setCursor(0, 0);
  lcd.print("BOILER1: ");
  lcd.setCursor(0, 1);
  lcd.print("BOILER2: ");

  // inserimento del carattere C
  lcd.setCursor (15, 0);
  lcd.print ("C");
  lcd.setCursor(15, 1);
  lcd.print ("C");
  
  Serial.begin(9600);
  Serial.print("inizio");
}

void loop() {
  sensors1.requestTemperatures();
  sensors2.requestTemperatures();

  float temperature_boiler1 = sensors1.getTempCByIndex(0);
  float temperature_boiler2 = sensors2.getTempCByIndex(0);

  luminosita = analogRead(A0);

  lcd.setCursor(8, 0);
  lcd.print("  "); // Clear previous temperature reading
  lcd.setCursor(8, 1);
  lcd.print("  "); // Clear previous temperature reading

  if (temperature_boiler1 >= TEMPERATURE_TRIGGER_BOILER_1 && digitalRead(RELAY_PIN_BOILER) == HIGH) {
    digitalWrite(RELAY_PIN_BOILER, LOW);
  } else if (temperature_boiler1 <= (TEMPERATURE_TRIGGER_BOILER_1 - HYSTERESIS) && digitalRead(RELAY_PIN_BOILER) == LOW) {
    digitalWrite(RELAY_PIN_BOILER, HIGH);
  }

  if (luminosita <= luce) {
    lcd.backlight();
  } else {
    lcd.noBacklight();
  }

  lcd.setCursor(10, 0);
  lcd.print(temperature_boiler1, 1); // Mostra una sola cifra decimale per le temperature
  lcd.setCursor(10, 1);
  lcd.print(temperature_boiler2, 1); // Mostra una sola cifra decimale per le temperature

  if (digitalRead(RELAY_PIN_BOILER) == HIGH) {
    lcd.setCursor(8, 0);
    lcd.write(ARROW_ICON); // Arrow on the first line when relay is LOW
    lcd.setCursor(8, 1);
    lcd.print(" "); // No arrow on the second line when relay is LOW
    Serial.print("c1");
  } else {
    lcd.setCursor(8, 0);
    lcd.print(" "); // No arrow on the first line when relay is HIGH
    lcd.setCursor(8, 1);
    lcd.write(ARROW_ICON); // Arrow on the second line when relay is HIGH
    Serial.print("c2");
  }

  // control LED for Boiler1 created by Matteo
    if (temperature_boiler1 > 70) {
    analogWrite(LED_PIN_BOILER_1, 75);
    Serial.print("c3");
  } else if (temperature_boiler1 < 70 && temperature_boiler1 > 50) {
    analogWrite(LED_PIN_BOILER_1, 75);
    delay(250);
    analogWrite(LED_PIN_BOILER_1, 0);
    delay (250);
    Serial.print("c4");
  } else {
    analogWrite(LED_PIN_BOILER_1, 75);
    delay(750);
    analogWrite(LED_PIN_BOILER_1, 0);
    delay (750);
    Serial.print("c5");
  }

    if (temperature_boiler2 > 70) {
    analogWrite(LED_PIN_BOILER_2, 75);
    Serial.print("c6");
  } else if (temperature_boiler2 < 70 && temperature_boiler2 > 50) {
    analogWrite(LED_PIN_BOILER_2, 75);
    delay(250);
    analogWrite(LED_PIN_BOILER_2, 0);
    delay (250);
    Serial.print("c7");
  } else {
    analogWrite(LED_PIN_BOILER_2, 75);
    delay(750);
    analogWrite(LED_PIN_BOILER_2, 0);
    delay (750);
    Serial.print("c8");
  }

  // Check Boiler1 temperature for relay connected to pin 10
  if (temperature_boiler1 > 50) {
    digitalWrite(RELAY_PIN_CALDAIA, HIGH);
    Serial.print("c9");
  } else if (temperature_boiler1 < 48) {
    digitalWrite(RELAY_PIN_CALDAIA, LOW);
    Serial.print("c10");
  }
  Serial.print("c11");
  temperature_boiler1=0;
  temperature_boiler2=0;
  Serial.print("\n");
  Serial.print(luminosita);
  Serial.print("\n");
  delay(100);
  Serial.print("fine");
  Serial.print("\n");
  Serial.print("\n");
}
