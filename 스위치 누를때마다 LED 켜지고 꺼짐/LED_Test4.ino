// 스위치 하나로  한 번 누르면 켜지고 한 번 누르면 꺼지는 식
int keyData = 0;
int inPin = 10;
int Amuguna = 0;    // 카운트 만드는게 중요함

void setup() {
  Serial.begin(115200);
  pinMode(inPin, INPUT_PULLUP);
  pinMode(2, OUTPUT);
}

void loop() {
  keyData = digitalRead(inPin);

  Serial.println(keyData);

  if(keyData == 0){   //스위치를 눌렀을 때
    Amuguna++;
  }
  delay(200);
  if(Amuguna % 2 != 0){
    digitalWrite(2, HIGH);
  }
  else{
    digitalWrite(2, LOW);
  }




}
