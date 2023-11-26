#ifndef Mouvement_Initialisateur_h
#define Mouvement_Initialisateur_h




#include "suiveurDeLigne.h"
#include "turnRound.h"
#include "commande_direction.h"
#include "GestionBouton.h"
//#include "GestionBouton.h"

//VARIABLE POUR MOUVEMENT


void InitialiserDirection (struct Direction infoDirection[NOMBRE_DE_DIRECTION]);
void InitialiserVariableMouvement (float *p_vitesse, float *p_vGauche, float *p_vDroite, struct Direction p_infoDirection[NOMBRE_DE_DIRECTION], char *p_intersectionActuelle, char *p_intersectionDebut, char *p_intersectionFin, struct FileGestion *p_fileCirculaire, bool *p_arret);
void MouvementGlobal(struct Direction *p_infoDirection, char *p_chemin, float *p_vitesse, float *p_vGauche, float *p_vDroite, bool *p_luxGauche, bool *p_luxCentre, bool *p_luxDroite, char *p_intersectionActuelle, char *p_intersectionDebut, char *p_intersectionFin, bool *p_arret);

#endif