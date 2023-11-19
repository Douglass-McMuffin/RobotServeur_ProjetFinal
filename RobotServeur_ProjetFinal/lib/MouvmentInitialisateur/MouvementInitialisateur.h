#ifndef Mouvement_Initialisateur_h
#define Mouvement_Initialisateur_h

#include "suiveurDeLigne.h"
//#include "turnRound.h"
//#include "commande_direction.h"

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


void InitialiserGraphe (struct Sommet *graphe);
void InitialiserVariableMouvement (float *p_vitesse);

#endif