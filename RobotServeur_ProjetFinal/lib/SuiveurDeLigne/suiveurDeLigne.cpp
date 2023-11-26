#include "suiveurDeLigne.h"

// La fonction devra modifier la vitesse des roues selon les capteurs

//À mettre dans le fichier .h (en bas)
/* float vGauche, vDroite;
float *p_vGauche, *p_vDroite;
p_vGauche = &vGauche;
p_vDroite = &vDroite; 
int eGauche, eDroite; */

// Inscrit les valeurs des capteurs dans les bools.
// La fonction prend 3 pointeurs pour les 3 capteurs.
// La fonction ne retourne rien. Les variables deviennent soit 0 pour quand il voit du noir et 1 pour quand il voit du blanc
void LireLumiere (bool *p_luxGauche, bool *p_luxCentre, bool *p_luxDroite)
{
    *p_luxGauche = analogRead(PIN_LUMIERE_GAUCHE) < 256;
    *p_luxCentre = analogRead(PIN_LUMIERE_CENTRE) < 300;
    *p_luxDroite = analogRead(PIN_LUMIERE_DROITE) < 256;
    //Serial.print(*p_luxDroite);
    //Serial.print(analogRead(PIN_LUMIERE_DROITE));
    //Serial.print("\n");
}

void ControleMoteurLigne (float vitesse, float *p_vGauche, float *p_vDroite, bool luxGauche, bool luxCentre, bool luxDroite)
{
    // Si le robot est sur la ligne noir (centre activé)
   
    if (!luxCentre)
    {
        //*p_vGauche = vitesse;
        //*p_vDroite = vitesse;
        if(luxGauche && luxDroite)
        {
            *p_vGauche = vitesse;
            *p_vDroite = vitesse;
        }
        else if (!luxGauche)
        {
            *p_vGauche = -vitesse/2;
            *p_vDroite = vitesse;
        }
        else 
        {
            *p_vGauche = vitesse;
            *p_vDroite = -vitesse/2;
        }
    }


    else if (!luxGauche)
    {
        *p_vGauche = -vitesse/2;
        *p_vDroite = vitesse;
       /*if(luxCentre)
        {
            *p_vGauche = -vitesse/2;
            *p_vDroite = vitesse;
        }*/
    }
   
    else if (!luxDroite)
    {
        *p_vGauche = vitesse;
        *p_vDroite = -vitesse/2;
        /*if(luxCentre)
        {
            *p_vGauche = vitesse;
            *p_vDroite = -vitesse/2;
        }*/
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
    char sommets[] = "0123456ABC;0 : A;1 : A;2 : B;3 : C;4 : A;5 : B;6 : C;A : 014B;B : 25AC;C : 36B;\0";
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
void Chemin (char debut, char fin, char *chemin)
{
    struct File file;
    file.debut = 0; file.fin = 0;
    struct Sommet *premierSommet;
    struct Sommet *voisin;
    struct Sommet sommetActuel;
    struct Sommet graphe[NOMBRE_DE_SOMMET];
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

int Direction (struct Direction infoDirection[], char chemin[3])
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

int IndexChemin (char *chemin, char intersection)
{
    int i = 0;
    for (;chemin[i] != intersection;i++);
    return i;
}




