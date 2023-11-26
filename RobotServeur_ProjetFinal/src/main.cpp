#include <RH_RF69.h>
#include <SPI.h>

#include <Arduino.h>
#include <LibRobus.h>
//#include "commande_direction.h"
#include "MouvementInitialisateur.h"
#include "drinkSelection.h"
#include "Recepteur.h"
#include "servo_driver.h"



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
float vitesse;
//vitesse desire lors des deplacements

char intersectionDebut;
char intersectionFin;

//char client;

bool arret; // est vrai si le robot ne bouge pas

char intersectionActuelle;

// variables prise de commande(choix)
int counter = 1000001, aLastState, aState, positionX, positionY, globalState = 0;
int drink;
int client = 0;
int condition = 0;


char chemin[NOMBRE_DE_SOMMET];
struct Direction infoDirection[NOMBRE_DE_DIRECTION];


void setup() {
  BoardInit();
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
  pinMode (inputSW, INPUT_PULLUP);
  aLastState = digitalRead(outputA); 

  DISPLAY_Clear();
  menuInit(counter,&positionX,&positionY);
  InitialiserVariableMouvement(&vitesse, &vGauche, &vDroite, infoDirection, &intersection_actuelle, &intersectionDebut, &intersectionFin, &arret);
}


void loop() {
  //activate_stepper(100);
  //deactivate_stepper();
  //set_stepper_dir(PUSH_CAN);
  MouvementGlobal(infoDirection, chemin, &vitesse, &vGauche, &vDroite, &luxGauche, &luxCentre, &luxDroite, &intersection_actuelle, &intersectionDebut, &intersectionFin, &arret);
  //drink = selection(&counter, &aLastState, &aState, &positionX, &positionY, &globalState);
  if (client == 0)
  {
  //client = ClientAssigner();
  // Au pire 
  client = 2;
  }
  if (client != 0)
  {
    // Code pour 1 client à la fois
    if (condition == 0)
    {
      intersectionFin = client + 48;
      condition++;
    } else if (condition == 1)
    {
      if (arret)
        condition++;
    } else if (condition == 2)
    {
      //On est devant le client pour prendre la commande
      //drink = selection(&counter, &aLastState, &aState, &positionX, &positionY, &globalState);
      drink = 6;
      if (drink != 7)
      {
        intersectionFin = drink + 48;
        condition++;
      } else {
        intersectionFin = '0';
        condition = 0;
        client = 0;
      }
    } else if (condition == 3)
    {
      if (arret)
        condition++;
    } else if (condition == 4)
    {
      //Il faut prendre le drink
      //set_stepper_dir(PULL_CAN);
      //activate_stepper(100);
      delay(1000);
      //deactivate_stepper();
      intersectionFin = client + 48;
      condition++;
    } else if (condition == 5)
    {
      if (arret)
        condition++;
    } else if (condition == 6)
    {
      //On est devant le client avec la cannette
      //set_stepper_dir(PUSH_CAN);
      //activate_stepper(100);
      delay(1000);
      //deactivate_stepper();
      intersectionFin = '0';
      client = 0;
      condition = 0;
    }

  }
  Serial.println(client);

  
  //Serial.print( selection(&counter, &aLastState, &aState, &positionX, &positionY, &globalState));


  //client = /*Vérifier bouton ClientAssigner()*/;
  //if (client != '0');
  //{
  //  EnfileClient(*GestionClient, client);
  //}

}