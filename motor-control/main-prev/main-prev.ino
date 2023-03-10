const int rearLeftWheel = 11;
const int rearRightWheel = 10;
const int frontLeftWheel = 5;
const int frontRightWheel = 6;

const int turnPwmHigh = 170;
const int turnPwmLow = 90;
//tune turnPwmLow according to your need so as to turn vehicle by certain angle : high , low or medium

const int forwardPwm = 150;

void turnLeft(){
  analogWrite(rearRightWheel, turnPwmHigh);
  analogWrite(frontRightWheel, turnPwmHigh);
  analogWrite(rearLeftWheel, turnPwmLow);
  analogWrite(frontLeftWheel, turnPwmLow);  

}

void turnRight(){
  analogWrite(rearRightWheel, turnPwmLow);
  analogWrite(frontRightWheel, turnPwmLow);
  analogWrite(rearLeftWheel, turnPwmHigh);
  analogWrite(frontLeftWheel, turnPwmHigh);  

}

void moveOrStop(int pwm){
  analogWrite(rearRightWheel, pwm);
  analogWrite(rearLeftWheel, pwm);
  analogWrite(frontRightWheel, 0);
  analogWrite(frontLeftWheel, 0);
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

pinMode(rearLeftWheel, OUTPUT);
pinMode(rearRightWheel, OUTPUT);
pinMode(frontLeftWheel, OUTPUT);
pinMode(frontRightWheel, OUTPUT);
moveOrStop(0);

}

String msg = "";

void readSerialData(){
  msg = "" ; 
  if (Serial.available()) {
    delay(10);
    while (Serial.available() > 0) {
      msg += (char)Serial.read();
    }
    Serial.flush();
    reactToSerialMsg();
  }
}

void reactToSerialMsg(){
  if(msg == "f" or msg == "f\n"){
    moveOrStop(forwardPwm);
    Serial.println("forward");
  }
  else if (msg == "r" || msg == "r\n"){
    turnRight();
    Serial.println("right");
  }
  else if(msg == "l" || msg == "l\n"){
    turnLeft();
    Serial.println("left");
  }
  else if(msg == "s" || msg == "s\n"){
    moveOrStop(0);
    Serial.println("stop");
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  readSerialData();
}
