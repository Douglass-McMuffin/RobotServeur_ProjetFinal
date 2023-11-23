#ifndef suiveurDeLigne_h
#define suiveurDeLigne_h

#include <Arduino.h>

#define LEFT 0
#define STRAIGHT 1
#define DROITE 2

#define PIN_LUMIERE_GAUCHE A12
#define PIN_LUMIERE_CENTRE A11
#define PIN_LUMIERE_DROITE A10

#define NOMBRE_DE_SOMMET 16
#define NOMBRE_DE_DIRECTION 40

struct Sommet {
    char nom; // Identifiant
    struct Sommet *voisin[NOMBRE_DE_SOMMET - 1]; // Les voisins immédiat du sommet
    int nb_voisin;
    struct Sommet *predecesseur; // Pointe vers le sommet qui s'y rend
    int marque; // la marque détermine si le sommet a déjà été vu.
};

struct File {
    struct Sommet sommets[NOMBRE_DE_SOMMET]; // Une file qui contient les sommets dans l'ordre de découverte
    int debut; // index du début
    int fin; // index de fin
};

struct Direction {
    char nom[3];
    int direction;
};


void LireLumiere (bool *p_luxGauche, bool *p_luxCentre, bool *p_luxDroite);
void ControleMoteurLigne (float vitesse, float *p_vGauche, float *p_vDroite, bool luxGauche, bool luxCentre, bool luxDroite);
void Enfile (struct File file, struct Sommet element);
void Defile (struct File file, struct Sommet *element);
int Dedans (struct File file, struct Sommet element);
struct Sommet AppelElement (struct Sommet *graphe, char nom);
void Chemin (char debut, char fin, char *chemin);
struct Sommet *AppelPointeur (struct Sommet *graphe, char nom);
void InitialiserGraphe (struct Sommet graphe[NOMBRE_DE_SOMMET]);
int Direction (struct Direction infoDirection[], char chemin[3]);
int IndexChemin (char *chemin, char intersection);

#endif