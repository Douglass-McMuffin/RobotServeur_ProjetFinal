#ifndef GestionBouton
#define GestionBouton

#define NOMBRE_DE_PLACE 10

struct FileGestion {
    char client[NOMBRE_DE_PLACE];
    int debut;
    int fin;
} GestionClient;

int DedansClient (struct FileGestion file, char client);
void EnfileClient (struct FileGestion *file, char client);
//Pour les files, permet de prendre un element
char DefileClient (struct FileGestion *file);

#endif