//캐서드 타입 공통 GND를 가지고 있따. COM 1, 2, 3, 4 가 GND랑 연결
//a = 40port // b = 41 // c = 42 // d = 43 // e = 44 // f = 45 // g = 46 
int Pins[] = {52, 50, 48, 46, 44, 42, 40};

void setup() 
{
  for(int i = 0; i<7; i++)
  {
    pinMode(Pins[i], OUTPUT);
  }

}

void loop() 
{
  for(int i = 0 ; i<7; i++)
  {
    digitalWrite(Pins[i], HIGH);   
  }
}