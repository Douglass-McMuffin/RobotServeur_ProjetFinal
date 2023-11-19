#include <Arduino.h>
#include <LibRobus.h>
//#include "commande_direction.h"
#include "MouvementInitialisateur.h"

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
    InitialiserDirection(infoDirection);
    InitialiserGraphe(graphe);

    for (int i = 0; i < NOMBRE_DE_SOMMET; i++)
    {
      Serial.print(graphe[i].nom);
      Serial.print(" : ");
      for (int j = 0; j < graphe[i].nb_voisin; j++)
      {
        Serial.print(graphe[i].voisin[j] -> nom);
      }
      Serial.print("\n");
    }
    for (int i = 0; i < 40; i++)
    {
      Serial.print(infoDirection[i].nom);
      Serial.print(" -> ");
      Serial.println(infoDirection[i].direction);
    }
    char chemin[3] = {'A','B','C'};
    Serial.println(Direction(infoDirection, chemin));
    chemin[0] = 'O';
    chemin[1] = 'A';
    chemin[2] = '1';
    Serial.println(Direction(infoDirection, chemin));


    //Chemin(graphe, '1', '3', chemin);
    //Serial.println(chemin);
    flag = false;
  }
}

