
#include "suiveurDeLigne.h"
#include <Arduino.h>


void InitialiserGraphe (struct Sommet graphe[NOMBRE_DE_SOMMET])
{
    char sommets[] = "OABCDEFG01234567;O : AD;A : OB1;B : AC2;C : B3;D : OE4;E : DF5;F : EG6;G : F7;0 : O;1 : A;2 : B;3 : C;4 : D;5 : E;6 : F;7 : G;";
    int i = 0;
    //Serial.println("Bonjour");
    int nombre_voisin;
    struct Sommet *sommetActuel;
    struct Sommet *indexVoisin;
    while (sommets[i] != ';') // Créer tous les sommets
    {
        graphe[i].nom = sommets[i];
        Serial.println(graphe[i].nom);
        i++;
    }
    i++;
    do { // Ajouter les voisins
        Serial.println(sommets[i]);
        AppelElement(graphe, sommets[i], sommetActuel);
        Serial.println(sommetActuel -> nom);
        i += 4; // Skip les 3 autres caractères
        nombre_voisin = 0;
        while (sommets[i] != ';')
        {

            AppelPointeur(graphe, sommets[i], &indexVoisin); // Enregistre le voisin
            sommetActuel -> voisin[nombre_voisin] = indexVoisin;
            Serial.print(sommets[i]);
            delay(100);
            i++;
            nombre_voisin++;
            indexVoisin++;
        }
        Serial.print("(");
        Serial.print(nombre_voisin);
        Serial.print(")");
        i++;
        sommetActuel -> nb_voisin = nombre_voisin;
        sommetActuel -> marque = 0;

    } while (sommets[i] != '\0');

    return;
}

void InitialiserVariableMouvement (float *p_vitesse)
{
    // ICI ON PEUT DÉTERMINER LES VALEURS POUR LES VARIABLES
    // On ne peut assigner de valeurs à l'extérieur de fonction
    *p_vitesse = 0.5;

    return;
}
