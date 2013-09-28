#ifndef Ecu_h
#define Ecu_h

#include "Arduino.h"

class Ecu
{
  public:
    Ecu();
    unsigned int getRpm();
    float getBattery();    
    int getIat();
    int getEct();
    int getTps();
    int getO2();
    int getVss();
    float getMap();
    float getInj();
    int getIgn();
    float getDutyCycle();
    float getInstantConsumption();
    int getVtec();    
    
  private:
    byte readEcu(byte ecuAddress);
    float calcTempInCelsius(float raw);
};

#endif
