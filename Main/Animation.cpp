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
}

void Animation::execute()
{
    /* WORM - BLINK */
    for (short n = 0; n < 4; n++)
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

    /* MAZE */
    bool lights[8] = { true, true, true, true, true, true, true, true };
    short startX = random(2);
    short startY = random(2);
    short startZ = random(2);
    for (short i = 0; i < 9; i++)
    {
        repeat.reset();
        for (short index = 0; index < 8; index++)
        {
            short x = index % 2;
            short y = (index % 4) / 2;
            short z = index / (2 * 2);
            if (lights[index])
            {
                repeat.addLedCoordinate(x, y, z, true, false, false);
            }
            else
            {
                repeat.addLedCoordinate(x, y, z, false, false, false);
            }
        }
        repeat.execute(1000);

        if (i != 8)
        {
            bool isFree = false;
            short retries = 100;
            while (!isFree && retries >= 0)
            {
                short direction = random(3);
                short value = (random(2) == 0) ? 1 : -1;

                short newX = (direction == 0) ? startX + value : startX;
                short newY = (direction == 1) ? startY + value : startY;
                short newZ = (direction == 2) ? startZ + value : startZ;

                short index = ((newZ) * newY * this->y) + newX;
                if (index >= 0 && index < 8)
                {
                    if (lights[index])
                    {
                        isFree = true;
                        lights[index] = false;

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

    /* WORM */
    for (short n = 0; n < 4; n++)
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

    /* BLINK */
    for (short n = 0; n < 4; n++)
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


