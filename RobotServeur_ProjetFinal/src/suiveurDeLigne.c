#include "suiveurDeLigne.h"
#include <Arduino.h>
#include <stdio.h>

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

bool Dedans (struct File file, struct Sommet element)
{
    for (int i = file.debut; i <= file.fin; i++)
    {
        if (element == file.sommets[i])
            return true;
    }
    return false;
}

void AppelElement (struct Sommet *graphe, char nom, struct Sommet *p_sommet)
{
    struct Sommet *index;
    index = graphe;
    while (index -> nom != nom)
        index++;
    *p_sommet = *index;
}

void Chemin (struct Sommet *graphe, char debut, char fin, char *chemin)
{
    struct File file;
    struct Sommet sommetActuel;

    AppelElement(graphe, debut, &sommetActuel);
    Enfile (file, sommetActuel);
    sommetActuel.marque = true;
    while (file.debut <= file.fin)
    {
        Defile(file, &sommetActuel);
        for (int i = 0; i < sommetActuel.nb_voisin; i++)
        {
            struct Sommet voisin = *(sommetActuel.voisin[i]);
            if (voisin.marque == false)
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
                    } while (voisin.nom != debut)
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
                voisin.marque = true;
            }
        }
    }
}

void LireGraphe (char *nomFichier, struct Sommet *graphe)
{
    FILE *fp;
    if ((fp = fopen(nomFichier, "r")) == NULL)
    {
        char c = getc(fp);
        struct Sommet *index0;
        struct Sommet sommetActuel;
        index0 = graphe;
        while (c != '\n') // Créer tous les sommets
        {
            graphe -> nom = getc(fp);
            c = getc(fp);
            graphe++;
        }
        do { // Ajouter les voisins
            AppelElement(graphe, getc(fp), &sommetActuel);
            getc(fp);getc(fp);getc(fp); // Skip les 3 autres caractères
            int nombre_voisin = 0;
            while (c != '\n')
            {
                AppelElement(graphe, getc(fp), &(index0 -> voisin[nombre_voisin])); // Enregistre le voisin
                c = getc(fp);
                nombre_voisin++;
            }
            index0 -> nb_voisin = nombre_voisin;
            index0++;

        } while (index0 != graphe)
        fclose(fp);
    }
    else 
    {
        //ERREUR LORS DE L'OUVERTURE DU FICHIER
        return;
    }
}