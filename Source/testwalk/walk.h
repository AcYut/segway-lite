#ifndef _WALK_H_
#define _WALK_H_

#include "testBot.h"
#include "communication.h"
#include "commondefswalk.h"
#include <stdlib.h>

#define broadcast_id 0xfe
#define id1 0
#define id2 1 


typedef uint8_t byte;





/* for friend access */
class testBot;

enum {SSP,DSP};

class Walk
{
	private:
	testBot* bot;
	double WHEELDIAmm;
	double WHEELDIST;
	double omega;
	public:
	Walk(testBot* bot);
	// float accelerate();
	// float velocity();
	// float velocity2();
	// float decelerate();
	// float turnleft(float theta);
	// float turnright(float theta);


	void move(float r,float theta);
	int sync_write_data_motor(int mode, int speed);
	


};
// void testBotWalk1(int cmd,int speed);
// int checksum(int size);
// int write_packet(byte *packet, int length);
// void ftdi_bootup();



#endif
