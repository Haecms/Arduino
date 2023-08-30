int keyData = 0;
int inPin = 10;
void setup() {
  Serial.begin(115200); // 통신 설정 근데 통신이 뭘까?
  pinMode(inPin, INPUT_PULLUP); // 풀업저항 사용 - 뭔 뜻인지 모름
  pinMode(2, OUTPUT);  // LED 핀 설정
}

void loop() {
  keyData = digitalRead(inPin); // 이것도 뭔지 모름
  delay(200); // 0.2초 정도 뒤에 출력하게 해줌(디바운딩)
  Serial.println(keyData); // keyData 값을 출력해줌
  if(keyData == LOW){     // keyData 값이 0이면
    digitalWrite(2, HIGH); // LED 13번 핀에 1의 값을 준다.
    delay (1000);
    digitalWrite(2, LOW);  // 다시 LED 13번 핀에 0의 값을 준다.
  } 
}
