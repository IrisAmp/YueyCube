#include "Program.h"
#include "Arduino.h"
#include <cstdint>
#include <random>

std::default_random_engine engine = std::default_random_engine();
std::uniform_int_distribution<unsigned int> dist512 = std::uniform_int_distribution<unsigned int>(0, 511);
std::uniform_int_distribution<unsigned int> dist256a = std::uniform_int_distribution<unsigned int>(0xC8, 0xFF);
std::uniform_int_distribution<unsigned int> dist256b = std::uniform_int_distribution<unsigned int>(0x00, 0xC7);
std::uniform_int_distribution<unsigned int> dist100 = std::uniform_int_distribution<unsigned int>(0, 100);

uint32_t getRandomColor() {
    return
        dist256b(engine) << 16 |
        dist256a(engine) << 8  |
        0xFF;
}

uint32_t dimColor(uint32_t color) {
    uint32_t parts [3] = {
        (color & 0xFF0000) >> 16,
        (color & 0x00FF00) >> 8,
        (color & 0x0000FF)
    };

    for (unsigned int i = 0; i < 3; ++i) {
        if (parts[i] < 4) {
            parts[i] = 0;
        } else {
            parts[i] -= 4;
        }
    }

    return (parts[0] << 16 | parts[1] << 8 | parts[2]);
}

Program::Program(ICube* _cube, IUtil* _util)
	: cube(_cube)
  , util(_util)
	, count(0)
{
}

Program::~Program()
{

}

void Program::setup()
{
  cube->setPixelIndex(0, 0xFFFFFF);
  cube->show();
  delay(1000);
}

void Program::loop()
{
	for (uint16_t i = 0; i < 512; i++)
	{
    	uint32_t c = cube->getPixelIndex(i);
    	if (c > 0)
    	{
    	    c = dimColor(c);
	        cube->setPixelIndex(i, c);
    	}
	}
	for (int i = 0; i < 50; ++i)
	{
	    if (dist100(engine) < 1)
	    {
	        cube->setPixelIndex(dist512(engine), getRandomColor());
	    }
	}
	cube->show();
	++count;
}
