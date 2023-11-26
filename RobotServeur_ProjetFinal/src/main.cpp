#include <RH_RF69.h>
#include <SPI.h>

#include <Arduino.h>
#include <LibRobus.h>
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
bool aCanette = false;

char intersectionActuelle;

// variables prise de commande(choix)
int counter = 1000001, aLastState, aState, positionX, positionY, globalState = 0;
char drink;
char client = 0;
int condition = 0;


char chemin[NOMBRE_DE_SOMMET];
struct Direction infoDirection[NOMBRE_DE_DIRECTION];
struct FileGestion fileCirculaire;


void setup() {
  BoardInit();
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
  pinMode (inputSW, INPUT_PULLUP);
  aLastState = digitalRead(outputA); 

  DISPLAY_Clear();
  menuInit(counter,&positionX,&positionY);
  InitialiserVariableMouvement(&vitesse, &vGauche, &vDroite, infoDirection, &intersection_actuelle, &intersectionDebut, &intersectionFin, &fileCirculaire, &arret);
}


void loop() {
  //activate_stepper(100);
  //deactivate_stepper();
  //set_stepper_dir(PUSH_CAN);
  MouvementGlobal(infoDirection, chemin, &vitesse, &vGauche, &vDroite, &luxGauche, &luxCentre, &luxDroite, &intersection_actuelle, &intersectionDebut, &intersectionFin, &arret);
  //drink = selection(&counter, &aLastState, &aState, &positionX, &positionY, &globalState);
  
  client = ClientAssigner() + 48;
  EnfileClient(&fileCirculaire, client, false);
  if (arret)
  {
    if (48 + 1 <= intersectionActuelle && intersectionActuelle <= 48 + 3)
    {
      client = DefileClient(&fileCirculaire);
      if (!aCanette)
      {
        drink = selection(&counter, &aLastState, &aState, &positionX, &positionY, &globalState) + 48;
        if (drink != '7')
        {
          EnfileClient(&fileCirculaire, drink, true);
          EnfileClient(&fileCirculaire, client, true);
        }
      } else {
        //On est devant le client avec la cannette
        //set_stepper_dir(PUSH_CAN);
        //activate_stepper(100);
        delay(1000);
        //deactivate_stepper();
        aCanette = false;
      }
    } else if (48 + 4 <= intersectionActuelle && intersectionActuelle <= 48 + 6)
    {
      drink = DefileClient(&fileCirculaire);
      //Il faut prendre le drink
      //set_stepper_dir(PULL_CAN);
      //activate_stepper(100);
      delay(1000);
      //deactivate_stepper();
      aCanette = true;
    }
    intersectionFin = LireClient(fileCirculaire);
  }
  Serial.println(client);

  
  //Serial.print( selection(&counter, &aLastState, &aState, &positionX, &positionY, &globalState));


  //client = /*Vérifier bouton ClientAssigner()*/;
  //if (client != '0');
  //{
  //  EnfileClient(*GestionClient, client);
  //}

}