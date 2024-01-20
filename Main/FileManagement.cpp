#include "FileManagement.h"

#define LED_DATA    "^[ ]*[0-9]*[ ]*,[ ]*[0-9]*[ ]*,[ ]*[0-9]*[ ]*,[ ]*[0-9]*[ ]*,[ ]*[0-9]*[ ]*,[ ]*[0-9]*[ ]*,[ ]*[0-9]*[ ]*$"
#define REPEAT      "^[ ]*repeat[ ]*:[ ]*[0-9]*[ ]*,[ ]*[0-9]*[ ]*$"

FileManagement::FileManagement() : FileManagement(0, 0, 0) {}
FileManagement::FileManagement(short x, short y, short z)
{
    this->x             = x;
    this->y             = y;
    this->z             = z;
    this->index         = 0;
    this->size          = 4;
    this->ledCoordinate = LedCoordinate(x, y, z);
    this->repeat        = Repeat(x, y, z);
    this->file          = new String[this->size];
    this->splitArray    = new String[7];

    this->file[0] = "1,0,1,0,1,0,1000";
    this->file[1] = "repeat: 2, 1000";
    this->file[2] = "1,0,0,1,0,0,0";
    this->file[3] = "1,0,1,1,0,0,0";
}

void FileManagement::execute()
{
    this->index = 0;
    while (this->index < this->size)
    {
        this->readNextLine();
    }
}

/* PRIVATE */
void FileManagement::readNextLine()
{
    this->translate(this->file[this->index++]);
}

void FileManagement::translate(String line)
{
    this->ms.Target(line.c_str());

    if (this->ms.Match(LED_DATA) == REGEXP_MATCHED)
    {
        this->split(line, ',');
        this->ledCoordinate.setCoords(this->splitArray[0].toInt(), this->splitArray[1].toInt(), this->splitArray[2].toInt());
        this->ledCoordinate.setColor(this->splitArray[3].toInt(), this->splitArray[4].toInt(), this->splitArray[5].toInt());
        this->ledCoordinate.execute(this->splitArray[6].toInt());
    }
    else if (this->ms.Match(REPEAT) == REGEXP_MATCHED)
    {
        this->repeat.reset();
        this->split(line, ':');
        this->split(this->splitArray[1], ',');
        short iterations   = this->splitArray[0].toInt();
        short delayTime    = this->splitArray[1].toInt();

        if (iterations > 0)
        {
            for (short i = 0; i < iterations; i++)
            {
                line = this->file[this->index++];
                this->ms.Target(line.c_str());
                if (this->ms.Match(LED_DATA) == REGEXP_MATCHED)
                {
                    this->split(line, ',');
                    this->repeat.addLedCoordinate(this->splitArray[0].toInt(), this->splitArray[1].toInt(), this->splitArray[2].toInt(), this->splitArray[3].toInt(), this->splitArray[4].toInt(), this->splitArray[5].toInt());
                }
            }
        }
        this->repeat.execute(delayTime);
    }
    else {
        this->ledCoordinate.setCoords(0, 0, 0);
        this->ledCoordinate.setColor(1, 0, 0);
        this->ledCoordinate.execute(1000);
    }
}

void FileManagement::split(String line, char delimiter)
{
    // Reset array
    for (short i = 0; i < 7; i++) this->splitArray[i] = "";

    short arrayPos = 0;
    short index = 0;
    while (line[index] != '\0')
    {
        if (line[index] != delimiter && line[index] != ' ')
        {
            this->splitArray[arrayPos] += line[index];
        }
        else if (line[index] == delimiter)
        {
            arrayPos++;
        }
        index++;
    }
}
