#include "testBot.h"

testBot::testBot(Communication *comm)
	{
		this->comm=comm;
		wheelDiameter=105.0;
		wheelDistance=330.0;
		angularVelocity=2.6177; /* This value is for 512. 10 rounds in 24 secs */
	}