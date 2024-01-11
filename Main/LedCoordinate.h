#ifndef LED_COORDINATE_H
#define LED_COORDINATE_H

class LedCoordinate {
protected:
    short   size_x, size_y, size_z;
    short   x, y, z;
    bool    red, green, blue;

    void sendData(short ledByte, short levelByte);
    void sendToRegistrer(short shift_register, short byte);

public:
    LedCoordinate();
    LedCoordinate(short x, short y, short z);

    void setCoords(short x, short y, short z);
    void setColor(bool red, bool green, bool blue);
    void execute(short delayTime);
};

#endif //LED_COORDINATE_H