#include <SoftwareSerial.h> //시리얼 통신 라이브러리 호출
#include <NewPing.h>

#define SONAR_NUM 3 // Number of sensors.
#define MAX_DISTANCE 200  // Maximum distance (in cm) to ping

//초음파 센서 PIN 설정
NewPing sonar[SONAR_NUM] = {  // Sensor object array.
  NewPing(8,9, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(10,11, MAX_DISTANCE),
  NewPing(12,13, MAX_DISTANCE)
};

void setup() {
  Serial.begin(9600);   //시리얼모니터

  //모터 핀모드 설정
  pinMode(LEFT_A1, OUTPUT);
  pinMode(RIGHT_A2, OUTPUT);
  pinMode(LEFT_B1, OUTPUT);
  pinMode(RIGHT_B2, OUTPUT);
}

void loop() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    Serial.print(i);
    Serial.print("=");
    Serial.print(sonar[i].ping_cm());
    Serial.print("cm ");
  }
  Serial.println();
}
