#include <Arduino.h>
#include <LibRobus.h>
//#include "commande_direction.h"
#include <LibRobus.h>
#include "MouvementInitialisateur.h"

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
float vitesse;
//vitesse desire lors des deplacements

char intersectionDebut;
char intersectionFin;

//char client;

bool arret; // est vrai si le robot ne bouge pas

char intersectionActuelle;




char chemin[NOMBRE_DE_SOMMET];
struct Direction infoDirection[NOMBRE_DE_DIRECTION];


void setup() {
  BoardInit();
  InitialiserVariableMouvement(&vitesse, &vGauche, &vDroite, infoDirection, &intersection_actuelle, &intersectionDebut, &intersectionFin, &arret);
}


void loop() {
  MouvementGlobal(infoDirection, chemin, &vitesse, &vGauche, &vDroite, &luxGauche, &luxCentre, &luxDroite, &intersection_actuelle, &intersectionDebut, &intersectionFin, &arret);
  //client = /*Vérifier bouton ClientAssigner()*/;
  //if (client != '0');
  //{
  //  EnfileClient(*GestionClient, client);
  //}



}