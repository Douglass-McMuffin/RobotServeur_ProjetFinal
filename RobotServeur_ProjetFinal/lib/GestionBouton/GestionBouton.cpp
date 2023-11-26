#include "GestionBouton.h"

int DedansClient (struct FileGestion file, char client)
{
    for (int i = file.debut; (i % NOMBRE_DE_PLACE) != ((file.fin + 1) % NOMBRE_DE_PLACE) ; i++)
    {
        if (client == file.client[i])
            return 1;
    }
    return 0;
}

void EnfileClient (struct FileGestion *file, char client)
{
    if (file -> debut == ((file -> fin) + 1) % NOMBRE_DE_PLACE) // La liste est remplie
    {
        return;
    }
    if (DedansClient(*file, client) == 0)
    {
        file -> client[file -> fin] = client;
        file -> fin = (file -> fin + 1) % NOMBRE_DE_PLACE;
    }
    return;
}

//Pour les files, permet de prendre un element
char DefileClient (struct FileGestion *file)
{
    if (file -> debut != file -> fin) // Vérifie s'il reste des éléments dans la file
    {
        char client = file -> client[file -> debut];
        file -> debut = (file -> debut + 1) % NOMBRE_DE_PLACE;
        return client;
    }
}

//Pour les files, permet de vérifier si un certain element est à l'intérieur