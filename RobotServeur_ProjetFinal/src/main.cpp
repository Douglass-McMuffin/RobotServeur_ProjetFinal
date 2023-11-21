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
 //variables pour fonction indication_direction & intersection_actuel
  char chemin[] = "0ABC3";
  char intersection = chemin[1];

  //variables pour fonction lireLumiere
  bool luxGauche; 
  bool luxCentre;
  bool luxDroite;
 
  //variables pour fonction ControleMoteurLigne
  float vitesse = 0.20;/*vitesse desire lors des deplacements*/
  float vGauche = vitesse;
  float vDroite = vitesse;
  
  //chemin //definir structure
  struct Trajet trajet[1] = {"0ABC3",STRAIGHT,STRAIGHT,LEFT};

void setup() {
  BoardInit();
  MOTOR_SetSpeed(0, vitesse);
  MOTOR_SetSpeed(1, vitesse);
  
}
//int flag = 0;

void loop() {
 
  LireLumiere(&luxGauche,&luxCentre,&luxDroite);

 /*if (luxGauche == 1 && luxCentre == 1 && luxDroite == 1){
    //intersection a deja ete initialiser(premiere position)
      indication_direction(trajet,chemin,&intersection); //tourne a l'intersection "actuel"
      intersection_suivant(chemin,&intersection);//avance dans la chaine de caractere chemin
  }*/
  ControleMoteurLigne(vitesse,&vGauche,&vDroite,luxGauche,luxCentre,luxDroite);
  MOTOR_SetSpeed(0, vGauche);
  MOTOR_SetSpeed(1, vDroite);
  delay(100);
  /*if (flag == 0)
  {
    struct Sommet graphe[NOMBRE_DE_SOMMET];
    char chemin[NOMBRE_DE_SOMMET];
    //InitialiserGraphe(graphe);
    //Chemin(graphe, '1', '3', chemin);
    //Serial.print(chemin);
    flag++;
  } */
}