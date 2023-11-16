#include <Arduino.h>
//#include <LibRobus.h>
//#include "commande_direction.h"
#include <stdio.h>
#include "suiveurDeLigne.h"

//VARIABLE POUR MOUVEMENT
char intersection;
char trajet[10];
char intersection_actuelle;

//variables pour fonction lireLumiere
bool luxGauche; 
bool luxCentre;
bool luxDroite;

//variables pour fonction ControleMoteurLigne
float vGauche;
float vDroite;
float vitesse;/*vitesse desire lors des deplacements*/
//chemin //definir structure
//variables pour fonction indication_direction

// Il faut un code pour le déplacement avec le suiveur de ligne
/*

Dans Alignement : 
Une fonction qui regarder les trois capteurs sont sur du noir.
    Cette fonction

ALOHA
POUR LE MOUVEMENT DU DÉPART AU CLIENT

On suppose qu'on sait c'est quel client (le deuxième)
On suppose qu'on sait qu'on est au départ

Tant qu'il n'est pas au client

*/


void setup() {
  BoardInit();
  Serial.begin(9600); 
}

void loop() {
  struct Sommet graphe[NOMBRE_DE_SOMMET];
  char chemin[NOMBRE_DE_SOMMET];
  InitialiserGraphe(graphe);
  Chemin(graphe, '1', '3', chemin);
  printf("NOMBRE_DE_SOMMET");
  delay(5000);
}
