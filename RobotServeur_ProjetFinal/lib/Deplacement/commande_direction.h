#ifndef commande_direction_h
#define commande_direction_h

#include <stdio.h>
#include <libRobus.h>
#include <arduino.h> // necessaire?
#define LEFT 0
#define STRAIGHT 1
#define RIGHT 2


/**
 * 
 * @param identifiant chemin, premiere lettre represente le depart, la derniere lettre la fin
 * @param membres chaque intersection contenant les valeurs suivantes: 0 = left ; 1 = straight ; 2 = right.
*/
struct chemin{
char identifiant[6];
int A;
int B;
int C;
};

struct chemin trajet1 = {"0AB2",STRAIGHT,LEFT};

}

void indication_direction (struct chemin[],char trajet[], char intersection_actuelle );
#endif