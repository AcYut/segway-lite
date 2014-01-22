#ifndef __IMU_H
#define __IMU_H
#include "cmt2.h"
#include "cmt3.h"
#include "cmtdef.h"
#include "xsens_time.h"
#include "xsens_list.h"
#include <pthread.h>
#include "cmtscan.h"
class Imu
{
private:
	bool initialized;
	xsens::Cmt2s serial;
	xsens::Message msg, reply;
	unsigned long msgCount;
	pthread_t readerThread;
	
public:
	Imu()
	{
		initialized = false;
		roll = 0.;
		pitch = 0.;
		yaw = 0.;
		msgCount = 0;
	};
	~Imu();
	bool init();
	void __update();
	void __flush();
	bool threadActive;
	double roll, pitch, yaw;
};
#endif