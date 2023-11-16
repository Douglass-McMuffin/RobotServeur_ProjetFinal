#ifndef suiveurDeLigne_h
#define suiveurDeLigne_h

#include <arduino.h>


#define PIN_LUMIERE_GAUCHE 40
#define PIN_LUMIERE_CENTRE 41
#define PIN_LUMIERE_DROITE 42

#define NOMBRE_DE_SOMMET 6

#define LEFT 0
#define STRAIGHT 1
#define RIGHT 2


struct Sommet {
    char nom;
    struct Sommet *voisin[NOMBRE_DE_SOMMET - 1];
    int nb_voisin;
    struct Sommet *predecesseur;
    bool marque;
};

struct File {
    struct Sommet sommets[NOMBRE_DE_SOMMET];
    int debut;
    int fin;
};

struct Mouv {
    char nom[4];
    int mouvement;
};

void LireLumiere (bool *p_luxGauche, bool *p_luxCentre, bool *p_luxDroite);
void ControleMoteurLigne (float vitesse, float *p_vGauche, float *p_vDroite, bool luxGauche, bool luxCentre, bool luxDroite);
void Enfile (struct File file, struct Sommet element);
void Defile (struct File file, struct Sommet *element);
bool Dedans (struct File file, struct Sommet element);
void AppelElement (struct Sommet *graphe, char nom, struct Sommet *p_sommet);
void Chemin (struct Sommet *graphe, char debut, char fin, char *chemin);
void InitialiserGraphe (struct Sommet *graphe);

#endif