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
        if (element.nom == file.sommets[i].nom)
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
                voisin.marque = true;
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
        index0 -> marque = false;
        index0++;

    } while (index0 != graphe);

    return;
}

