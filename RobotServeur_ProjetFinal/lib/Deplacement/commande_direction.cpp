/***********************************************************************************************|
File:           commande_direction.cpp                                                          |
Author:         Jonathan Martel-Joseph, MARJ1522                                                |
Date:           12/11/2023		                                                                |
Last Updated:   12/11/2023  																	|
By:             Jonathan Martel-Joseph, MARJ1522                                                |
Description:    permet de suivre des indications aux intersections (selon une structure)        |
************************************************************************************************/

#include <Arduino.h>

#include "commande_direction.h"
#include "turnRound.h"

void indication_direction (struct Trajet trajet1[],char chemin[], char* p_intersection){

    int i = 0;

//1. Acceder a la bonne structure en verifiant le membre "identifiant" de la structure (ex: chemin[i].identifiant == '0ABC3')
    /*while ((trajet1[i].identifiant) != chemin){
        i++;
    }*/

//selon l'intersection, voir la directive associe
    if (*p_intersection == 'A')
    {
        deplacement_intersection(trajet1[i].A);
    }

    if (*p_intersection == 'B')
    {
        deplacement_intersection(trajet1[i].B);
    }

    if (*p_intersection == 'C'){
        deplacement_intersection(trajet1[i].C);
    }

}

void intersection_suivant(char chemin[],char* p_intersection)
{
    int i = 0;
    while (chemin[i] != *p_intersection){
        i++;  
    }
    *p_intersection = chemin[(i+1)];
}


