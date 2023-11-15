#include <Arduino.h>
//#include <LibRobus.h>
//#include "commande_direction.h"
#include <stdio.h>
#include "MouvementInitialisateur.h"



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
  //BoardInit();
  //Serial.begin(9600); 
  //MOTOR_SetSpeed(0, vitesse);
  //MOTOR_SetSpeed(1, vitesse);
}
//***idee personelle du deplacment du robot***//
/*
void loop() {
  //se rendre au client
  //+fonction verifier activation de bouton et sauvegarder en memoire ordre
  
  LireLumiere ()//modifie valeur dans les adresses des capteurs associes(0 ou 1)
  //ajouter condition si trois capteurs == 1{\
    //incrementer ou decrinmenter le positionnement selon les intersections vues par les capteurs(valeur precedante?)*********
        /fonction:indications(struct chemin(on lui transmet), identifiant "choisi" (on lui transmet), intersection (on lui transmet) )
             1. Acceder a la bonne structure en verifiant le membre "identifiant" de la structure (ex: chemin[i].identifiant == '0ABC1')
                1.1 conserver la valeur de i (la structure)
             2. selon l'intersection, voir la directive associe (if intersection == A, check le membre A et faire l'action)
                  
        //}*/
void loop() {
  // On lit les lumières
  //LireLumiere(&luxGauche,&luxCentre,&luxDroite);

  // On vérifie les boutons
  // SI on doit être quelque part (position actuelle != position désirée)
    // On se change les vitesse pour se rendre à la position désirée
    // SI on est à une intersection
      // 
  // SINON
    // On est arrêté
  /*
  if (luxGauche == 1 && luxCentre == 1 && luxDroite == 1){
    
     indication_direction(/envoie de la bonne "structure"/,trajet,intersection_actuelle);
  }
  ControleMoteurLigne(vitesse,&p_vGauche,&vDroite,luxGauche,luxCentre,luxDroite);
  MOTOR_SetSpeed(0, vGauche);
  MOTOR_SetSpeed(1, vDroite);
  */
  struct Sommet graphe[NOMBRE_DE_SOMMET];
  char chemin[NOMBRE_DE_SOMMET];
  InitialiserGraphe(graphe);
  Chemin(graphe, '1', '3', chemin);
  printf("NOMBRE_DE_SOMMET");
  delay(5000);
}
