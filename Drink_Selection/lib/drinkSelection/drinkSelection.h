#ifndef drinkSelection_h
#define drinkSelection_h
    #include <librobus.h>
    #include <Wire.h>

    #define COCA 0 //Rouge
    #define SEVENUP 1 //Vert
    #define PEPSI 2 //Bleu
    #define TONIC 3 //Jaune

    #define outputA 10
    #define outputB 11
    #define inputSW 12

    #define totalColumns 16 //Columns on the LCD screen
    #define totalRows 2 //Rows on the LCD screen

    int selection(int* counter, int* aLastState, int* aState, int* positionX, int* positionY, int* globalState);
    void menuInit(int counter, int* positionX, int* positionY);
    void cursor(int counter, int* positionX, int* positionY);
#endif