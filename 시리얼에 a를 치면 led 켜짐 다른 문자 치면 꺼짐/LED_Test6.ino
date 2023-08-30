// Serial Monitor에 a를 입력하면 불 들어오고 다른걸 입력하면 불이 꺼짐
void setup() {
  Serial.begin(9600);
  Serial.println("Serial Test!!");
  Serial.print("ECHO>> ");
  pinMode(2, OUTPUT);
}

void loop() {
  char data;
  if(Serial.available() > 0){ // 시리얼에 말을 걸었을 때
    data = Serial.read();
    if(data == 'a' || data =='A'){
    digitalWrite(2, HIGH);
    delay(150);
    }
    else{
    digitalWrite(2, LOW);
    delay(150);
    }


  }


}
