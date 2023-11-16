#include "suiveurDeLigne.h"
#include <arduino.h>

// Inscrit les valeurs des capteurs dans les bools.
// La fonction prend 3 pointeurs pour les 3 capteurs.
// La fonction ne retourne rien. Les variables deviennent soit 0 pour quand il voit du noir et 1 pour quand il voit du blanc
void LireLumiere (int *p_luxGauche, int *p_luxCentre, int *p_luxDroite)
{
    if (analogRead(PIN_LUMIERE_GAUCHE) < 512)
        *p_luxGauche = 1;
    else
        *p_luxGauche = 0;
    if (analogRead(PIN_LUMIERE_CENTRE) < 512)
        *p_luxCentre = 1;
    else
        *p_luxCentre = 0;
    if (analogRead(PIN_LUMIERE_DROITE) < 512)
        *p_luxDroite = 1;
    else
        *p_luxDroite = 0;
    return;
}

void ControleMoteurLigne (float vitesse, float *p_vGauche, float *p_vDroite, int luxGauche, int luxCentre, int luxDroite)
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

void Enfile (struct File file, struct Sommet element)
{
    file.sommets[file.fin] = element;
    file.fin++;
}

void Defile (struct File file, struct Sommet *element)
{
    if (file.debut <= file.fin) // Vérifie s'il reste des éléments dans la file
    {
        *element = file.sommets[file.debut];
        file.debut++;
    }
}

int Dedans (struct File file, struct Sommet element)
{
    for (int i = file.debut; i <= file.fin; i++)
    {
        if (element.nom == file.sommets[i].nom)
            return 1;
    }
    return 0;
}

void AppelElement (struct Sommet *graphe, char nom, struct Sommet *p_sommet)
{
    struct Sommet *index;
    index = graphe;
    while (index -> nom != nom)
        index++;
    *p_sommet = *index;
}

void AppelPointeur (struct Sommet *graphe, char nom, struct Sommet **p_sommet)
{
    struct Sommet *index;
    index = graphe;
    while (index -> nom != nom)
        index++;
    *p_sommet = index;
}

void Chemin (struct Sommet *graphe, char debut, char fin, char *chemin)
{
    struct File file;
    file.debut = 0; file.fin = 0;
    struct Sommet sommetActuel;

    AppelElement(graphe, debut, &sommetActuel);
    Enfile (file, sommetActuel);
    sommetActuel.marque = 1;
    while (file.debut <= file.fin)
    {
        Defile(file, &sommetActuel);
        for (int i = 0; i < sommetActuel.nb_voisin; i++)
        {
            struct Sommet voisin = *(sommetActuel.voisin[i]);
            if (voisin.marque == 0)
            {
                if (voisin.nom == fin)
                {
                    char cheminPred[20];
                    int i = 0;
                    do
                    {
                        cheminPred[i] = voisin.nom;
                        voisin = *voisin.predecesseur;
                        i++;
                    } while (voisin.nom != debut);
                    cheminPred[i] = debut;
                    for (int j = 0; j <= i; j++)
                    {
                        *chemin = cheminPred[i-j];
                        chemin++;
                    }
                    *chemin = '\0';
                    return;
                }
                voisin.predecesseur = &sommetActuel;
                Enfile(file, voisin);
                voisin.marque = 1;
            }
        }
    }
}

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


