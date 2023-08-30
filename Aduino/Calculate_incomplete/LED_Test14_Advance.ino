// 1000개의 계산을 받아낼 수 있는 계산기
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <string.h>
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

LiquidCrystal_I2C lcd(0x27,20,4);

// 내가 만든 변수들
String Number;         // 키패드에 치는거 받을 변수
int count = 0;         // 연산자가 들어왔을 때 카운트
int Array[1000];       // 계산 할 수들
char Operator[1000];   // 연산자가 뭐 들어왔는지 저장할 변수 
double Result = 0;     // 계산한 결과값을 나타낼 변수


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

  // 커스텀키에 값이 들어와야 로직 시작
  if(customKey != NULL)
  {
    // Number 라는 스트링에 숫자받기
    if(customKey != '+' && customKey != '-' && customKey != '*' && customKey != '/' && customKey != '=' && customKey != 'c')
    {
      Number += customKey;
      lcd.setCursor(0,0);
      lcd.print(Number);
    }

    // (연산자, =) 을 받았을 때
    else if(customKey == '+' || customKey == '-' || customKey == '*' || customKey == '/' || customKey == '=')
    {
      lcd.clear();
      lcd.print(customKey);

      // Number에 숫자 받기 AND Operator에 (연산자와 =) 받기
      count++;
      for(int i=0; i<count; i++)
      {
        if(Array[i] == 0)  // Null이 아니라 0 일 수도 있음 ** Operator도 
        {
          Array[i]    = Number.toInt();
          Operator[i] = customKey;
          Number      = "";
        }
      }

      // 첫 번째 수는 Result에 저장하기
      if(count <= 1)
      {
        Result = Array[0];
        Serial.println(Result);
        return;
      }
      // '=' 이라는 값을 입력받으면 한꺼번에 계산 시작
      if(customKey == '=')
      {
        lcd.clear();
        for(int i=0; i<count; i++)
        {
          switch(Operator[i])
          {
            case '+':
              Result += Array[i+1];
              break;
            case '-':
              Result -= Array[i+1];
              break;
            case '*':
              Result *= Array[i+1];
              break;
            case '/':
              Result /= Array[i+1];
              break;
            case '=':
              lcd.setCursor(0,0);
              lcd.print(Result);
              for(int i=0; i<count; i++)
              {
                Array[i]    = NULL;
                Operator[i] = NULL;
              }
              Number = Result;
              count  = 0;
              break;
          }
        }
      }
    }

    // 입력키가 c 일 경우     
    else if(customKey == 'c')
    {
      for(int i=0; i< count; i++)
      {
        Array[i]    = NULL;
        Operator[i] = NULL;
      }
      Result = 0;
      count  = 0;
      Number = "";
      lcd.init();
    }
  }
}





