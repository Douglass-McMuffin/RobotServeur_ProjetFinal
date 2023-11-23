#include <Arduino.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
#include "Recepteur.h"

RH_ASK driver;

uint16_t data;

void setup()
{
    Serial.begin(9600);	// Debugging only
    Serial.println("init...");
    if (!driver.init())
         Serial.println("init failed");
}

void loop() {
    uint16_t xyz;
    xyz = ClientAssigner();
    Serial.println(xyz);
}