#include <Arduino.h>
#include "LibRobus.h"
#include "drinkSelection.h"

int positionX;
int positionY;
int counter = 1000001;
int drink;
int aLastState;
int aState;
int globalState = 0;

void setup() {
  BoardInit();
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
  pinMode (inputSW, INPUT_PULLUP);

  aLastState = digitalRead(outputA); 

  DISPLAY_Clear();
  menuInit(counter, &positionX, &positionY);
}
void loop() {
  //Drink selection for the client
  drink = selection(&counter, &aLastState, &aState, &positionX, &positionY, &globalState);
  if(drink == 3){
    
  }
  Serial.print("Drink: ");
  Serial.print(drink);
  Serial.print(" ");
}