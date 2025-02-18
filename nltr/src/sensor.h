#ifndef _sensor_h
#define _sensor_h

#include <Arduino.h>

class Sensor
{
public:
    Sensor(int *pins, int pin_size, int threshold);
    void setup();
    bool isBlack(int pin);
    int state();
private:
    int *pins;
    int pin_size;
    int values[100];
    int threshold;
};

Sensor::Sensor(int *pins, int pin_size, int threshold) {
    this->pins = pins;
    this->pin_size = pin_size;
    this->threshold = threshold;
}

void Sensor::setup() {
    for (int i = 0; i < pin_size; i++)pinMode(pins[i], INPUT);
}

bool Sensor::isBlack(int pin) {
    return analogRead(pin) > threshold;
}

int Sensor::state() {
    int state = 0;
    for (int i = 0; i < pin_size; i++)
        if (isBlack(pins[i]))
            state |= 1 << i;
    return state;
}


#endif