
#include <SoftwareSerial.h>   // 引用程式庫
#include <Wire.h>

// 定義連接藍牙模組的序列埠
SoftwareSerial BT(2, 3); // 接收腳RX, 傳送腳TX.(2接藍芽TX,3接藍芽RX)

char Car_status;
//右馬達
const byte RIGHT1 = 7; //IN3
const byte RIGHT2 = 6; //IN4
const byte RIGHT_PWM= 5;

//左馬達
const byte LEFT1 = 8; //IN1
const byte LEFT2 = 9; //IN2
const byte LEFT_PWM= 10;

///紅外線1
int DigitalPin = 4;   
int AnalogPin = A0;
//2
int DigitalPin1 = 11;   
int AnalogPin1 = A1;
//中間
int DigitalPin2 = 12;

byte Speed_value = 100; //設定PWM輸出值（車子速度
byte Speed_value1 = 130; //給右輪子
//尋跡
int Speed_value2 = 90; 
int Speed_value3 = 110;//給右輪子
int Speed_value4 = 40; 
int Speed_value5 = 60;//給右輪子
int timer= 200;        //設定車子行走時間

void setup() {
  Serial.begin(9600);   //  以9600 bps初始化序列埠
  Serial.println("BT is ready!");
  BT.begin(9600); // 設定HC-05藍牙模組，AT命令模式的連線速率。）
  //L298N
  pinMode(RIGHT1, OUTPUT);
  pinMode(RIGHT2, OUTPUT);
  pinMode(RIGHT_PWM, OUTPUT);
  pinMode(LEFT1, OUTPUT);
  pinMode(LEFT2, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);
  //紅外線
  pinMode(DigitalPin, INPUT); // 設定數位Pin為輸入
  pinMode(AnalogPin, INPUT); // 設定數位Pin為輸入
  pinMode(DigitalPin1, INPUT);
  pinMode(DigitalPin2, INPUT);
  
}

void backward(){
  digitalWrite(LEFT1, HIGH);
  digitalWrite(LEFT2, LOW);
  digitalWrite(RIGHT1, HIGH);
  digitalWrite(RIGHT2, LOW);
  analogWrite(LEFT_PWM, Speed_value2);
  analogWrite(RIGHT_PWM, Speed_value3);
}
void backward1(){ //右輪快
  digitalWrite(LEFT1, HIGH);
  digitalWrite(LEFT2, LOW);
  digitalWrite(RIGHT1, HIGH);
  digitalWrite(RIGHT2, LOW);
  analogWrite(LEFT_PWM, Speed_value2);
  analogWrite(RIGHT_PWM, Speed_value1);
}


void forward(){
  digitalWrite(LEFT1, LOW);
  digitalWrite(LEFT2, HIGH);
  digitalWrite(RIGHT1, LOW);
  digitalWrite(RIGHT2, HIGH);
  analogWrite(LEFT_PWM, Speed_value2);
  analogWrite(RIGHT_PWM, Speed_value3);
}
void forward2(){
  digitalWrite(LEFT1, LOW);
  digitalWrite(LEFT2, HIGH);
  digitalWrite(RIGHT1, LOW);
  digitalWrite(RIGHT2, HIGH);
  analogWrite(LEFT_PWM, Speed_value4);
  analogWrite(RIGHT_PWM, Speed_value5);
}

void left(){ 
  digitalWrite(RIGHT1, LOW);
  digitalWrite(RIGHT2, HIGH);
  analogWrite(LEFT_PWM, 0);
  analogWrite(RIGHT_PWM, Speed_value3);
}

void right(){ 
  digitalWrite(LEFT1, LOW);
  digitalWrite(LEFT2, HIGH);
  analogWrite(LEFT_PWM, Speed_value2);
  analogWrite(RIGHT_PWM, 0);
}

void stopMotor(){
  analogWrite(LEFT_PWM, 0);
  analogWrite(RIGHT_PWM, 0);
}



void loop() {
   if (BT.available()) { // 如果藍芽接收到資料
    Car_status =BT.read();  
    Serial.println(Car_status); 
    if (Car_status == 'F') {  //前進
      forward();
    } else if (Car_status == 'B') {  //後退
      backward();
    } else if (Car_status == 'L') {  //左轉
      left();
    } else if (Car_status == 'R') {  //右轉
      right();
    } else if (Car_status == 'S') {  //停止
      stopMotor();
    }
  }

else 
  { 
    if (Serial.available()) // 檢查是否有可用的訊息
    {
     char receivedChar = Serial.read(); // 讀取接收到的字元  
       if (receivedChar == 's') // 判斷接收到的字元是否為 's'
       {
          Serial.println("Stop"); // 在序列埠中顯示出 "Stop"
          stopMotor();
       }
       if (receivedChar == 'g')
       {
        
         Serial.println("Forward"); // 在序列埠中顯示出 "Forward"
         forward2();
         delay(500); 
       }
    }
 }
}
