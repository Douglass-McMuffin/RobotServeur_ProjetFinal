#include <librobus.h>
#include <Wire.h>

#define COCA 4 //Rouge
#define SEVENUP 5 //Vert
#define PEPSI 6 //Bleu

#define outputA 38
#define outputB 40
#define inputSW 39

#define totalColumns 16 //Columns on the LCD screen
#define totalRows 2 //Rows on the LCD screen

//int counter, aLastState, aState, positionX, positionY, globalState;


int selection(int* counter, int* aLastState, int* aState, int* positionX, int* positionY, int* globalState);
void menuInit(int counter, int* positionX, int* positionY);
void cursor(int counter, int* positionX, int* positionY);
