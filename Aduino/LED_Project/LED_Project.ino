// 시리얼 1 입력하면 3색 LED
// 시리얼 2 입력하면 피에조부저(음악)
// 시리얼 3 입력하면 UltraSonic(거리 비례 소리)
// 시리얼 4 입력하면 도어락(키패드를 이용)

// 표준 입출력 함수 엔터를 치면 개행값이 버퍼에 들어감;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
//#include <string.h>
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
Keypad customKeypad = Keypad(makeKeymap(hexaKeys),
rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 20, 4);
int data  = 0;      
int check = 0;
int Red   = 11;
int Green = 12;
int Blue  = 13;

int Buzor = 10;
int Melody[] = {784, 0, 659, 698, 783, 0, 659, 698, 783, 391, 440, 494, 523, 587, 659, 698, 659, 0, 523, 587, 659, 0, 329, 349, 392, 440, 392, 349, 392, 523, 494, 523};

int Triger = 9;
int Echo   = 8;

char customKey;   // 키패드에서 받는 값
char changeKey;   // 비밀번호 
String bimilBunho = "1234";
String changeBunho;
String ddulKi;

void setup() {
  Serial.begin(9600);
  pinMode(Red,    OUTPUT);
  pinMode(Green,  OUTPUT);
  pinMode(Blue,   OUTPUT);
  pinMode(Buzor,  OUTPUT);
  pinMode(Triger, OUTPUT);
  pinMode(Echo,   INPUT);
  Serial.println(" Mode : Serial Monitor");
  Serial.println("1. 3색 LED 시작");
  Serial.println("2. Music 시작");
  Serial.println("3. Ultra sensor 시작");
  Serial.println("4. Doorlock 시작");
}
void loop() {

  if(Serial.available() > 0)
  {
    check = Serial.read()-48;
    if(check != -38)
    {
      data = check;
      hello();
    }
  }

  // LED 3색 시작
  if(data == 1)
  {
    led_Light(Red, 1, Green, 0, Blue, 0);
    escape();
    if(data != 1)
    {
      led_Light(Red, 0, Green, 0, Blue, 0);
      hello();
      return;
    }
    delay(500);
    led_Light(Red, 0, Green, 1, Blue, 0);
    escape();
    if(data != 1)
    {
      led_Light(Red, 0, Green, 0, Blue, 0);
      hello();
      return;
    }
    delay(500);
    led_Light(Red, 0, Green, 0, Blue, 1);
    escape();
    if(data != 1)
    {
      led_Light(Red, 0, Green, 0, Blue, 0);
      hello();
      return;
    }
    delay(500);
    led_Light(Red, 0, Green, 0, Blue, 0);
  }

  // 캐논 변주곡 하이라이트 시작
  else if(data == 2)
  {
    for(int i=0; i<sizeof(Melody)/sizeof(Melody[0]); i++)
    {
      escape();
      if(data !=2)
      {
        hello();
        break;
      }
      tone(Buzor, Melody[i]);
      delay(200);
    }
    noTone(Buzor);
  }

  // 거리에 따른 소리 시작
  else if(data == 3)
  {
    digitalWrite(Triger, HIGH);
    delayMicroseconds(10);
    digitalWrite(Triger, LOW);

    long duration   = pulseIn(Echo, HIGH);
    double distance = (double(duration*340.0))/10000/2;

    Serial.print(distance);
    Serial.println(" cm");

    delay(200);

    if(distance<=30 && distance>=21){
      Sori(Buzor, 300, 800);
    }
    else if(distance>=11 && distance<=20){
      Sori(Buzor, 400, 500);
    }
    else if(distance<=10){
      Sori(Buzor, 500, 300);
    }
  }

  // 도어락 성공, 실패, 비밀번호 변경 가능
  else if(data == 4)
  {
    customKey = customKeypad.getKey();
    if(customKey)
    {
      Serial.println(customKey);
    }

    if(customKey != NULL)
    {
      if(changeKey == '*')
      {
        if(customKey != '=' && customKey != '*' && customKey != 'c') // 숫자를 입력하면
        {
          bimilBunho += customKey;
          return;
        }
        else if(customKey == '=')
        {
          changeBunho = "";
          changeKey = NULL;
          Serial.println(bimilBunho);
          Serial.println("비밀번호가 변경 완료되었습니다.");
          return;
        }
        else if(customKey == 'c')
        {
          bimilBunho = changeBunho;
          changeBunho = "";
          changeKey = NULL;
          Serial.println("비밀번호 변경을 취소하였습니다.");
          return;
        }
      }
      // 체인지 키를 * 받는 곳
      if(customKey == '*')
      {
        ddulKi = "";
        changeBunho = bimilBunho;
        bimilBunho = "";
        changeKey = '*';
        Serial.println(bimilBunho);
        Serial.println("비밀번호 변경을 시작합니다.");
      }
      
      if(customKey != '=' && customKey != '*')
      {
        ddulKi += customKey;
      }
      else if(customKey == '=' && ddulKi != ' ')
      {
        if(bimilBunho == ddulKi)
        {
          Serial.println("열렸습니다^^");
          ddulKi = "";
        }
        else if(bimilBunho != ddulKi)
        {
          Serial.println("나가라");
          ddulKi = "";
        }
      }
      if(customKey == 'c')
      {
        ddulKi = "";
      }
    }
  }
}

// 키보드 입력 시 안내 문구 함수
void hello()
{
  Serial.println(data);
  if(data == 1)
  {
    Serial.println("3색 LED 시작!");
  }
  else if(data == 2)
  {
    Serial.println("Music 시작!");
  }
  else if(data == 3)
  {
    Serial.println("Ultra sensor 시작!");
  }
  else if(data == 4)
  {
    Serial.println("Doorlock 시작! 비밀번호를 입력해주세요 ^^");
    ddulKi = "";
    changeBunho = bimilBunho;
  }
  else
  {
    Serial.println("종료하겠습니다.");
  }
}

// 로직 진행 중 시리얼 리드값 변화 생기면 받는 함수
void escape()
{
  if(Serial.available())
  {
    check = Serial.read()-48;
    if(check != -38)
    {
      data = check;
    }
  }
}

// led 불 관리
void led_Light(int Red, int red_light, int Green, int green_light, int Blue, int blue_light)
{
  digitalWrite(Red,   red_light);
  digitalWrite(Green, green_light);
  digitalWrite(Blue,  blue_light);
}


void Sori(int Buzor, int decibel, int latetime)
{
  tone(Buzor, decibel);
  delay(latetime);
  noTone(Buzor);
}

