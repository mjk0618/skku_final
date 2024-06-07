int pirPin = 9;  // PIR 센서 핀 번호
int pirState = LOW;  // 초기 상태를 LOW로 설정
int val = 0;  // 센서 값을 저장할 변수

void setup() {
  pinMode(pirPin, INPUT);  // PIR 센서 핀을 입력 모드로 설정
  Serial.begin(9600);  // 시리얼 통신 시작
}

void loop() {
  val = digitalRead(pirPin);  // PIR 센서 값을 읽음

  if (val == HIGH) {  // 동작이 감지되었을 때
    if (pirState == LOW) {
      // 상태가 LOW에서 HIGH로 변경될 때만 메시지 출력
      Serial.println("Motion detected");
      pirState = HIGH;  // 상태를 HIGH로 변경
    }
  } else {
    if (pirState == HIGH) {
      // 상태가 HIGH에서 LOW로 변경될 때
      pirState = LOW;  // 상태를 LOW로 변경
    }
  }
}
