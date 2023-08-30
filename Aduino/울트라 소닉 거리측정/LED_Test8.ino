// 자동차 뒤에 센서 울리는거처럼 트리거에서 소리를 내보내고 에코핀에 소리를 받아와서 얼마만큼 차이가 나는지 알려줌
int trigPin = 3;
int echoPin = 5;
int Sori[3] = {100, 300, 500};
void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, HIGH);  // 내가 알고 있는게 트리거가 시작해서 어떤 벽에 부딪히고 다시 돌아온다.
  delayMicroseconds(10);        // 그런데 여기있는 delayMicroseconds는 무엇인가? 왜 필요한가??
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH); // 트리거핀이 출발해서 벽에 부딪히고 돌아와서 pin에 들어오기까지 시간을 측정.
  long distance = ((float)(duration*340)) /10000 / 2; // 위의 시간을 왜 곱하기 340하는지 왜 나누기 10000을 하는지. 외워야 하는 식인가?

  Serial.print(distance);
  Serial.println(" cm");

  delay(200);

  if(distance<=30 && distance>=21){
    tone(7, Sori[0]);
    delay(200);
    noTone(7);
  }
  else if(distance>=11 && distance<=20){
    tone(7, Sori[1]);
    delay(100);
    noTone(7);
  }
  else if(distance<=10){
    tone(7, Sori[2]);
    delay(30);
    noTone(7);
  }
}
