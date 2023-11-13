#include <Arduino.h>
#include <LibRobus.h>
#include "commande_direction.h"
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
 //variables pour fonction indication_direction

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
  float vitesse = 0.5;/*vitesse desire lors des deplacements*/
  //chemin //definir structure

void setup() {
  BoardInit();
  Serial.begin(9600); 
  MOTOR_SetSpeed(0, vitesse);
  MOTOR_SetSpeed(1, vitesse);

}
int flag = 0;

void loop() {

  LireLumiere(&luxGauche,&luxCentre,&luxDroite);
  if (luxGauche == 1 && luxCentre == 1 && luxDroite == 1){
    
     indication_direction(/*envoie de la bonne "structure"*/,trajet,intersection_actuelle);
  }
  ControleMoteurLigne(vitesse,&p_vGauche,&vDroite,luxGauche,luxCentre,luxDroite);
  MOTOR_SetSpeed(0, vGauche);
  MOTOR_SetSpeed(1, vDroite);

  if (flag == 0)
  {
    struct Sommet graphe[NOMBRE_DE_SOMMET];
    char chemin[NOMBRE_DE_SOMMET];
    //InitialiserGraphe(graphe);
    //Chemin(graphe, '1', '3', chemin);
    //Serial.print(chemin);
    flag++;
  } 
}

