/*
Projet S1 2018
Class to interface some of the ArduinoX "on board" functionnalities
@author Jean-Samuel Lauzon, Jonathan Vincent, Marc Rousseau
@version 1.0 26/05/2018
*/

#include "Robus.h"

void Robus::init(){
  for(uint8_t i = 0; i < 4; i++){
    pinMode(BUMPER_PIN[i], INPUT);
  }
  for(uint8_t id = 0; id < 2; id++){
    //enableServo(id);
    __sonar__[id].init(__SONAR_ECHO_PINS__[id], __SONAR_TRIG_PINS__[id]);
  }
}

bool Robus::isBumper(uint8_t id){
  if(id<0 || id>4){
    Serial.println("Invalid Bumper id!");
    return false;
  }
  return digitalRead(BUMPER_PIN[id]);
}

uint16_t Robus::readIR(uint8_t id){
  if(id<0 || id>4){
    Serial.println("Invalid IR id!");
    return 0;
  }
  return analogRead(IR_PIN[id]);
}


float Robus::getRangeSonar(uint8_t id){
  if(id<0 || id>1){
    Serial.println("Invalid sonar id!");
  return 0;
  }
  return __sonar__[id].getRange();
}