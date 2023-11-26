#include <MouvementInitialisateur.h>
#include <Arduino.h>
#include "turnRound.h"



void InitialiserDirection (struct Direction infoDirection[NOMBRE_DE_DIRECTION])
{
    infoDirection[0] = {{'C','B','A'}, STRAIGHT};
    infoDirection[1] = {{'B','A','0'}, STRAIGHT};
    infoDirection[2] = {{'0','A','B'}, STRAIGHT};
    infoDirection[3] = {{'A','B','C'}, STRAIGHT};
    infoDirection[4] = {{'1','A','4'}, STRAIGHT};
    infoDirection[5] = {{'4','A','1'}, STRAIGHT};
    infoDirection[6] = {{'2','B','5'}, STRAIGHT};
    infoDirection[7] = {{'5','B','2'}, STRAIGHT};
    infoDirection[8] = {{'3','C','6'}, STRAIGHT};
    infoDirection[9] = {{'6','C','3'}, STRAIGHT};

    infoDirection[10] = {{'3','C','B'}, DROITE};
    infoDirection[11] = {{'C','B','2'}, DROITE};
    infoDirection[12] = {{'2','B','A'}, DROITE};
    infoDirection[13] = {{'B','A','1'}, DROITE};
    infoDirection[14] = {{'1','A','0'}, DROITE};
    infoDirection[15] = {{'0','A','4'}, DROITE};
    infoDirection[16] = {{'4','A','B'}, DROITE};
    infoDirection[17] = {{'A','B','5'}, DROITE};
    infoDirection[18] = {{'5','B','C'}, DROITE};
    infoDirection[19] = {{'B','C','6'}, DROITE};

    infoDirection[20] = {{'6','C','B'}, LEFT};
    infoDirection[21] = {{'C','B','5'}, LEFT};
    infoDirection[22] = {{'5','B','A'}, LEFT};
    infoDirection[23] = {{'B','A','4'}, LEFT};
    infoDirection[24] = {{'4','A','0'}, LEFT};
    infoDirection[25] = {{'0','A','1'}, LEFT};
    infoDirection[26] = {{'1','A','B'}, LEFT};
    infoDirection[27] = {{'A','B','2'}, LEFT};
    infoDirection[28] = {{'2','B','C'}, LEFT};
    infoDirection[29] = {{'B','C','3'}, LEFT};
}



void InitialiserVariableMouvement (float *p_vitesse, float *p_vGauche, float *p_vDroite, struct Direction p_infoDirection[NOMBRE_DE_DIRECTION], char *p_intersectionActuelle, char *p_intersectionDebut, char *p_intersectionFin, bool *p_arret)
{
    // ICI ON PEUT DÉTERMINER LES VALEURS POUR LES VARIABLES
    // On ne peut assigner de valeurs à l'extérieur de fonction
    *p_vitesse = 0.25;
    *p_vGauche = *p_vitesse;
    *p_vDroite = *p_vitesse;
    *p_intersectionActuelle = '0';
    *p_intersectionDebut = *p_intersectionActuelle;
    *p_intersectionFin = '0';
    *p_arret = true;
    //GestionClient -> debut = 0;
    //GestionClient -> fin = 0;
    //for (int i = 0; i < NOMBRE_DE_BOUTON; i++)
    //{
    //    GestionClient -> client[i] = '\0';
    //}


    InitialiserDirection(p_infoDirection);
    
}

void MouvementGlobal(struct Direction *p_infoDirection, char *p_chemin, float *p_vitesse, float *p_vGauche, float *p_vDroite, bool *p_luxGauche, bool *p_luxCentre, bool *p_luxDroite, char *p_intersectionActuelle, char *p_intersectionDebut, char *p_intersectionFin, bool *p_arret)
{
    
    if (!*p_arret) // S'il bouge
    {
        LireLumiere(p_luxGauche, p_luxCentre, p_luxDroite);
        if (!*p_luxCentre && !*p_luxGauche && !*p_luxDroite)
        {
            if (*p_intersectionActuelle != *p_intersectionFin)
            {
                // On est dans une intersection
                int index = IndexChemin(p_chemin, *p_intersectionActuelle);
                char action[3] = {p_chemin[index - 1], p_chemin[index], p_chemin[index + 1]};
                int direction = Direction(p_infoDirection, action); // LEFT = 0, STRAIGH = 1, DROITE = 2

                deplacement_intersection(direction);
                MOTOR_SetSpeed(0,*p_vitesse);
                MOTOR_SetSpeed(1,*p_vitesse);
                delay(500);

                intersection_suivant(p_chemin, p_intersectionActuelle);
            }
            else 
            {
                //On est arrivé
                *p_arret = true;
                MOTOR_SetSpeed(0,0);
                MOTOR_SetSpeed(1,0);
            }
        }
        if (!*p_arret)
        {
            ControleMoteurLigne(*p_vitesse, p_vGauche, p_vDroite, *p_luxGauche, *p_luxCentre, *p_luxDroite);
            MOTOR_SetSpeed(0,*p_vGauche);
            MOTOR_SetSpeed(1,*p_vDroite);
        }
    }
    // S'il ne bouge pas
    else if (*p_intersectionActuelle != *p_intersectionFin && *p_intersectionFin != '\0')
    {
        Chemin(*p_intersectionActuelle, *p_intersectionFin, p_chemin);
        *p_intersectionDebut = p_chemin[0];
        intersection_suivant(p_chemin, p_intersectionActuelle);

        deplacement_intersection(LEFT);
        deplacement_intersection(LEFT);

        *p_arret = false;

    }
    
} 
