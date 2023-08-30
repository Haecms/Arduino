// 가로등처럼 밝기에 따라 LED켜지게 함(조도센서)
void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  Serial.println(analogRead(A5));
  delay(100);
  if(analogRead(A5)>=170){
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
  }
  else if(analogRead(A5) >= 121 && analogRead(A5)<=169){
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
  }
  else if(analogRead(A5)<=120){
    digitalWrite(2, HIGH);
    digitalWrite(4, HIGH); 
  }

}

