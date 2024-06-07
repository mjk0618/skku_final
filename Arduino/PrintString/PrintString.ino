void setup() {
  Serial.begin(9600);  // 시리얼 통신 시작
}

void loop() {
  float hum = 55.0;  // 가상의 습도 값
  float temp = 24.0; // 가상의 온도 값

  Serial.print("Humidity_in_Arduino: ");
  Serial.print(hum);
  Serial.println(" %");
  
  Serial.print("Temperature_in_Arduino: ");
  Serial.print(temp);
  Serial.println(" C");

  delay(2000);  // 2초 대기
}
