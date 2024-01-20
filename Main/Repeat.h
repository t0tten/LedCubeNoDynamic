#ifndef REPEAT_H
#define REPEAT_H

#include "LedCoordinate.h"

class Repeat {
protected:
    short currentAmount;
    short size;
    LedCoordinate* array;
    short x, y, z;

public:
    Repeat();
    Repeat(short x, short y, short z);

    bool addLedCoordinate(short x, short y, short z, bool red, bool green, bool blue);
    void reset();
    
    void execute(short delayTime);
};

#endif //REPEAT_H