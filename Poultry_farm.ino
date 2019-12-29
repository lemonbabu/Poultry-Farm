
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int ledPin = A5, fanPin = A4, tmpPin = A0, mtrPin = A1;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
unsigned long crntTime, preTime;
int cel;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2); 
  pinMode(ledPin,OUTPUT);
  pinMode(fanPin,OUTPUT);
  pinMode(tmpPin,INPUT);
  pinMode(mtrPin,OUTPUT);
  preTime = millis();
  Serial.begin(9600);
}

void loop() {

  //Tempature sensor reading code
  int tmp = analogRead(tmpPin);
  float mv = ( tmp/1024.0)*5000;
  cel = mv/10;
  Serial.print("TEMPRATURE = "); 
  Serial.println(cel);/// just for show data in serial monitor

  if(cel > 15){
    digitalWrite(ledPin,LOW);
    if(cel > 20)
      analogWrite(fanPin,800);
    else if(cel > 25)
      analogWrite(fanPin, 1000);
    else 
      analogWrite(fanPin, 500);
  }
  else{
    digitalWrite(ledPin,HIGH);
    analogWrite(fanPin,LOW);
  }

//time calculation for auto food servicing 
  crntTime = millis();
  if(crntTime - preTime > 12000){
    analogWrite(mtrPin, 1000);
    delay(1000);
    preTime = crntTime;
  }
  else 
    analogWrite(mtrPin, LOW);

    lcd.clear();  
    Display();
    delay(2000);
}


void Display(){
    
  // set the cursor to (0,0):
  lcd.setCursor(0, 0);
 // lcd.autoscroll(); // set the display to automatically scroll:
  lcd.print("   CSE, DUET");

  // set the cursor to (16,1):
  lcd.setCursor(0, 1);
  lcd.noAutoscroll();
  lcd.print("Teamp = ");
  lcd.print(cel);
  lcd.print("'C");
}
