// 아날로그 입력 핀 설정
const int Sensor1 = A0; // 압력센서 1
const int Sensor2 = A1; // 압력센서 2
const int Sensor3 = A2; // 압력센서 3
const int Sensor4 = A5; // 플렉스센서 1
const int Sensor5 = A6; // 플렉스센서 2
const int Sensor6 = A7; // 플렉스센서 3

// 진동 모터 핀 설정
const int motorPins1[] = {3, 4}; // Sensor1 -> Motor pins 3, 4
const int motorPins2[] = {5, 6}; // Sensor2 -> Motor pins 5, 6
const int motorPins3[] = {10, 11}; // Sensor5 -> Motor pins 10, 11
const int motorPins4[] = {12, 13}; // Sensor6 -> Motor pins 12, 13

unsigned long startTime3 = 0;
unsigned long startTime4 = 0;
bool measuring3 = false;
bool measuring4 = false;

// flag 변수 초기화
bool flag1 = false; // Sensor1의 500 초과 여부
bool flag2 = false; // Sensor2의 500 초과 여부
bool flag3 = false; // Sensor5의 500 초과 여부
bool flag4 = false; // Sensor6의 500 초과 여부
bool flag5 = false; // Sensor3의 700 초과 여부
bool flag6 = false; // Sensor4의 700 초과 여부

void setup() {
  // 시리얼 통신 시작
  Serial.begin(9600); // 시리얼 통신 속도 9600

  // 진동 모터 핀을 출력으로 설정
  for (int i = 0; i < 2; i++) {
    pinMode(motorPins1[i], OUTPUT);
    analogWrite(motorPins1[i], 119); // 수정된 부분
    pinMode(motorPins2[i], OUTPUT);
    analogWrite(motorPins2[i], 119);
    pinMode(motorPins3[i], OUTPUT);
    analogWrite(motorPins3[i], 119); // 수정된 부분
    pinMode(motorPins4[i], OUTPUT);
    analogWrite(motorPins4[i], 119);
  }
}

void loop() {
  // 각 센서의 아날로그 값을 읽음
  int Value1 = analogRead(Sensor1);
  int Value2 = analogRead(Sensor2);
  int Value3 = analogRead(Sensor3);
  int Value4 = analogRead(Sensor4);
  int Value5 = analogRead(Sensor5);
  int Value6 = analogRead(Sensor6);

  // 압력 센서가 500을 초과하면 해당 번호 출력 (한 번만)
  if (Value1 > 500 && !flag1) {
    Serial.println("3"); // 압력센서 1이 500을 넘으면 3 출력
    flag1 = true; // flag1을 true로 설정하여 이후엔 출력 안 함
  } else if (Value1 <= 500) {
    flag1 = false; // Value1이 500 이하로 돌아오면 flag1 초기화
  }

  if (Value2 > 500 && !flag2) {
    Serial.println("4"); // 압력센서 2가 500을 넘으면 4 출력
    flag2 = true; // flag2를 true로 설정하여 이후엔 출력 안 함
  } else if (Value2 <= 500) {
    flag2 = false; // Value2가 500 이하로 돌아오면 flag2 초기화
  }

  if (Value5 > 500 && !flag3) {
    Serial.println("5"); // 압력센서 5가 500을 넘으면 5 출력
    flag3 = true; // flag3을 true로 설정하여 이후엔 출력 안 함
  } else if (Value5 <= 500) {
    flag3 = false; // Value5가 500 이하로 돌아오면 flag3 초기화
  }

  if (Value6 > 500 && !flag4) {
    Serial.println("6"); // 압력센서 6이 500을 넘으면 6 출력
    flag4 = true; // flag4를 true로 설정하여 이후엔 출력 안 함
  } else if (Value6 <= 500) {
    flag4 = false; // Value6이 500 이하로 돌아오면 flag4 초기화
  }

  if (Value3 > 200 && Value3 < 700 && !measuring3) {
    startTime3 = millis();
    measuring3 = true;
  }
  // 3번 센서 값이 700 이상이면 "1" 출력 (한 번만)
  if (Value3 > 700 && !flag5 && measuring3) {
    Serial.println("1"); // 3번 센서 값이 700을 넘으면 "1" 출력
    unsigned long endTime3 = millis();
    unsigned long duration = endTime3 - startTime3;
    Serial.println(String(duration) + "ms");

    startTime3 = 0;
    flag5 = true; // flag5를 true로 설정하여 이후엔 출력 안 함
    measuring3 = false;
  } else if (Value3 > 300 && Value3 < 700 && !measuring3) {
    startTime3 = millis();
    measuring3 = true;
  } else if (Value3 < 300) {
    startTime3 = 0;
    measuring3 = false;
    flag5 = false; // Value3이 200 이하로 돌아오면 flag5 초기화
  }

  // 4번 센서 값이 700 이상이면 "2" 출력 (한 번만)
  if (Value4 > 700 && !flag6 && measuring4) {
    Serial.println("2"); // 3번 센서 값이 700을 넘으면 "1" 출력
    unsigned long endTime4 = millis();
    unsigned long duration = endTime4 - startTime4;
    Serial.println(String(duration) + "ms");

    flag6 = true; // flag5를 true로 설정하여 이후엔 출력 안 함
    startTime4 = 0;
    measuring4 = false;
  } else if (Value4 > 300 && Value4 < 700 && !measuring4) {
    startTime4 = millis();
    measuring4 = true;
  } else if (Value4 < 300) {
    measuring4 = false;
    startTime4 = 0;
    flag6 = false; // Value3이 200 이하로 돌아오면 flag5 초기화
  }

  // 센서 값에 따라 진동 모터 작동
  // Sensor1: 3번, 4번 모터
  if (Value1 > 500) {
    analogWrite(motorPins3[0], 255); // 3번 모터 ON
    analogWrite(motorPins3[1], 255); // 4번 모터 ON
  } else {
    analogWrite(motorPins3[0], 119); // 3번 모터 OFF
    analogWrite(motorPins3[1], 119); // 4번 모터 OFF
  }

  // Sensor2: 5번, 6번 모터
  if (Value2 > 500) {
    analogWrite(motorPins4[0], 255); // 3번 모터 ON
    analogWrite(motorPins4[1], 255); // 4번 모터 ON
  } else {
    analogWrite(motorPins4[0], 119); // 3번 모터 OFF
    analogWrite(motorPins4[1], 119); // 4번 모터 OFF
  }

  // Sensor5: 10번, 11번 모터
  if (Value5 > 500) {
    analogWrite(motorPins1[0], 255); // 3번 모터 ON
    analogWrite(motorPins1[1], 255); // 4번 모터 ON
  } else {
    analogWrite(motorPins1[0], 119); // 3번 모터 OFF
    analogWrite(motorPins1[1], 119); // 4번 모터 OFF
  }

  // Sensor6: 12번, 13번 모터
  if (Value6 > 500) {
    analogWrite(motorPins2[0], 255); // 3번 모터 ON
    analogWrite(motorPins2[1], 255); // 4번 모터 ON
  } else {
    analogWrite(motorPins2[0], 119); // 3번 모터 OFF
    analogWrite(motorPins2[1], 119); // 4번 모터 OFF
  }

  delay(100); // 100ms 대기하여 출력과 센서 읽기 간격을 빠르게 설정
}