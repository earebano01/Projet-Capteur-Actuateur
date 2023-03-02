#include <Arduino.h>

class capteur
{
private:
    int pirSensor;
    int flamme;

public:
    capteur(int pirSensor, int flamme);
    ~capteur();

    void init();
    int readMouvement();
    int readFlamme();
};


