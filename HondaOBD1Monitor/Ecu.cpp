#include "Arduino.h"
#include "Ecu.h"

// OBD1 - These adresses are for Crome >= 1.4 dataloger plugin aka QD2
#define ECT_CROME14     0x1D
#define IAT_CROME14     0x1B
#define O2_CROME14      0x20
#define BARO_CROME14    0x1E
#define MAP_CROME14     0x14
#define TPS_CROME14     0x15
#define RPMLOW_CROME14  0x10
#define RPMHIGH_CROME14 0x11
#define LOCAM_CROME14   0x12
#define HICAM_CROME14   0x13
#define COL_CROME14     0x16
#define VSS_CROME14     0x1C
#define VTEC_CROME14    0x22
#define IGN_CROME14     0x19
#define INJLOW_CROME14  0x17
#define INJHIGH_CROME14 0x18
#define KNOCK_CROME14   0x1A
#define BATT_CROME14    0x1F

#define injsize 240

unsigned int ecuTimeout=10000;


Ecu::Ecu(){
}

byte Ecu::readEcu(byte ecuAddress){  
  
  Serial.flush();
  Serial.write(ecuAddress);
  unsigned int time=0;
  while(Serial.available() == 0 && time < ecuTimeout) time+=1;
  if (time >= ecuTimeout) return 0x00;  
  else return Serial.read();
}

unsigned int Ecu::getRpm(){
  unsigned int rpmLowRaw=readEcu(RPMLOW_CROME14);
  unsigned int rpmHighRaw=readEcu(RPMHIGH_CROME14); 
  return 1851562/((rpmHighRaw * 256) + rpmLowRaw);  
}

float Ecu:: getBattery(){
  float batteryRaw = readEcu(BATT_CROME14);
  return (26.0 * batteryRaw) / 270.0;
}

float Ecu::calcTempInCelsius(float raw){
  raw = raw / 51;
  raw = (0.1423*pow(raw,6)) - (2.4938*pow(raw,5))  + (17.837*pow(raw,4)) - (68.698*pow(raw,3)) + (154.69*pow(raw,2)) - (232.75*raw) + 284.24;
  return ((raw - 32)*5)/9;
}

int Ecu:: getIat(){
  float iatRaw = readEcu(IAT_CROME14);
  return calcTempInCelsius(iatRaw);                  
}

int Ecu::getEct(){
  float ectRaw = readEcu(ECT_CROME14);
  return calcTempInCelsius(ectRaw);
}

int Ecu::getTps(){
  float tpsRaw = readEcu(TPS_CROME14);
  tpsRaw = (0.4716  * tpsRaw) - 11.3184;
  return constrain(tpsRaw, 0, 100);    
 
}

int Ecu::getO2(){
  int o2Raw = readEcu(O2_CROME14);  
  return (2*o2Raw) + 10;
}
    
int Ecu::getVss(){
  float vssRaw = readEcu(VSS_CROME14);
  return vssRaw/60;
}

float Ecu::getMap(){ //in mBar
  float mapRaw = readEcu(MAP_CROME14);
  return (1764/255)*mapRaw; 
}

float Ecu::getInj(){
  unsigned int InjLowRaw = readEcu(INJLOW_CROME14);
  unsigned int InjHighRaw = readEcu(INJHIGH_CROME14); 
  float injRaw = (InjHighRaw * 256) + InjLowRaw;
  return injRaw / 352;  
}

int Ecu::getIgn(){
  unsigned int ignRaw =readEcu(IGN_CROME14);
  return (0.25 * ignRaw) - 6;
}

float Ecu::getDutyCycle(){
  float rpm = getRpm();
  float inj = getInj();
  return (rpm * inj) / 1200;
}

float Ecu::getInstantConsumption(){
  float hundredkm = ((60 / getVss()) * 100) / 60;     //minutes needed to travel 100km
  float fuelc = (hundredkm * ((injsize / 100) * getDutyCycle())) / 1000;     
  return constrain(fuelc, 0.0001, 50.0);
}

int Ecu::getVtec(){
  int vtec = readEcu(VTEC_CROME14);
  if (vtec == 67) return 1;
  else return 0;
}













