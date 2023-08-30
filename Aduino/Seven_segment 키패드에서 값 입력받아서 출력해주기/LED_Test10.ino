// 키패드 입력시 7세그먼트 숫자 나옴
#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','a','b'},
  {'c','d','e','f'}
};

int led[7] = {4, 5, 12, 11, 10, 3, 2};
char led2[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
int output[16][7] = {
  {0, 0, 0, 0, 0, 0, 1}, // 0
  {1, 0, 0, 1, 1, 1, 1}, // 1
  {0, 0, 1, 0, 0, 1, 0}, // 2
  {0, 0, 0, 0, 1, 1, 0}, // 3
  {1, 0, 0, 1, 1, 0, 0}, // 4
  {0, 1, 0, 0, 1, 0, 0}, // 5
  {0, 1, 0, 0, 0, 0, 0}, // 6
  {0, 0, 0, 1, 1, 1, 1}, // 7
  {0, 0, 0, 0, 0, 0, 0}, // 8
  {0, 0, 0, 0, 1, 0, 0}, // 9
  {0, 0, 0, 1, 0, 0, 0}, // A
  {0, 0, 0, 0, 0, 0, 0}, // B
  {0, 1, 1, 0, 0, 0, 1}, // C
  {1, 0, 0, 0, 0, 0, 0}, // D
  {0, 1, 1, 0, 0, 0, 0}, // E
  {0, 1, 1, 1, 0, 0, 0}, // F
};

byte rowPins[ROWS] = {30, 32, 34, 36};
byte colPins[COLS] = {28, 26, 24, 22};
char customKey;
Keypad customKeypad = Keypad(makeKeymap(hexaKeys),
rowPins, colPins, ROWS, COLS);


void setup()
{
  Serial.begin(9600);
  for(int i=0; i<7; i++)
  {
    pinMode(led[i], OUTPUT);
  }
}

void loop() {
  customKey = customKeypad.getKey();
  if(customKey)
  {
    Serial.println(customKey);
  }
  for(int i=0; i<16; i++)
  {
    if(customKey == led2[i])
    {
      for(int k=0; k<7; k++)
      {
        digitalWrite(led[k], output[i][k]);
      }
    }
  }
}
