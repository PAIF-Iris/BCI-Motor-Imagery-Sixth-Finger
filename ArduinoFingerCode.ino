#include <ESP32Servo.h>
#include <IRremote.hpp>

const int CONTINUE_SERVO = 14;
const int SERVO = 33;
const int REMOTE = 25;

const uint16_t CODE_forward = 0x18; 
const uint16_t CODE_backward = 0x52; 
const uint16_t CODE_stop = 0x1C; 
const uint16_t CODE_rotate = 0x5A; 
const uint16_t CODE_rotate_back = 0x45; 

Servo rServo;
Servo tServo; 

void setup() {
  Serial.begin(115200);

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  rServo.setPeriodHertz(50);
  rServo.attach(SERVO, 500, 2400);

  tServo.setPeriodHertz(50);
  tServo.attach(CONTINUE_SERVO, 500, 2400);

  IrReceiver.begin(REMOTE, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()){
    uint16_t command = IrReceiver.decodedIRData.command;
    
    if (command == CODE_forward){
      tServo.write(100);
    }
    else if (command == CODE_backward){
      tServo.write(90);
    }
    else if (command == CODE_stop){
      tServo.write(92);
    }
    else if (command == CODE_rotate){
      rServo.write(90);
    }
    else if (command == CODE_rotate_back){
      rServo.write(0);
    }
    IrReceiver.resume();
  }
}



