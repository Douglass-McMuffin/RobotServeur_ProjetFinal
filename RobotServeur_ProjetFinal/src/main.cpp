#include <Arduino.h>
#include <LibRobus.h>
#include "suiveurDeLigne.h"

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
  // put your setup code here, to run once:
  BoardInit();
  Serial.begin(9600);
  struct Sommet graphe[NOMBRE_DE_SOMMET];
  char chemin[NOMBRE_DE_SOMMET];
  InitaliserGraphe(&graphe);
  Chemin(&graphe, '1', '3', chemin);
  Serial.print(chemin);


  initaliserGraphe()

}


void loop() {
  // put your main code here, to run repeatedly:
}

