#include <Arduino.h>
#include <LibRobus.h>
//#include "commande_direction.h"
#include "MouvementInitialisateur.h"




void setup() {
  BoardInit();
  InitialiserVariableMouvement(&vitesse, &vGauche, &vDroite, infoDirection, &intersection_actuelle, &intersectionDebut, &intersectionFin, &arret);
}


void loop() {
  MouvementGlobal(infoDirection, chemin, &vitesse, &vGauche, &vDroite, &luxGauche, &luxCentre, &luxDroite, &intersection_actuelle, &intersectionDebut, &intersectionFin, &arret);
  
}