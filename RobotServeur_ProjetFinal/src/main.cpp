#include <Arduino.h>
#include <LibRobus.h>
//#include "commande_direction.h"
#include "MouvementInitialisateur.h"
#include <stdio.h>

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

bool flag = true;
void loop() {


  if (flag)
  {
    struct Sommet graphe[NOMBRE_DE_SOMMET];
    char chemin[NOMBRE_DE_SOMMET];
    InitialiserGraphe(graphe);
    Chemin(graphe, '1', '3', chemin);
    Serial.println(chemin);
    flag = false;
  }
}

