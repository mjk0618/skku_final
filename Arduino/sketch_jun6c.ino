#include <Servo.h>

int pirPin = 9;  // PIR 센서 핀 번호
int servoPin = 2;  // 서보 모터 핀 번호
Servo myservo;  // 서보 모터 객체 생성

int pirState = LOW;  // 초기 상태를 LOW로 설정
int val = 0;  // 센서 값을 저장할 변수

void setup() {
  pinMode(pirPin, INPUT);  // PIR 센서 핀을 입력 모드로 설정
  myservo.attach(servoPin);  // 서보 모터 핀 설정
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

  // 시리얼 통신으로부터 데이터를 읽어옴
  if (Serial.available() > 0) {
    int command = Serial.parseInt();  // 시리얼로부터 정수 값 읽기
    if (command == 1) {
      myservo.write(90);  // 서보 모터 90도 회전
    } else if (command == 0) {
      myservo.write(0);  // 서보 모터 0도 회전
    }
  }
}
