// 두 개의 수를 입력 받고 계산하기
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'+','1','2','3'},
  {'-','4','5','6'},
  {'*','7','8','9'},
  {'/','c','0','='}
};

byte rowPins[ROWS] = {30, 32, 34, 36};
byte colPins[COLS] = {28, 26, 24, 22};
char customKey;
Keypad customKeypad = Keypad(makeKeymap(hexaKeys),
rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// 숫자 두 개를 받는 변수
int Num1 = 0;
int Num2 = 0;

// lcd칸이 가로가 16칸이므로 lcd화면에 몇번째 칸에 나타낼지 카운트를 하는 변수
int can = 0;

// '+', '-', '*', '/' 를 받을 변수
char Modify[1];

// '=' 을 받을 변수
char End[1];

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

  // 키패드에 +, -, *, / 중 하나를 받으면 Modify 변수에 담을 로직 
  if(customKey == '+'|| customKey == '-'|| customKey == '*'|| customKey == '/')
  {
    if(customKey == '+')
    {
      Modify[0] = customKey;
      lcd.setCursor(can,1);
      lcd.print('+');
      can++;
    }
    else if(customKey == '-')
    {
      Modify[0] = customKey;
      lcd.setCursor(can,1);
      lcd.print('-');
      can++;      
    }
    else if(customKey == '*')
    {
      Modify[0] = customKey;
      lcd.setCursor(can,1);
      lcd.print('*');
      can++;      
    }
    else if(customKey == '/')
    {
      Modify[0] = customKey;
      lcd.setCursor(can,1);
      lcd.print('/');
      can++;      
    }
  }

  // 키패드에 = 이라는 값을 받으면 End 변수에 담을 로직
  if(customKey == '=')
  {
    End[0] = customKey;
    lcd.setCursor(can,1);
    lcd.print('=');
    can++;     
  }

  // 키패드에 c 라는 값을 받으면 lcd화면도 변수도 모두 리셋하는 로직
  if(customKey == 'c')
  {
    Num1 = 0;
    Num2 = 0;
    can =  0;
    Modify[0] = NULL;
    End[0] = NULL;
    lcd.init();
  }

  /*첫 번째 수를 받을 로직 (1. +,-,*,/ 를 받기 전까지 숫자 입력가능 - 하나라도 받으면 건너띔
                           2. 키패드에 값을 입력해야만 로직을 탐   - 루프가 한 번 돌면 customKey값은 NULL이 되는데 
                                                                    customKey != NULL을 넣지 않으면 customKey 값은 NULL 상태로
                                                                    계속 현재 로직을 타게 됨. 그래서 숫자를 하나만 넣어도
                                                                    Num1에 값이 생기면서 현재 if문을 계속 타니까 숫자가 무한히 증가
                           3. c는 모든것을 리셋해야 하는 키이기 때문)  */
  if(Modify[0] == NULL && customKey != NULL && customKey != 'c')
  {
    Num1 = Num1 * 10 + customKey-48;
    lcd.setCursor(can,1);
    lcd.print(customKey);
    can++;
  }

  /*두 번째 수를 받을 로직(1. (+,-,*,/) 를 입력 받고 '='을 입력받지 않았을 때 두 번째 수 입력 가능한 로직
                          2. 첫 번째 수를 받을 로직의 2번 째 이유와 마찬가지로 customKey != NULL 넣어줘야 함
                          3. 하지만 현재 else if 문은 (+,-,*,/) 를 입력받으면, 4개의 연산자도 현재 로직에 들어갈 수 있음
                             - 그래서 else if문 안에 if문을 넣어서, customKey 값이 4개의 연산자 중 하나라도 있으면 걸러주게
                               해서 숫자만 입력 가능하게 함 
                             - if문이 없고 else의 로직만 있으면 customKey값에 4개의 연산자 중 하나의 아스키코드 값이 들어가서 꼬임*/
  else if(Modify[0] != NULL && End[0] == NULL && customKey != NULL)
  {
    if(customKey == '+'|| customKey == '-'|| customKey == '*'|| customKey == '/')
    {
      
    }
    else
    {
      Num2 = Num2 * 10 + customKey-48;
      lcd.setCursor(can,1);
      lcd.print(customKey);
      can++;
    }
  }

  // 마지막으로 '=' 이라는 값을 받으면 식은 완성이 되었으니 계산 로직 시작
  if(End[0] != NULL)
  {
    if(Modify[0] == '+')
    {
      lcd.setCursor(5,0);
      lcd.print("Duhagi");

      lcd.setCursor(0,1);
      lcd.print(Num1);
      lcd.print(" + ");
      lcd.print(Num2);
      lcd.print(" = ");

      lcd.print(Num1+Num2);
    }
    else if(Modify[0] == '-')
    {
      lcd.setCursor(5,0);
      lcd.print("Bbaegi");

      lcd.setCursor(0,1);
      lcd.print(Num1);
      lcd.print(" - ");
      lcd.print(Num2);
      lcd.print(" = ");

      lcd.print(Num1-Num2);
    }
    else if(Modify[0] == '*')
    {
      lcd.setCursor(5,0);
      lcd.print("Gobhagi");

      lcd.setCursor(0,1);
      lcd.print(Num1);
      lcd.print(" * ");
      lcd.print(Num2);
      lcd.print(" = ");

      lcd.print(Num1*Num2);     
    }
    else if(Modify[0] == '/')
    {
      lcd.setCursor(5,0);
      lcd.print("Nanugi");

      lcd.setCursor(0,1);
      lcd.print(Num1);
      lcd.print(" / ");
      lcd.print(Num2);
      lcd.print(" = ");

      lcd.print(float(Num1)/Num2);      
    }
  }
}