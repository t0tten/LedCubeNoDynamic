#include "Animation.h"
#include "Arduino.h"

Animation::Animation()
{
    ledCoordinate   = LedCoordinate();
    repeat          = Repeat();
}

Animation::Animation(short x, short y, short z)
{
    repeat          = Repeat(x, y, z);
    ledCoordinate   = LedCoordinate(x, y, z);
    this->x         = x;
    this->y         = y;
    this->z         = z;
    randomSeed(analogRead(0));
    this->size = this->x * this->y * this->z;
    this->lights = new bool[this->size];
}

void Animation::execute()
{
    this->worm(4);
    this->maze(1);
    this->wormBlink(4);
    this->blink(4);
}

/* ANIMATIONS */
void Animation::maze(short iterations)
{
    /* MAZE */
    for (short iteration = 0; iteration < iterations; iteration++)
    {
        for (short i = 0; i < this->size; i++) this->lights[i] = true;
        short startX = random(this->x);
        short startY = random(this->y);
        short startZ = random(this->z);
        for (short i = 0; i < this->size + 1; i++)
        {
            repeat.reset();
            for (short index = 0; index < this->size; index++)
            {
                short x = index % this->x;
                short y = (index % (this->y * this->y)) / this->x;
                short z = index / (this->z * this->z);
                if (this->lights[index])    repeat.addLedCoordinate(x, y, z, true, false, false);
                else                        repeat.addLedCoordinate(x, y, z, false, false, false);
            }
            repeat.execute(1000);

            if (i != this->size)
            {
                bool isFree = false;
                short retries = 100;
                while (!isFree && retries >= 0)
                {
                    short direction = random(3);
                    short value     = (random(2) == 0) ? 1 : -1;
                    short newX      = (direction == 0) ? startX + value : startX;
                    short newY      = (direction == 1) ? startY + value : startY;
                    short newZ      = (direction == 2) ? startZ + value : startZ;
                    
                    if ((newX >= 0 && newX < this->x) &&
                        (newY >= 0 && newY < this->y) &&
                        (newZ >= 0 && newZ < this->z))
                    {
                        short index = (newZ * (this->x * this->y)) + (newY * this->x) + newX;
                        if (this->lights[index])
                        {
                            isFree = true;
                            this->lights[index] = false;

                            startX = newX;
                            startY = newY;
                            startZ = newZ;
                        }
                    }
                    retries--;
                }

                if (!isFree)
                {
                    break;
                }
            }
        }
    }
}

void Animation::blink(short iterations)
{
    /* BLINK */
    for (short iteration = 0; iteration < iterations; iteration++)
    {
        repeat.reset();
        for (short i = 0; i < 8; i++)
        {
            short x = i % 2;
            short y = (i % 4) / 2;
            short z = i / (2 * 2);
            repeat.addLedCoordinate(x, y, z, true, false, false);
        }
        repeat.execute(800);
        
        repeat.reset();
        for (short i = 0; i < 8; i++)
        {
            short x = i % 2;
            short y = (i % 4) / 2;
            short z = i / (2 * 2);
            repeat.addLedCoordinate(x, y, z, false, false, false);
        }
        repeat.execute(150);
    }
}
void Animation::worm(short iterations)
{
    /* WORM */
    for (short iteration = 0; iteration < iterations; iteration++)
    {
        for (short i = 0; i < 8; i++)
        {
            repeat.reset();
            short color = i % 3;
            bool red    = (color == 0) ? true : false;
            bool green  = (color == 1) ? true : false;
            bool blue   = (color == 2) ? true : false;
            ledCoordinate.setColor(red, green, blue);

            short x = i % 2;
            short y = (i % 4) / 2;
            short z = i / (2 * 2);
            repeat.addLedCoordinate(x, y, z, red, green, blue);

            short ii = i - 1;
            if (ii == -1) ii = 7;
            short xx = ii % 2;
            short yy = (ii % 4) / 2;
            short zz = ii / (2 * 2);
            repeat.addLedCoordinate(xx, yy, zz, red, green, blue);
            repeat.execute(50);
        }
    }
}

void Animation::wormBlink(short iterations)
{
    /* WORM - BLINK */
    for (short iteration = 0; iteration < iterations; iteration++)
    {
        for (short i = 0; i < 8; i++)
        {
            short color = i % 3;
            bool red    = (color == 0) ? true : false;
            bool green  = (color == 1) ? true : false;
            bool blue   = (color == 2) ? true : false;
            ledCoordinate.setColor(red, green, blue);

            short x = i % 2;
            short y = (i % 4) / 2;
            short z = i / (2 * 2);
            ledCoordinate.setCoords(x, y, z);
            ledCoordinate.execute(50);

            short ii = i - 1;
            if (ii == -1) ii = 7;
            short xx = ii % 2;
            short yy = (ii % 4) / 2;
            short zz = ii / (2 * 2);
            ledCoordinate.setCoords(xx, yy, zz);
            ledCoordinate.execute(50);
        }
    }
}


