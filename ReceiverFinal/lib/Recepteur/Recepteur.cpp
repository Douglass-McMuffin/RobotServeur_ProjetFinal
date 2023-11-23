#include "Recepteur.h"



int ClientAssigner () 
{
    RH_ASK driver;
    uint16_t data;
    uint8_t datalen = sizeof(data);
    if (driver.recv((uint8_t*)&data, &datalen) && datalen == sizeof(data)) {
        Serial.println(data);
        return data;
  }
}
