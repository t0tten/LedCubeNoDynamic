#ifndef ANIMATION_H
#define ANIMATION_H

#include "LedCoordinate.h"
#include "Repeat.h"

class Animation {
protected:
    LedCoordinate ledCoordinate;
    Repeat repeat;
    short x, y, z;

    /* FUNCTIONS */
    void maze(short iterations);
    void blink(short iterations);
    void worm(short iterations);
    void wormBlink(short iterations);

public:
    Animation();
    Animation(short x, short y, short z);

    void execute();
};

#endif //ANIMATION_H