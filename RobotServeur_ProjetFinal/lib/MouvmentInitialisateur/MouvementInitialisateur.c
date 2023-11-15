
#include "MouvementInitialisateur.h"


void InitialiserGraphe (struct Sommet *graphe)
{
    char sommets[] = "ABC123\nA : 1B\nB : A2C\nC : 3B\n1 : A\n2 : B\n3 : C";
    int i = 0;
    struct Sommet *index0;
    struct Sommet sommetActuel;
    index0 = graphe;
    while (sommets[i] != '\n') // Créer tous les sommets
        {
            graphe -> nom = sommets[i];
            i++;
            graphe++;
        }
    i++;
    do { // Ajouter les voisins
        AppelElement(graphe, sommets[i], &sommetActuel);
        i += 4; // Skip les 3 autres caractères
        int nombre_voisin = 0;
        while (sommets[i] != '\n')
        {
            AppelPointeur(graphe, sommets[i], &(sommetActuel.voisin[nombre_voisin])); // Enregistre le voisin
            i++;
            nombre_voisin++;
        }
        index0 -> nb_voisin = nombre_voisin;
        index0 -> marque = 0;
        index0++;

    } while (index0 != graphe);

    return;
}

void InitialiserVariableMouvement (float *p_vitesse)
{
    // ICI ON PEUT DÉTERMINER LES VALEURS POUR LES VARIABLES
    // On ne peut assigner de valeurs à l'extérieur de fonction
    *p_vitesse = 0.5;

    return;
}