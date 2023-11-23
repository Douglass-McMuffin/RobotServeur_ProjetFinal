#include "drinkSelection.h"

LiquidCrystal_I2C lcd(0x27, totalColumns, totalRows);
const char* menuItems[] = {"CocaCola", "Sprite", "Pepsi", "Cancel",  NULL};

int selection(int* counter, int* aLastState, int* aState, int* positionX, int* positionY, int* globalState){
    //Decision not yet taken
    int decision = 0;
    // If the previous and the current state of the outputA are different, that means a Pulse has occured
    while(!decision){
        // Reads the "current" state of the outputA
        *aState = digitalRead(outputA);
        switch (*globalState)
        {
        case 0:
        if (*aState != *aLastState){    
        //If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
            if (digitalRead(outputB) != *aState) 
            {
                (*counter) --;
            }else {
                (*counter) ++;
            }
        cursor((*counter)/2, positionX, positionY);
        }
        if(!digitalRead(inputSW) && ((*counter / 2) % 4) != 3){
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Vous avez pris:");
            lcd.setCursor(0, 1);
            lcd.print(menuItems[((*counter/2) % 4)]);
            *globalState = 1;
            //Decision has been taken
            decision = 1;
            delay(3000);
        }else if(!digitalRead(inputSW) && ((*counter / 2) % 4) == 3){
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("On se recroise");
            lcd.setCursor(0, 1);
            lcd.print("mes ptits tanant");
            *globalState = 1;
             //Decision has been taken
            decision = 1;
            delay(3000);
        }
        break;
        case 1:
        //lcd.clear();//inutile??
        menuInit(*counter, positionX, positionY);
        *globalState = 0;
        default:
        break;
        }
    *aLastState = *aState; // Updates the previous state of the outputA with the current state
    }
    return ((*counter/2) % 4 ) + 4;
}
void cursor(int counter, int* positionX, int* positionY){
  lcd.setCursor(*positionX, *positionY);
  lcd.print(" ");
  *positionX = (counter % 4) >= 2 ? 9 : 0;
  *positionY = (counter % 2);
  lcd.setCursor(*positionX, *positionY);
  lcd.print(">");
}
void menuInit(int counter, int* positionX, int* positionY){
    lcd.init();
    cursor(counter/2, positionX, positionY);
    unsigned int nbItems = 0;
    
    while(menuItems[nbItems] != nullptr){
        nbItems++;
    }
    for(unsigned int i = 0; i <= (nbItems); i++){
        lcd.setCursor((i % 4) >= 2 ? 10 : 1, (i % 2));
        lcd.print(menuItems[i]);
    }
}