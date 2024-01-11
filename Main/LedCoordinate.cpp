#include "Animation.h"
#include "Arduino.h"

/* SHIFT REGISTERS */
#define SHIFT_REGISTERS 4
#define INSTRUCTIONS    3
/* 74HC595 Shift register */
#define DATA            0
#define CLOCK           1
#define LATCH           2
#define RESET           3

#define ALL             0
#define RED             0
#define GREEN           1
#define BLUE            2
#define LEVELS          3

const short PIN_LAYOUT[SHIFT_REGISTERS][INSTRUCTIONS] = {
  { 8,  7,  4  }, // RED
  { 6,  5,  -1 }, // GREEN
  { 3,  2,  -1 }, // BLUE
  { 10, 9,  -1 }  // Levels
};


LedCoordinate::LedCoordinate() : LedCoordinate(0, 0, 0) {}
LedCoordinate::LedCoordinate(short x, short y, short z)
{
    this->size_x    = x;
    this->size_y    = y;
    this->size_z    = z;
    this->x         = 0;
    this->y         = 0;
    this->z         = 0;

    for (short shiftRegister = 0; shiftRegister < SHIFT_REGISTERS; shiftRegister++) {
        for (short pinIndex = 0; pinIndex < INSTRUCTIONS; pinIndex++) {
            if (PIN_LAYOUT[shiftRegister][pinIndex] != -1) {
            pinMode(PIN_LAYOUT[shiftRegister][pinIndex], OUTPUT);
            }
        }
    }
}

void LedCoordinate::setCoords(short x, short y, short z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void LedCoordinate::setColor(bool red, bool green, bool blue)
{
    this->red   = red;
    this->green = green;
    this->blue  = blue;
}

void LedCoordinate::execute(short delayTime)
{
    short index     = (this->y * this->size_y) + this->x;
    short ledByte   = 1;
    ledByte         = ledByte << index;

    short levelByte = 1;
    levelByte       = levelByte << this->z;
    levelByte       = ~levelByte;

    this->sendData(ledByte, levelByte);
    delay(delayTime);
}

void LedCoordinate::sendData(short ledByte, short levelByte)
{
    short redData   = this->red     ? ledByte : 0;
    short greenData = this->green   ? ledByte : 0;
    short blueData  = this->blue    ? ledByte : 0;

    if (red)    redData     = ledByte;
    if (green)  greenData   = ledByte;
    if (blue)   blueData    = ledByte;

    digitalWrite(PIN_LAYOUT[ALL][LATCH], LOW);
    shiftOut(PIN_LAYOUT[RED][DATA], PIN_LAYOUT[RED][CLOCK], MSBFIRST, redData);
    shiftOut(PIN_LAYOUT[GREEN][DATA], PIN_LAYOUT[GREEN][CLOCK], MSBFIRST, greenData);
    shiftOut(PIN_LAYOUT[BLUE][DATA], PIN_LAYOUT[BLUE][CLOCK], MSBFIRST, blueData);
    shiftOut(PIN_LAYOUT[LEVELS][DATA], PIN_LAYOUT[LEVELS][CLOCK], MSBFIRST, levelByte);
    digitalWrite(PIN_LAYOUT[ALL][LATCH], HIGH);
}