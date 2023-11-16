/***********************************************************************************************|
File:           commande_direction.cpp                                                          |
Author:         Jonathan Martel-Joseph, MARJ1522                                                |
Date:           12/11/2023		                                                                |
Last Updated:   12/11/2023  																	|
By:             Jonathan Martel-Joseph, MARJ1522                                                |
Description:    permet de suivre des indications aux intersections (selon une structure)        |
************************************************************************************************/

#include <Arduino.h>
#include <LibRobus.h>

#include "commande_direction.h"
#include "turnRound.h"

//***idee personelle du deplacment du robot***//
/*
void loop() {
  //se rendre au client
  //+fonction verifier activation de bouton et sauvegarder en memoire ordre
  
  LireLumiere ()//modifie valeur dans les adresses des capteurs associes(0 ou 1)
  //ajouter condition si trois capteurs == 1{\
    //incrementer ou decrinmenter le positionnement selon les intersections vues par les capteurs(valeur precedante?)*********
        /*fonction:indications(struct chemin(on lui transmet), identifiant "choisi" (on lui transmet), intersection (on lui transmet) )
             1. Acceder a la bonne structure en verifiant le membre "identifiant" de la structure (ex: chemin[i].identifiant == '0ABC1')
                1.1 conserver la valeur de i (la structure)
             2. selon l'intersection, voir la directive associe (if intersection == A, check le membre A et faire l'action)
                  
        //}*/

void indication_direction (struct trajet trajet[],char chemin[], char intersection_actuelle ){
    int i = 0;

//1. Acceder a la bonne structure en verifiant le membre "identifiant" de la structure (ex: chemin[i].identifiant == '0ABC1')
    while ((trajet[i].identifiant) != chemin){
        i++;
    }

//selon l'intersection, voir la directive associe
    if (intersection_actuelle == 'A')
    {
        deplacement_intersection(trajet[i].A);
    }

    if (intersection_actuelle == 'B')
    {
        deplacement_intersection(trajet[i].B);
    }

    if (intersection_actuelle == 'C'){
        deplacement_intersection(trajet[i].C);
    }

}