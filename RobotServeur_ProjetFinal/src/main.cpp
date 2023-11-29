#include <RH_ASK.h>
#include <SPI.h>

#include <Arduino.h>
#include <LibRobus.h>
#include "MouvementInitialisateur.h"
#include "drinkSelection.h"
#include "Recepteur.h"
#include "servo_driver.h"
#include "GestionBouton.h"

RH_ASK driver;


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
char client;
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
  
  if (!driver.init())
    Serial.println("Init failed");
  deactivate_stepper();
  DISPLAY_Clear();
  menuInit(counter,&positionX,&positionY);
  InitialiserVariableMouvement(&vitesse, &vGauche, &vDroite, infoDirection, &intersection_actuelle, &intersectionDebut, &intersectionFin, &fileCirculaire, &arret);
}


void loop() {
  MouvementGlobal(infoDirection, chemin, &vitesse, &vGauche, &vDroite, &luxGauche, &luxCentre, &luxDroite, &intersection_actuelle, &intersectionDebut, &intersectionFin, &arret);
  
  
  client = ClientAssigner(&driver) + 48;
  if (48 + 1 <= client && client <= 48 + 3)
    EnfileClient(&fileCirculaire, client, false);
  if (arret)
  {
    if (48 + 1 <= intersectionActuelle && intersectionActuelle <= 48 + 3)
    {
    //On est devant un client
      client = DefileClient(&fileCirculaire);
      if (!aCanette)
      {
        //On n'a pas de cannette avec nous
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
      //On est devant un drink
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
  //Serial.println(client);
  /*Serial.print(analogRead(PIN_LUMIERE_GAUCHE));
  Serial.print(", ");
  Serial.print(analogRead(PIN_LUMIERE_CENTRE));
  Serial.print(", ");
  Serial.println(analogRead(PIN_LUMIERE_DROITE));*/
  //Serial.print(luxGauche);
  //Serial.print(", ");
  //Serial.print(luxCentre);
  //Serial.print(", ");
  //Serial.println(luxDroite);
}