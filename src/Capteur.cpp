#include <Arduino.h>
#include <Capteur.h>

capteur::capteur(int pirSensor, int flamme)
{
    this->pirSensor = pirSensor;
    this->flamme = flamme;
}

capteur::~capteur()
{
}
void capteur::init(){
    pinMode (pirSensor, INPUT);
    pinMode (flamme, INPUT);
}

int capteur::readMouvement(){
    return digitalRead(pirSensor);
}

int capteur::readFlamme(){
    return digitalRead(flamme);
}