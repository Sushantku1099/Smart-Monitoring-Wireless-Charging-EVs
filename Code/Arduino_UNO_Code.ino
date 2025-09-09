#include <LiquidCrystal.h>
int Contrast=75;
// LCD module connections (change these according to your setup)
const int rs = 12, en = 11, d4 = 7, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int IR = 8;     //Station detector
int Relay = 9;   //Station Coil


void setup() {
pinMode (IR,INPUT);
pinMode (Relay,OUTPUT);
Serial.begin(9600);
// Set up the LCD number of columns and rows
analogWrite(6,Contrast);
lcd.begin(16, 2);

// Print a message to the LCD
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Charg. P.f. Status:");}

void loop() {
 int Station = digitalRead(IR); 
 
if (Station==0){
  digitalWrite(Relay,LOW);//here we use(Coil_A,LOW)because Relay are active low electromagnetic switch.
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Platform is ON");
  
  Serial.println("platfrom is ON");
  delay(1000);} 
  
else {digitalWrite(Relay,HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("platfrom is OFF");

  Serial.println("platfrom is OFF");
  delay(1000);}}
