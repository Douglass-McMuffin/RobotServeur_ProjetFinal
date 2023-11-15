#ifndef suiveurDeLigne_h
#define suiveurDeLigne_h

#include <arduino.h>


#define PIN_LUMIERE_GAUCHE 50 //À changer dans le futur
#define PIN_LUMIERE_CENTRE 51 //même chose
#define PIN_LUMIERE_DROITE 52 //même chose

#define NOMBRE_DE_SOMMET 6 // À mettre à jour plus tard


struct Sommet {
    char nom; // Identifiant
    struct Sommet *voisin[NOMBRE_DE_SOMMET - 1]; // Les voisins immédiat du sommet
    int nb_voisin;
    struct Sommet *predecesseur; // Pointe vers le sommet qui s'y rend
    bool marque; // la marque détermine si le sommet a déjà été vu.
};

struct File {
    struct Sommet sommets[NOMBRE_DE_SOMMET]; // Une file qui contient les sommets dans l'ordre de découverte
    int debut; // index du début
    int fin; // index de fin
};

// LireLumiere permet de modifier les bool des trois capteurs de lumière
// *p_luxGauche = adresse du bool pour Gauche et ainsi de suite
void LireLumiere (int *p_luxGauche, int *p_luxCentre, int *p_luxDroite);
// ControleMoteurLigne change la vitesse selon la situation
void ControleMoteurLigne (float vitesse, float *p_vGauche, float *p_vDroite, int luxGauche, int luxCentre, int luxDroite);
void Enfile (struct File file, struct Sommet element);
void Defile (struct File file, struct Sommet *element);
int Dedans (struct File file, struct Sommet element);
void AppelElement (struct Sommet *graphe, char nom, struct Sommet *p_sommet);
void Chemin (struct Sommet *graphe, char debut, char fin, char *chemin);
void AppelPointeur (struct Sommet *graphe, char nom, struct Sommet **p_sommet);

#endif