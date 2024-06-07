#include <Servo.h>
#include <SoftwareSerial.h>

// 핀 설정
const int pirPin = 2;
const int servoPin = 9;
const int rxPin = 10;  // 아두이노의 RX 핀
const int txPin = 11;  // 아두이노의 TX 핀

// 상태 변수
int pirState = LOW;
int val = 0;

// 서보 모터 설정
Servo myservo;

// SoftwareSerial 설정
SoftwareSerial mySerial(rxPin, txPin);  // RX, TX

void setup() {
  // 핀 모드 설정
  pinMode(pirPin, INPUT);
  myservo.attach(servoPin);

  // 하드웨어 및 소프트웨어 시리얼 통신 시작
  Serial.begin(9600);
  mySerial.begin(9600);

  // 서보 모터 초기 위치 설정 (문 열기 상태)
  myservo.write(90);
}

void loop() {
  // PIR 센서 입력 읽기
  val = digitalRead(pirPin);

  if (val == HIGH) {
    if (pirState == LOW) {
      // 사람이 감지됨
      Serial.println("Motion detected!");
      mySerial.println("Motion detected!"); // 라즈베리 파이로 신호 전송
      pirState = HIGH;
    }
  } else {
    if (pirState == HIGH) {
      // 사람이 감지되지 않음
      Serial.println("Motion ended!");
      mySerial.println("Motion ended!"); // 라즈베리 파이로 신호 전송
      pirState = LOW;
    }
  }

  // 라즈베리 파이로부터 얼굴 인식 결과 수신
  if (mySerial.available()) {
    char command = mySerial.read();
    if (command == 'L') {
      // 치매 노인으로 인식됨 -> 문 잠금
      myservo.write(0);
      Serial.println("Door locked!");
    } else if (command == 'U') {
      // 치매 노인이 아님 -> 문 열기
      myservo.write(90);
      Serial.println("Door unlocked!");
    }
  }

  // 문이 잠긴 상태에서 일정 시간 동안 사람이 인식되지 않으면 문 열기
  if (pirState == LOW && myservo.read() == 0) {
    delay(10000); // 10초 대기
    if (digitalRead(pirPin) == LOW) {
      myservo.write(90); // 문 열기
      Serial.println("Door unlocked due to inactivity!");
    }
  }
}
