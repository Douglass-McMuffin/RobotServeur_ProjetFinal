#ifndef Mouvement_Initialisateur_h
#define Mouvement_Initialisateur_h




#include "suiveurDeLigne.h"
#include "turnRound.h"
#include "commande_direction.h"

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

char intersectionDebut;
char intersectionFin;

bool arret; // est vrai si le robot ne bouge pas

char intersectionActuelle;




struct Sommet graphe[NOMBRE_DE_SOMMET];
char chemin[NOMBRE_DE_SOMMET];
struct Direction infoDirection[NOMBRE_DE_DIRECTION];

void InitialiserDirection (struct Direction infoDirection[NOMBRE_DE_DIRECTION]);
void InitialiserVariableMouvement (float *p_vitesse, float *p_vGauche, float *p_vDroite, struct Direction p_infoDirection[NOMBRE_DE_DIRECTION], char *p_intersectionActuelle, char *p_intersectionDebut, char *p_intersectionFin, bool *p_arret)
void MouvementGlobal(struct Direction *p_infoDirection, char *p_chemin, float *p_vitesse, float *p_vGauche, float *p_vDroite, bool *p_luxGauche, bool *p_luxCentre, bool *p_luxDroite, char *p_intersectionActuelle, char *p_intersectionDebut, char *p_intersectionFin, bool *p_arret);

#endif