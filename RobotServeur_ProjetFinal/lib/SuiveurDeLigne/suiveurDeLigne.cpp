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

// Permet de modifier la vitesse des moteurs selon la situation
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

//Pour les files, permet d'ajouter un element
void Enfile (struct File *file, struct Sommet element)
{
    file -> sommets[file -> fin] = element;
    file -> fin++;
}

//Pour les files, permet de prendre un element
void Defile (struct File *file, struct Sommet *element)
{
    if (file -> debut <= file -> fin) // Vérifie s'il reste des éléments dans la file
    {
        *element = file -> sommets[file -> debut];
        file -> debut++;
    }
}

//Pour les files, permet de vérifier si un certain element est à l'intérieur
int Dedans (struct File file, struct Sommet element)
{
    for (int i = file.debut; i <= file.fin; i++)
    {
        if (element.nom == file.sommets[i].nom)
            return 1;
    }
    return 0;
}

//Pour les graphes, permet de prendre d'un sommet
struct Sommet AppelElement (struct Sommet *graphe, char nom)
{
    struct Sommet *index;
    index = graphe;
    while (index -> nom != nom)
        index++;
    return *index;
}

//Pour les graphes, permet de prendre l'adresse d'un sommet
struct Sommet *AppelPointeur (struct Sommet *graphe, char nom)
{
    struct Sommet *index;
    index = graphe;
    while (index -> nom != nom)
        index++;
    return index;
}

void InitialiserGraphe (struct Sommet graphe[NOMBRE_DE_SOMMET])
{
    char sommets[] = "OABCDEFG01234567;O : AD0;A : OB1;B : AC2;C : B3;D : OE4;E : DF5;F : EG6;G : F7;0 : O;1 : A;2 : B;3 : C;4 : D;5 : E;6 : F;7 : G;\0";
    int i = 0;
    Serial.println("JE VAIS RÉINITIALISER LE GRAPHE");
    int nombre_voisin;
    struct Sommet *sommetActuel;
    struct Sommet *indexVoisin;
    while (sommets[i] != ';') // Créer tous les sommets
    {
        graphe[i].nom = sommets[i];
        i++;
    }
    i++;
    do { // Ajouter les voisins
        sommetActuel = AppelPointeur(graphe, sommets[i]);
        i += 4; // Skip les 3 autres caractères
        nombre_voisin = 0;
        while (sommets[i] != ';')
        {
            indexVoisin = AppelPointeur(graphe, sommets[i]); // Enregistre le voisin
            sommetActuel -> voisin[nombre_voisin] = indexVoisin;
            i++;
            nombre_voisin++;
        }
        i++;
        sommetActuel -> nb_voisin = nombre_voisin;
        sommetActuel -> marque = 0;

    } while (sommets[i] != '\0');

    return;
}


//Permet de trouver le chemin entre deux points
void Chemin (struct Sommet graphe[NOMBRE_DE_SOMMET], char debut, char fin, char *chemin)
{
    struct File file;
    file.debut = 0; file.fin = 0;
    struct Sommet *premierSommet;
    struct Sommet *voisin;
    struct Sommet sommetActuel;
    InitialiserGraphe(graphe);
    premierSommet = AppelPointeur(graphe, debut);
    premierSommet -> marque = 1;
    Enfile (&file, *premierSommet);
    
    while (file.debut <= file.fin)
    {
        Defile(&file, &sommetActuel);
        for (int i = 0; i < sommetActuel.nb_voisin; i++)
        {
            
            voisin = AppelPointeur(graphe, sommetActuel.voisin[i] -> nom);
            
            if (voisin -> marque == 0)
            {
                if (voisin -> nom == fin)
                {
                    voisin -> predecesseur = AppelPointeur(graphe, sommetActuel.nom);
                    char cheminPred[20];
                    int i = 0;
                    do
                    {
                        cheminPred[i] = voisin -> nom;
                        
                        voisin = voisin -> predecesseur;
                        i++;
                    } while (voisin -> nom != debut);
                    
                    cheminPred[i] = debut;
                    for (int j = 0; j <= i; j++)
                    {
                        *chemin = cheminPred[i-j];
                        chemin++;
                    }
                    *chemin = '\0';
                    return;
                }
                voisin -> predecesseur = AppelPointeur(graphe, sommetActuel.nom);
                voisin -> marque = 1;
                Enfile(&file, *voisin);
                
            }
        }
    }
}

int Direction (struct Direction infoDirection[], char chemin[4])
{
    int i = 0;
    while ((infoDirection[i].nom[0] != chemin[0] || infoDirection[i].nom[1] != chemin[1] || infoDirection[i].nom[2] != chemin[2]) && i < NOMBRE_DE_DIRECTION)
    {
        i++;
    }
    if (i < NOMBRE_DE_DIRECTION)
    {
        return infoDirection[i].direction;
    }
    else
    {
        return -1;
    }
}



