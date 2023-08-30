const int buzzerPin = 9;

void setup() {
  // 피에조 부저 핀을 출력으로 설정
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // 주의 및 경고 멜로디 연주
  playWarningMelody();
  delay(2000); // 2초 대기
}

// 주의 및 경고 멜로디 연주 함수
void playWarningMelody() {
  // 멜로디를 표현하는 음계의 주파수 배열
  int melody[] = {
    523, 659, 783, 932, 1047
  };
  
  // 음계에 해당하는 재생 시간 배열 0.2s 텀
  int noteDuration[] = {
    200, 200, 200, 200, 200
  };

  // 멜로디 연주
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    int duration = noteDuration[i];
    tone(buzzerPin, melody[i], duration);
    delay(duration);
  }

  // 부저 끄기
  noTone(buzzerPin);
}