// 한자릿수만 더하기 빼기 나누기 곱하기
// 아두이노 LCD 숫자 출력하기
//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;

char array[3];
int check = 0;

char hexaKeys[ROWS][COLS] = {
  {'+','1','2','3'},
  {'-','4','5','6'},
  {'*','7','8','9'},
  {'/','0','0','0'}
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
}


void loop()
{
  customKey = customKeypad.getKey();
  if(customKey)
  {
    Serial.println(customKey);
  }

  for(int i=0; i<3; i++)
  {
    if(array[i] == NULL)
    {
      array[i] = customKey;
      break;
    }
  }

  if(array[2] != NULL)
  {
    lcd.init();

    if(array[1] == '+')
    {
      lcd.setCursor(6,0);
      lcd.print("Add");

      lcd.setCursor(4,1);
      lcd.print(array[0]);
      lcd.print(" + ");
      lcd.print(array[2]);
      lcd.print(" = ");

      lcd.print((array[0]-'0') + (array[2]-'0'));
    }

    else if(array[1] == '-')
    {
      lcd.setCursor(5,0);
      lcd.print("Minus");

      lcd.setCursor(4,1);
      lcd.print(array[0]);
      lcd.print(" - ");
      lcd.print(array[2]);
      lcd.print(" = ");

      lcd.print((array[0]-'0') - (array[2]-'0'));      
    }

    else if(array[1] == '*')
    {
      lcd.setCursor(1,0);
      lcd.print("Multiplication");

      lcd.setCursor(4,1);
      lcd.print(array[0]);
      lcd.print(" * ");
      lcd.print(array[2]);
      lcd.print(" = ");

      lcd.print((array[0]-'0') * (array[2]-'0'));
    }
    
    else if(array[1] == '/')
    {
      lcd.setCursor(5,0);
      lcd.print("Divide");

      lcd.setCursor(4,1);
      lcd.print(array[0]);
      lcd.print(" / ");
      lcd.print(array[2]);
      lcd.print(" = ");

      lcd.print((array[0]-'0') / float((array[2]-'0')));      
    }

    check = 0;
    for(int i=0; i<3; i++)
    {
      array[i] = NULL;
    }
  }
}





