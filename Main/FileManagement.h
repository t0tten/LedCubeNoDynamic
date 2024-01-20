#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#include "LedCoordinate.h"
#include "Repeat.h"
#include "Arduino.h"
#include <Regexp.h>

class FileManagement {
protected:
    LedCoordinate ledCoordinate;
    Repeat repeat;
    short x, y, z;

    int index;
    int size;

    String* file;
    String* splitArray;

    MatchState ms;

    void readNextLine();
    void translate(String line);
    void split(String line, char delimiter);

public:
    FileManagement();
    FileManagement(short x, short y, short z);

    void execute();
};

#endif //FILE_MANAGEMENT_H