#ifndef __PROGRAM_H_DEFINED__
#define __PROGRAM_H_DEFINED__

#include <cstdint>

#include "Interface.h"

class Program
{
public:
	Program(ICube*, IUtil*);
	~Program();
	void setup();
	void loop();

private:
	ICube* cube;
	IUtil* util;
	uint16_t count;
};

#endif // !__PROGRAM_H_DEFINED__
