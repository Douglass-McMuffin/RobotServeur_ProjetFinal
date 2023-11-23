#include <MouvementInitialisateur.h>
#include <Arduino.h>



void InitialiserDirection (struct Direction infoDirection[NOMBRE_DE_DIRECTION])
{
    infoDirection[0] = {{'C','B','A'}, STRAIGHT};
    infoDirection[1] = {{'B','A','O'}, STRAIGHT};
    infoDirection[2] = {{'A','O','D'}, STRAIGHT};
    infoDirection[3] = {{'O','D','E'}, STRAIGHT};
    infoDirection[4] = {{'D','E','F'}, STRAIGHT};
    infoDirection[5] = {{'E','F','G'}, STRAIGHT};

    infoDirection[6] = {{'A','B','C'}, STRAIGHT};
    infoDirection[7] = {{'O','A','B'}, STRAIGHT};
    infoDirection[8] = {{'D','O','A'}, STRAIGHT};
    infoDirection[9] = {{'E','D','O'}, STRAIGHT};
    infoDirection[10] = {{'F','E','D'}, STRAIGHT};
    infoDirection[11] = {{'G','F','E'}, STRAIGHT};

    infoDirection[12] = {{'3','C','B'}, DROITE};
    infoDirection[13] = {{'2','B','A'}, DROITE};
    infoDirection[14] = {{'1','A','O'}, DROITE};
    infoDirection[15] = {{'0','O','A'}, DROITE};
    infoDirection[16] = {{'4','D','E'}, DROITE};
    infoDirection[17] = {{'5','E','F'}, DROITE};
    infoDirection[18] = {{'6','F','G'}, DROITE};

    infoDirection[19] = {{'C','B','2'}, DROITE};
    infoDirection[20] = {{'B','A','1'}, DROITE};
    infoDirection[21] = {{'O','D','4'}, DROITE};
    infoDirection[22] = {{'D','O','0'}, DROITE};
    infoDirection[23] = {{'D','E','5'}, DROITE};
    infoDirection[24] = {{'E','F','6'}, DROITE};
    infoDirection[25] = {{'F','G','7'}, DROITE};

    infoDirection[26] = {{'B','C','3'}, LEFT};
    infoDirection[27] = {{'A','B','2'}, LEFT};
    infoDirection[28] = {{'O','A','1'}, LEFT};
    infoDirection[29] = {{'0','O','D'}, LEFT};
    infoDirection[30] = {{'E','D','4'}, LEFT};
    infoDirection[31] = {{'F','E','5'}, LEFT};
    infoDirection[32] = {{'G','F','6'}, LEFT};

    infoDirection[33] = {{'2','B','C'}, LEFT};
    infoDirection[34] = {{'1','A','B'}, LEFT};
    infoDirection[35] = {{'A','O','0'}, LEFT};
    infoDirection[36] = {{'4','D','O'}, LEFT};
    infoDirection[37] = {{'5','E','D'}, LEFT};
    infoDirection[38] = {{'6','F','E'}, LEFT};
    infoDirection[39] = {{'7','G','F'}, LEFT};
}



void InitialiserVariableMouvement (float *p_vitesse, float *p_vGauche, float *p_vDroite, struct Direction p_infoDirection[NOMBRE_DE_DIRECTION], char *p_intersectionActuelle, char *p_intersectionDebut, char *p_intersectionFin, bool *p_arret)
{
    // ICI ON PEUT DÉTERMINER LES VALEURS POUR LES VARIABLES
    // On ne peut assigner de valeurs à l'extérieur de fonction
    *p_vitesse = 0.5;
    *p_vGauche = *p_vitesse;
    *p_vDroite = *p_vitesse;
    *p_intersectionActuelle = '0';
    *p_intersectionDebut = *p_intersectionActuelle;
    *p_intersectionFin = '\0';
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

                // ICI, il faut tourner avec la bonne direction (Partie Hardcoder)

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

        // ICI, on doit faire 180 degrée pour pointer dans la bonne direction

        *p_arret = false;

    }
    
}
