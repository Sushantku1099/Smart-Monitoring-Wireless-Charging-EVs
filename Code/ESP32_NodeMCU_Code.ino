#define BLYNK_PRINT Serial
#include "EmonLib.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

EnergyMonitor emon;
 
#define vCalibration 83.3
#define currCalibration 0.50
 
BlynkTimer timer;

char auth[] = "EFwDlkjugUKmZxmGf2hd2s3WdbIhNRgL";
char ssid[] = "Sushant's_wifi";
char pass[] = "Sushant@12";

float kWh = 0;
unsigned long lastmillis = millis();
 
void myTimerEvent()
{
  emon.calcVI(20, 2000);
  kWh = kWh + emon.apparentPower * (millis() - lastmillis) / 3600000000.0;
  yield();
  Serial.print("Vrms: ");
  Serial.print(emon.Vrms, 2);
  Serial.print("V");
 
  Serial.print("\tIrms: ");
  Serial.print(emon.Irms, 4);
  Serial.print("A");
 
  Serial.print("\tPower: ");
  Serial.print(emon.apparentPower, 4);
  Serial.print("W");
 
  Serial.print("\tkWh: ");
  Serial.print(kWh, 5);
  Serial.println("kWh");
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vrms:");
  lcd.print(emon.Vrms, 2);
  lcd.print("V");
  
  lcd.setCursor(0, 1);
  lcd.print("Irms:");
  lcd.print(emon.Irms, 4);
  lcd.print("A");
  delay(2500);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Power:");
  lcd.print(emon.apparentPower, 4);
  lcd.print("W");
  
  lcd.setCursor(0, 1);
  lcd.print("kWh:");
  lcd.print(kWh, 4);
  lcd.print("W");
  delay(2500);

  lastmillis = millis();
 
  Blynk.virtualWrite(V0, emon.Vrms);
  Blynk.virtualWrite(V1, emon.Irms);
  Blynk.virtualWrite(V2, emon.apparentPower);
  Blynk.virtualWrite(V3, kWh);
}
 
void setup()
{
 Serial.begin(9600);
 Blynk.begin(auth, ssid, pass);
 Wire.begin();
 lcd.begin(LCD_COLUMNS, LCD_ROWS);  // Initialize the LCD with 16 columns and 2 rows
 lcd.backlight();  // Turn on the backlight
 lcd.setCursor(0, 0);  // Set the cursor to the first column, first row
 lcd.print("BMS Status: ");
 delay(3000);
 lcd.clear();
 
 emon.voltage(35, vCalibration, 1.7); // Voltage: input pin, calibration, phase_shift
 emon.current(34, currCalibration); // Current: input pin, calibration.
 
 timer.setInterval(5000L, myTimerEvent);}

void loop()
{
  Blynk.run();
  timer.run();
}
