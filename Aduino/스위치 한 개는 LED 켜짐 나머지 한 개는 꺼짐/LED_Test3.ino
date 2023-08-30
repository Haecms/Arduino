int keyData = 0;
int keyData2 = 0;
int inPin = 10;
int inPin2 = 12;
void setup() {
  Serial.begin(115200); // 통신 설정 근데 통신이 뭘까?
  pinMode(inPin, INPUT_PULLUP); // 풀업저항 사용 - 뭔 뜻인지 모름
  pinMode(inPin2, INPUT_PULLUP);
  pinMode(2, OUTPUT);  // LED 핀 설정
}

void loop() {
  keyData = digitalRead(inPin); // 이것도 뭔지 모름
  keyData2 = digitalRead(inPin2);

  Serial.println(keyData); // keyData 값을 출력해줌
  Serial.println(keyData2);

  if(keyData == LOW){     // keyData 값이 0이면
    digitalWrite(2, HIGH); // LED 13번 핀에 1의 값을 준다.
  }
  if(keyData2 == LOW){
    digitalWrite(2,LOW);
  }

}
