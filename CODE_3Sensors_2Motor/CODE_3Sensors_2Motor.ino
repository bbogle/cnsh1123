#include <SoftwareSerial.h> //시리얼 통신 라이브러리 호출
#include <NewPing.h>

#define SONAR_NUM 3 // Number of sensors.
#define MAX_DISTANCE 200  // Maximum distance (in cm) to ping

#define SONAR1 8
#define SONAR2 9
#define SONAR3 10

//초음파 센서 PIN 설정
NewPing sonar[SONAR_NUM] = {  // Sensor object array.
  NewPing(SONAR1, SONAR1, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(SONAR2, SONAR2, MAX_DISTANCE), 
  NewPing(SONAR3, SONAR3, MAX_DISTANCE)
};

//모터 PIN 설정
#define LEFT_A1 4 //왼쪽 바퀴
#define LEFT_B1 5 //왼쪽 바퀴
#define RIGHT_A2 6 //오른쪽 바퀴
#define RIGHT_B2 7 //오른쪽 바퀴

void setup() {
  Serial.begin(115200);   //시리얼모니터

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

  // 기본 주행
  if(sonar[0].ping_cm() == 0 || sonar[1].ping_cm() == 0 || sonar[2].ping_cm() == 0) {
      Serial.println("forward");
      forward();
  }else{
    if(sonar[0].ping_cm() > 15 && sonar[1].ping_cm() > 15 && sonar[2].ping_cm() > 15){
      Serial.println("forward");
      forward();
    }else{
      // 좌측 sonar[0] 장애물감지시
      if(sonar[0].ping_cm() < 15) {
        Serial.println("sonar[0] detected object");
        stop(1000);
        right(500);
        delay(500); 
      }
      
      // 중앙 sonar[1] 장애물 감지시
      if(sonar[1].ping_cm() < 15) {
        Serial.println("sonar[1] detected object");
        stop(1000);
        left(300);
        delay(300);
      }
    
      // 우측 sonar[2] 장애물 감지시
      if(sonar[2].ping_cm() < 15) {
        Serial.println("sonar[2] detected object");
        stop(1000);
        left(500);
        delay(500);
      }    
   }
  }
}

void forward() {
  digitalWrite(LEFT_A1, HIGH);
  digitalWrite(LEFT_B1, LOW);
  digitalWrite(RIGHT_A2, HIGH);
  digitalWrite(RIGHT_B2, LOW);
}
void backward(int d) {
  digitalWrite(LEFT_A1, LOW);
  digitalWrite(LEFT_B1, HIGH);
  digitalWrite(RIGHT_A2, LOW);
  digitalWrite(RIGHT_B2, HIGH);
  delay(d);
}
void left(int d) {
  digitalWrite(LEFT_A1, LOW);
  digitalWrite(LEFT_B1, HIGH);
  digitalWrite(RIGHT_A2, HIGH);
  digitalWrite(RIGHT_B2, LOW);
  delay(d);
}
void right(int d) {
  digitalWrite(LEFT_A1, HIGH);
  digitalWrite(LEFT_B1, LOW);
  digitalWrite(RIGHT_A2, LOW);
  digitalWrite(RIGHT_B2, HIGH);
  delay(d);
}
void stop(int d) {
  digitalWrite(LEFT_A1, LOW);
  digitalWrite(LEFT_B1, LOW);
  digitalWrite(RIGHT_A2, LOW);
  digitalWrite(RIGHT_B2, LOW);
  delay(d);
}
