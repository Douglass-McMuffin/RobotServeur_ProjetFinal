#ifndef SUIVEURDELIGNE

#include <libRobus.h>
#include <arduino.h>


#define PIN_LUMIERE_GAUCHE
#define PIN_LUMIERE_CENTRE
#define PIN_LUMIERE_DROITE

#define NOMBRE_DE_SOMMET 6

struct Sommet {
    char nom;
    struct Sommet *voisin[NOMBRE_DE_SOMMET - 1]
    int nb_voisin;
    struct Sommet *predecesseur;
    bool marque = false;
}

struct File {
    struct Sommet sommets[NOMBRE_DE_SOMMET];
    int debut = 0;
    int fin = 0;
}



#endif