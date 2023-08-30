// 아두이노 LCD 숫자 출력하기
//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','a','b'},
  {'c','d','e','f'}
};

byte rowPins[ROWS] = {30, 32, 34, 36};
byte colPins[COLS] = {28, 26, 24, 22};
char customKey;
Keypad customKeypad = Keypad(makeKeymap(hexaKeys),
rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();


  //lcd.setCursor(3,0);
  //lcd.print("Hello, world!");
  //lcd.setCursor(2,1);
  //lcd.print("Ywrobot Arduino!");
   //lcd.setCursor(0,2);
  //lcd.print("Arduino LCM IIC 2004");
   //lcd.setCursor(2,3);
  //lcd.print("Power By Ec-yuan!");
  lcd.setCursor(5,0);
  lcd.print("Gugudan");
}


void loop()
{
  customKey = customKeypad.getKey();
  if(customKey)
  {
    lcd.init();
    Serial.println(customKey);
    for(int j=1; j<10; j++)
    {
      lcd.setCursor(5,0);
      lcd.print("Gugudan");

      lcd.setCursor(4,1);
      lcd.print(customKey);
      lcd.print(" * ");
      lcd.print(j);
      lcd.print(" = ");

      lcd.print((customKey-48)*j);
      delay(1000);
    }
  }




}

