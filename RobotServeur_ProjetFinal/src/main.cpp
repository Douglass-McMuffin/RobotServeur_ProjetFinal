#include <Arduino.h>
#include <LibRobus.h>
//#include "commande_direction.h"


//VARIABLE POUR MOUVEMENT
char intersection;
char trajet[10];
char intersection_actuelle;

//variables pour fonction lireLumiere
bool luxGauche; 
bool luxCentre;
bool luxDroite;

//variables pour fonction ControleMoteurLigne
float vGauche;
float vDroite;
float vitesse;/*vitesse desire lors des deplacements*/
//chemin //definir structure
//variables pour fonction indication_direction

// Il faut un code pour le déplacement avec le suiveur de ligne
/*

Dans Alignement : 
Une fonction qui regarder les trois capteurs sont sur du noir.
    Cette fonction

ALOHA
POUR LE MOUVEMENT DU DÉPART AU CLIENT

On suppose qu'on sait c'est quel client (le deuxième)
On suppose qu'on sait qu'on est au départ

Tant qu'il n'est pas au client

*/

#define PIN_LUMIERE_GAUCHE 50 //À changer dans le futur
#define PIN_LUMIERE_CENTRE 51 //même chose
#define PIN_LUMIERE_DROITE 52 //même chose

#define NOMBRE_DE_SOMMET 16 // À mettre à jour plus tard


struct Sommet {
    char nom; // Identifiant
    struct Sommet *voisin[NOMBRE_DE_SOMMET - 1]; // Les voisins immédiat du sommet
    int nb_voisin;
    struct Sommet *predecesseur; // Pointe vers le sommet qui s'y rend
    int marque; // la marque détermine si le sommet a déjà été vu.
};

struct File {
    struct Sommet sommets[NOMBRE_DE_SOMMET]; // Une file qui contient les sommets dans l'ordre de découverte
    int debut; // index du début
    int fin; // index de fin
};

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
    file->sommets[file->fin] = element;
    file->fin++;
}

//Pour les files, permet de prendre un element
void Defile (struct File *file, struct Sommet *element)
{
    if (file->debut <= file->fin) // Vérifie s'il reste des éléments dans la file
    {
        *element = file->sommets[file->debut];
        file->debut++;
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
void AppelElement (struct Sommet *graphe, char nom, struct Sommet *p_sommet)
{
    struct Sommet *index;
    index = graphe;
    while (index -> nom != nom)
        index++;
    *p_sommet = *index;
}

//Pour les graphes, permet de prendre l'adresse d'un sommet
void AppelPointeur (struct Sommet *graphe, char nom, struct Sommet **p_sommet)
{
    struct Sommet *index;
    index = graphe;
    while (index -> nom != nom)
        index++;
    *p_sommet = index;
}

//Permet de trouver le chemin entre deux points
void Chemin (struct Sommet *graphe, char debut, char fin, char *chemin)
{
    struct File file;
    file.debut = 0; file.fin = 0;
    struct Sommet sommetActuel;

    AppelElement(graphe, debut, &sommetActuel);
    Enfile (&file, sommetActuel);
    sommetActuel.marque = 1;
    while (file.debut <= file.fin)
    {
        Defile(&file, &sommetActuel);
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
                Enfile(&file, voisin);
                voisin.marque = 1;
            }
        }
    }
}

void InitialiserGraphe (struct Sommet *graphe)
{
    char sommets[] = "OABCDEFG01234567;O : AD;A : OB1;B : AC2;C : B3;D : OE4;E : DF5;F : EG6;G : F7;0 : O;1 : A;2 : B;3 : C;4 : D;5 : E;6 : F;7 : G;";
    int i = 0;
    int nombre_voisin;
    struct Sommet *index0;
    struct Sommet sommetActuel;
    index0 = graphe;
    while (sommets[i] != ';') // Créer tous les sommets
        {
            graphe -> nom = sommets[i];
            i++;
            graphe++;
        }
    i++;
    
    do { // Ajouter les voisins
        AppelElement(graphe, sommets[i], &sommetActuel);
        i += 4; // Skip les 3 autres caractères
        nombre_voisin = 0;
        while (sommets[i] != ';')
        {
            AppelPointeur(graphe, sommets[i], &(sommetActuel.voisin[nombre_voisin])); // Enregistre le voisin
            Serial.print(sommets[i]);
            delay(500);
            i++;
            nombre_voisin++;
        }
        i++;
        sommetActuel.nb_voisin = nombre_voisin;
        sommetActuel.marque = 0;
        index0++;

    } while (index0 != graphe);

    return;
}



void setup() {
  BoardInit();
  Serial.begin(9600); 
}

bool flag = true;
void loop() {


  if (flag)
  {
  struct Sommet graphe[NOMBRE_DE_SOMMET];
  char chemin[NOMBRE_DE_SOMMET];
  InitialiserGraphe(graphe);
  Chemin(graphe, '1', '3', chemin);
  Serial.println(chemin);
  flag = false;
  }
}
