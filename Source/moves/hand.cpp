#include "hand.h"

Hand::Hand(int hand, Communication* comm)
{
	this->comm = comm;
	for (int i = 0; i < HAND_MOTORS_COUNT; ++i)
	{
		m[i] = new Motor(MX64, hand*20+7+i, this->comm);
	}
	this->hand = hand;
}

void Hand::setIDList(int* idList, int n)
{
	for (int i = 0; i < n && i < HAND_MOTORS_COUNT; ++i)
	{
		m[i]->setIDSoft(idList[i]);
	}
}

int Hand::setSpeed(int speed)
{
	for(int i=0; i< HAND_MOTORS_COUNT; i++)
	{
		m[i]->setMovingSpeedSync(speed);
	}

}

int Hand::getLoad()
{
	for (int i = 0; i < HAND_MOTORS_COUNT; ++i)
	{
		m[i]->getPresentLoad();
	}
}

int* Hand::pingHand()
{
	for (int i = 0; i < HAND_MOTORS_COUNT; ++i)
	{
		m[i]->ping();
	}
}

int Hand::getMotorLoad(int motor)
{
	m[motor]->getPresentLoad();
}

void Hand::init()
{
	double pos[HAND_MOTORS_COUNT];
	if(hand==LEFT)
	{
		pos[0]=4096-2172;
		pos[1]=4096-1040;
		pos[2]=1792;
		pos[3]=4096-2198;
	}
	else
	{
		pos[0]=2172;
		pos[1]=1040;
		pos[2]=4096-1792;
		pos[3]=2048;
	}
	

	for (int i = 0; i < HAND_MOTORS_COUNT; ++i)
	{
		m[i]->setGoalPositionSync(pos[i]);
	}
}

void Hand::setGoalPositionSync(int* pos)
{

	// pos[0]=2048;
	// 	pos[1]=4096-3071;
	// 	pos[2]=4096-1792;
	// 	pos[3]=2048;
	for (int i = 0; i < HAND_MOTORS_COUNT; ++i)
	{
		m[i]->setGoalPositionSync(pos[i]);
	}
}

void Hand::torqueOFF()
{
	for (int i = 0; i < HAND_MOTORS_COUNT; ++i)
	{
		m[i]->torqueDisable();
	}
}
void Hand::torqueON()
{
	for (int i = 0; i < HAND_MOTORS_COUNT; ++i)
	{
		m[i]->torqueEnable();
	}
}

void Hand::readMotorValues(int* arr)
{
	int val[4];
	// printf("Entered\n");


	

	for(int i = 0; i < HAND_MOTORS_COUNT; ++i)
	{
		if(i == 2) continue;

		val[i] = m[i]->getPresentPosition();
		usleep(10000);
		while(val[i] == -1337)
		{
			val[i] = m[i]->getPresentPosition();	
			usleep(10000);
		}
	}
	// for (int i = 0; i < HAND_MOTORS_COUNT; ++i)
	// {

	// 	printf("Reading motor %d\n", i);
	// 	val[3]=m[3]->getPresentPosition();
	// }



	printf("%d %d %d\n",val[0],val[1],val[3]);

	if(arr != NULL)
	{
		arr[0] = val[0];
		arr[1] = val[1];
		arr[2] = val[3];
	}
	// printf("Exited\n");
}
