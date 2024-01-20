#include "Repeat.h"
#include "Arduino.h"

Repeat::Repeat(): Repeat(0, 0, 0) {}
Repeat::Repeat(short x, short y, short z)
{
    this->currentAmount = 0;
    this->size = x * y * z;
    LedCoordinate tmp[this->size];
    this->array = tmp;
    for (short i = 0; i < this->size; i++)
    {
        this->array[i] = LedCoordinate(x, y, z);
    }
}

bool Repeat::addLedCoordinate(short x, short y, short z, bool red, bool green, bool blue)
{
    if (this->currentAmount < this->size)
    {
        this->array[this->currentAmount] = LedCoordinate(2, 2, 2);
        this->array[this->currentAmount].setCoords(x, y, z);
        this->array[this->currentAmount].setColor(red, green, blue);
        this->currentAmount++;
        return true;
    }
    return false;
}

void Repeat::reset()
{
    this->currentAmount = 0;
}

void Repeat::execute(short delayTime)
{
    long stop = millis() + delayTime;
    while (millis() < stop)
    {
        for (short i = 0; i < this->currentAmount; i++)
        {
            this->array[i].execute(0);
        }
    }
}



