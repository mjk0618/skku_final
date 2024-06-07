#include <Servo.h>

Servo myservo;
int pirPin = 2;
int servoPin = 9;
unsigned long lastMotionDetectedTime = 0;
const unsigned long motionTimeout = 10000; // 10 seconds

void setup() {
  pinMode(pirPin, INPUT);
  myservo.attach(servoPin);
  Serial.begin(9600);
  myservo.write(90); // 기본 상태를 "열림"으로 설정
}

void loop() {
  if (digitalRead(pirPin) == HIGH) {
    Serial.println("Motion detected");
    lastMotionDetectedTime = millis();
    delay(1000);  // Debounce delay
  }

  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); // 시리얼에서 데이터를 읽어 command에 저장
    if (command == "Unlock") {
      myservo.write(90); // 잠금 해제
    } else if (command == "Lock") {
      myservo.write(0);  // 잠금
    }
  }

  // 사람이 감지되지 않은 시간이 설정된 타임아웃을 초과하면 "열림" 상태로 전환하고 저전력 모드로 전환
  if (millis() - lastMotionDetectedTime > motionTimeout) {
    myservo.write(90);  // 기본 "열림" 상태로 전환
    Serial.println("No motion detected");
    delay(1000);  // Debounce delay

    // 저전력 모드로 전환
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    // 외부 인터럽트를 허용하여 슬립 모드에서 깨어날 수 있도록 설정
    attachInterrupt(digitalPinToInterrupt(pirPin), wakeUp, RISING);
    sleep_mode();

    // 슬립 모드에서 깨어난 후
    sleep_disable();
    detachInterrupt(digitalPinToInterrupt(pirPin));
  }
}

// 인터럽트 핸들러 (슬립 모드에서 깨어나기 위한 함수)
void wakeUp() {
  // 인터럽트가 발생하면 이 함수가 호출됩니다. 아무 작업도 필요하지 않습니다.
}
