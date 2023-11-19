
#include "suiveurDeLigne.h"
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

    infoDirection[12] = {{'3','C','B'}, RIGHT};
    infoDirection[13] = {{'2','B','A'}, RIGHT};
    infoDirection[14] = {{'1','A','O'}, RIGHT};
    infoDirection[15] = {{'0','O','A'}, RIGHT};
    infoDirection[16] = {{'4','D','E'}, RIGHT};
    infoDirection[17] = {{'5','E','F'}, RIGHT};
    infoDirection[18] = {{'6','F','G'}, RIGHT};

    infoDirection[19] = {{'C','B','2'}, RIGHT};
    infoDirection[20] = {{'B','A','1'}, RIGHT};
    infoDirection[21] = {{'O','D','4'}, RIGHT};
    infoDirection[22] = {{'D','O','0'}, RIGHT};
    infoDirection[23] = {{'D','E','5'}, RIGHT};
    infoDirection[24] = {{'E','F','6'}, RIGHT};
    infoDirection[25] = {{'F','G','7'}, RIGHT};

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
    return;
}



void InitialiserVariableMouvement (float *p_vitesse)
{
    // ICI ON PEUT DÉTERMINER LES VALEURS POUR LES VARIABLES
    // On ne peut assigner de valeurs à l'extérieur de fonction
    *p_vitesse = 0.5;

    return;
}
