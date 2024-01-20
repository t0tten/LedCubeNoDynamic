#include <iostream>
#include <string>
#include <fstream>

short size = 10;
std::string path = "out/";
std::string filename = "animation.cube";
std::ofstream file;

void animation();
std::string repeat(short dataAmount, short delayTime);
std::string ledData(short x, short y, short z, bool r, bool g, bool b, short delayTime);

void maze(short);
void blink(short);
void worm_blink(short);
void worm(short);

int main ()
{

	file.open(path + filename);
	std::cout << "---- Generating animations file ----" << std::endl;
	animation();
	std::cout << "Done, file can be found in " << path + filename << std::endl;
	file.close();
	return 0;
}

void writeLine(std::string line)
{
	if (file.is_open())
	{
		file << line + "\n";
	}
}

void animation ()
{
	maze(1);
	blink(1);
	worm_blink(1);
	worm(1);
}

void maze (short iterations)
{
	std::cout << "Generating animation: Maze" << std::endl;
	short size = 8;
	short size_x = 2;
	short size_y = 2;
	short size_z = 2;
	bool lights[8];
	for (short iteration = 0; iteration < iterations; iteration++)
    	{
        	for (short i = 0; i < size; i++) lights[i] = true;
        	short startX = std::rand() % size_x;
        	short startY = std::rand() % size_y;
        	short startZ = std::rand() % size_z;

        	for (short i = 0; i < size + 1; i++)
        	{
			writeLine(repeat(size, 1000));
            		for (short index = 0; index < size; index++)
            		{
                		short x = index % size_x;
                		short y = (index % (size_x * size_y)) / size_x;
                		short z = index / (size_y * size_x);
                		if (lights[index])    writeLine(ledData(x,y,z,1,0,0,0));
                		else                  writeLine(ledData(x,y,z,0,0,0,0));
            		}

            		if (i != size)
            		{
                		bool isFree = false;
                		short retries = 100;
                		while (!isFree && retries >= 0)
                		{
                    			short direction = std::rand() % 3;
                    			short value     = ((std::rand() % 2) == 0) ? 1 : -1;
                    			short newX      = (direction == 0) ? startX + value : startX;
                    			short newY      = (direction == 1) ? startY + value : startY;
                    			short newZ      = (direction == 2) ? startZ + value : startZ;

                    			if ((newX >= 0 && newX < size_x) &&
                        		(newY >= 0 && newY < size_y) &&
                        		(newZ >= 0 && newZ < size_z))
                    			{
                        			short index = (newZ * (size_x * size_y)) + (newY * size_x) + newX;
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
    	}
}

void blink (short iterations)
{
	std::cout << "Generating animation: Blink" << std::endl;
	short dataAmount = 8;
	short delayTime = 1000;
	for (short iteration = 0; iteration < iterations; iteration++)
    	{
		writeLine(repeat(dataAmount, delayTime));
        	for (short i = 0; i < 8; i++)
        	{
            		short x = i % 2;
            		short y = (i % 4) / 2;
            		short z = i / (2 * 2);
			writeLine(ledData(x, y, z, 0, 1, 0, 0));
        	}

		writeLine(repeat(dataAmount, delayTime));
        	for (short i = 0; i < 8; i++)
        	{
            		short x = i % 2;
            		short y = (i % 4) / 2;
            		short z = i / (2 * 2);
			writeLine(ledData(x, y, z, 0, 0, 0, 0));
        	}
    	}
}

void worm_blink (short iterations)
{
	std::cout << "Generating animation: Worm blink" << std::endl;
	short delayTime = 50;
	for (short iteration = 0; iteration < iterations; iteration++)
    	{
        	for (short i = 0; i < 8; i++)
        	{
            		short color = i % 3;
            		bool red    = (color == 0) ? true : false;
            		bool green  = (color == 1) ? true : false;
            		bool blue   = (color == 2) ? true : false;

            		short x = i % 2;
            		short y = (i % 4) / 2;
            		short z = i / (2 * 2);
			writeLine(ledData(x, y, z, red, green, blue, delayTime));

            		short ii = i - 1;
            		if (ii == -1) ii = 7;
            		short xx = ii % 2;
            		short yy = (ii % 4) / 2;
            		short zz = ii / (2 * 2);
			writeLine(ledData(x, y, z, red, green, blue, delayTime));
       	 	}
   	 }
}

void worm (short iterations)
{
	std::cout << "Generating animation: Worm" << std::endl;
	short dataAmount = 2;
	short delayTime = 1000;
	for (short iteration = 0; iteration < iterations; iteration++)
    	{
        	for (short i = 0; i < 8; i++)
        	{
			writeLine(repeat(dataAmount, delayTime));
            		short color = i % 3;
            		bool red    = (color == 0) ? true : false;
            		bool green  = (color == 1) ? true : false;
            		bool blue   = (color == 2) ? true : false;

            		short x = i % 2;
            		short y = (i % 4) / 2;
            		short z = i / (2 * 2);
			writeLine(ledData(x, y, z, red, green, blue, 0));

            		short ii = i - 1;
            		if (ii == -1) ii = 7;
            		short xx = ii % 2;
            		short yy = (ii % 4) / 2;
            		short zz = ii / (2 * 2);
			writeLine(ledData(xx, yy, zz, red, green, blue, 0));
        	}
    	}
}

std::string repeat(short dataAmount, short delayTime)
{
	return "repeat:" + std::to_string(dataAmount) + "," + std::to_string(delayTime);
}
	
std::string ledData(short x, short y, short z, bool r, bool g, bool b, short delayTime)
{
	return std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "," + std::to_string(r) + "," + std::to_string(g) + "," + std::to_string(b) + "," + std::to_string(delayTime);
}
