#include "suiveurDeLigne.h"
#include <Arduino.h>

// La fonction devra modifier la vitesse des roues selon les capteurs

//À mettre dans le fichier .h (en bas)
float vGauche, vDroite;
float *p_vGauche, *p_vDroite;
p_vGauche = &vGauche;
p_vDroite = &vDroite;
int eGauche, eDroite;

// Inscrit les valeurs des capteurs dans les bools.
// La fonction prend 3 pointeurs pour les 3 capteurs.
// La fonction ne retourne rien. Les variables deviennent soit 0 pour quand il voit du noir et 1 pour quand il voit du blanc
void LireLumiere (bool *p_luxGauche, bool *p_luxCentre, bool *p_luxDroite)
{
    *p_luxGauche = !digitalRead(PIN_LUMIERE_GAUCHE);
    *p_luxCentre = !digitalRead(PIN_LUMIERE_CENTRE);
    *p_luxDroite = !digitalRead(PIN_LUMIERE_DROITE);
    return;
}

void ControleMoteurLigne (float vitesse, float *p_vGauche, float *p_vDroite, bool luxGauche, bool luxCentre, bool luxDroite)
{
    // Si le robot est sur la ligne noir (centre activé)
    if (luxGauche)
    {
        if(!luxCentre)
        {
            *p_vGauche = -vitesse/2;
            *p_vDroite = vitesse;
        }
    }
    if (luxCentre)
    {
        if(!luxGauche && !luxDroite)
        {
            *p_vGauche = vitesse;
            *p_vDroite = vitesse;
        }
    }
    if (luxDroite)
    {
        if(!luxCentre)
        {
            *p_vGauche = vitesse;
            *p_vDroite = -vitesse/2;
        }
    }
}