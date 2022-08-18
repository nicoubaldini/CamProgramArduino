#include <Servo.h>
#include <ArduinoJson.h>

Servo servo1;
Servo servo2;

int PinServo1 = 3;
int PinServo2 = 2;

StaticJsonDocument<500> docInput;

int Servo1Angulo = 90;
int Servo2Angulo = 90;

int MinServo1 = 400;
int MaxServo1 = 2700;

int MinServo2 = 550;
int MaxServo2 = 2700;

void setup() {
  Serial.begin(57600);
  servo1.attach(PinServo1, MinServo1, MaxServo1);
  servo2.attach(PinServo2, MinServo2, MaxServo2);
}

void loop() {
  String input = "";
  while (Serial.available() > 0)
  {
    delayMicroseconds(500); 
    char c = Serial.read();
    input += c;
  }
  input.replace("\n","");
  input.replace("\r","");
  input.replace(" ","");
  input.trim();

  deserializeJson(docInput, input);
  

  bool ServoIzq = docInput["ServoIzq"];
  bool ServoDer = docInput["ServoDer"];
  bool ServoArriba = docInput["ServoArriba"];
  bool ServoAbajo = docInput["ServoAbajo"];


  if(ServoIzq && Servo2Angulo <= 179)
  {
    Servo2Angulo = Servo2Angulo + 1;
    servo2.write(Servo2Angulo);
  }
  else if(ServoDer && Servo2Angulo >= 1)
  {
    Servo2Angulo = Servo2Angulo - 1;
    servo2.write(Servo2Angulo);
  }

  if(ServoArriba && Servo1Angulo <= 179)
  {
    Servo1Angulo = Servo1Angulo + 1;
    servo1.write(Servo1Angulo);
  }
  else if(ServoAbajo && Servo1Angulo >= 1)
  {
    Servo1Angulo = Servo1Angulo - 1;
    servo1.write(Servo1Angulo);
  }

}
