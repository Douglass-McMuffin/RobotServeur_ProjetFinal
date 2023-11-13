#ifndef commande_direction_h
#define commande_direction_h

#include <stdio.h>
#include <libRobus.h>
#include <arduino.h> // necessaire?
/**
 * @par identifiant The action parameter represents the movement we want to give to the robot
 * @param identifiant chemin, premiere lettre reprsente le depart, la derniere lettre la fin
 * 
*/
struct chemin{
char identifiant[6];//chemin pour se rendre d'un point 1 a 2
//donner instruction pour chaque intersection(0 = left ; 1 = straight ; 2 = right.)
int A;
int B;
int C;
};

#endif