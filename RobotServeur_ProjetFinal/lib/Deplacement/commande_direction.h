#ifndef commande_direction_h
#define commande_direction_h


#include <Arduino.h> // necessaire?
#define LEFT 0
#define STRAIGHT 1
#define DROITE 2


/**
 * 
 * @param identifiant chemin, premiere lettre represente le depart, la derniere lettre la fin
 * @param membres chaque intersection contenant les valeurs suivantes: 0 = left ; 1 = straight ; 2 = right.
*/
struct Trajet{
char identifiant[6];
int A;
int B;
int C;
};


void indication_direction (struct Trajet trajet[],char chemin[], char* p_intersection );
void intersection_suivant (char chemin[],char* p_intersection);

#endif