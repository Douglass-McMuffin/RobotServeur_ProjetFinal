#include "Recepteur.h"
#include <RH_ASK.h>
#include <SPI.h>


uint16_t data;
int ClientAssigner (RH_ASK *p_driver) 
{
    uint8_t datalen = sizeof(data);
    if ((*p_driver).recv((uint8_t*)&data, &datalen) && datalen == sizeof(data)) {
        //Serial.println(data);
        return data;
  }
}
