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
struct trajet{
char identifiant[6];
int A;
int B;
int C;
};

struct trajet trajet = {"0ABC3",STRAIGHT,STRAIGHT,LEFT};

}

void indication_direction (struct trajet trajet[],char chemin[], char* p_intersection );
void intersection_actuel (char chemin[],char* p_intersection);

#endif