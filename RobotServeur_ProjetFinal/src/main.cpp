#include <Arduino.h>
#include <LibRobus.h>
//#include "commande_direction.h"
#include "MouvementInitialisateur.h"




void setup() {
  BoardInit();
  Serial.begin(9600);
  InitialiserDirection(infoDirection); 
}
int flag = 1;

void loop() {
  if (flag)
  {
    LireLumiere(&luxGauche,&luxCentre,&luxDroite);
    /*Serial.print("Gauche = ");
    Serial.print(luxGauche);
    Serial.print(" Centre = ");
    Serial.print(luxCentre);
    Serial.print(" Droite = ");
    Serial.println(luxDroite);*/
  if (!luxCentre && !luxDroite && !luxGauche){
      //intersection a deja ete initialiser(premiere position)
        indication_direction(trajet,chemin,&intersection); //tourne a l'intersection "actuel"
        intersection_suivant(chemin,&intersection);//avance dans la chaine de caractere chemin
        Serial.print("big ballz");  
        delay(500); 
    }
    
    ControleMoteurLigne(vitesse,&vGauche,&vDroite,luxGauche,luxCentre,luxDroite);
    MOTOR_SetSpeed(0, vGauche);
    MOTOR_SetSpeed(1, vDroite);
    
    delay(50);
    /*if (!luxCentre && !luxDroite && !luxGauche)
    {
      MOTOR_SetSpeed(0,0);
      MOTOR_SetSpeed(1,0);
      flag = 0;
    }*/
  }
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