#include <Arduino.h>
#include <LibRobus.h>
//#include "commande_direction.h"
#include "MouvementInitialisateur.h"




void setup() {
  BoardInit();
  Serial.begin(9600);
  InitialiserDirection(infoDirection); 
}

void loop() {
  
  
}

