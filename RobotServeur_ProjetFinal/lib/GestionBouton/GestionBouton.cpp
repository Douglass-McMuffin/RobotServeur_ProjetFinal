#include "GestionBouton.h"

int DedansBouton (struct FileBouton file, char client)
{
    for (int i = 0; i < NOMBRE_DE_BOUTON; i++)
    {
        if (client == file.client[i])
            return 1;
    }
    return 0;
}

void EnfileBouton (struct FileBouton *file, char client)
{
    if (file -> debut == ((file -> fin) + 1) % NOMBRE_DE_BOUTON) // La liste est remplie
    {
        return;
    }
    if (DedansBouton(*file, client) == 0)
    {
        file -> client[file -> fin] = client;
        file -> fin = (file -> fin + 1) % NOMBRE_DE_BOUTON;
    }
    return;
}

//Pour les files, permet de prendre un element
char DefileBouton (struct FileBouton *file)
{
    if (file -> debut != file -> fin) // Vérifie s'il reste des éléments dans la file
    {
        char client = file -> client[file -> debut];
        file -> debut = (file -> debut + 1) % NOMBRE_DE_BOUTON;
        return client;
    }
}

//Pour les files, permet de vérifier si un certain element est à l'intérieur
