#include <Servo.h>

Servo myservo;  // 서보 모터 객체 생성
int servoPin = 2;  // 서보 모터 핀 번호
int angle = 0;  // 초기 각도
int angleIncrement = 10;  // 각도 증가량
int delayTime = 1000;  // 시간 지연 (밀리초)

void setup() {
  myservo.attach(servoPin);  // 서보 모터 핀 설정
}

void loop() {
  // 서보 모터를 현재 각도로 회전
  myservo.write(angle);
  
  // 각도 증가
  angle += angleIncrement;
  
  // 각도가 0도 이하 또는 180도 이상이면 방향을 반대로 전환
  if (angle >= 180 || angle <= 0) {
    angleIncrement = -angleIncrement;
  }
  
  // 지연 시간 동안 대기
  delay(delayTime);
}
