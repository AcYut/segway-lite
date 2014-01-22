#ifndef TEST_BOT_H
#define TEST_BOT_H
#include "communication.h"
class testBot
{

private:
	Communication *comm;
	double wheelDiameter;
	double wheelDistance;
	double angularVelocity;

	friend class Walk;

	
public:
	testBot(Communication *comm);
};

#endif