#include <curses.h>
#include <time.h>
#include <cstdio>
#include "./Source/common/common.h"
#include "./Source/testwalk/walk_thread.h"
// #include "./Source/walk/walk_thread.h"
#include "./Source/gameController/gamecontrollerfunc.h"
#include "./Source/switch/acyut_gpio.h"

using namespace std;

pthread_t thread_id_walk;
pthread_t thread_id_gc;
pthread_t thread_id_switch;
pthread_mutex_t mutex_walkflag=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_walkstr=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_bodycommand=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_changewalkflag=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_GCData=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_pathpacket=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_switch=PTHREAD_MUTEX_INITIALIZER;

Imu imu;
double IMU_INITIAL_ANGLE;
int FACE_FOUND; // BGM Haar
WalkStructure prevwalkstr;
WalkStructure walkstr;
RoboCupGameControlData GCData;
PathPacket pathpackvar;

int main(void)
{	
	

	#ifdef SWITCH_IS_ON
        pthread_create(&thread_id_switch,NULL,switchupdate,NULL);
    #endif

			#ifdef WALK_IS_ON
				pthread_create (&thread_id_walk, NULL, walk_thread, NULL);
			#endif
		
			#ifdef GC_IS_ON
	  			pthread_create (&thread_id_gc, NULL, readGameController, NULL);
			#endif
	    
	    	#ifdef IMU_IS_ON
	    		imu.init();

	    		fstream f1;
	        	f1.open("Source/xsens/imuyaw.angle", ios::in);
	        	f1>>IMU_INITIAL_ANGLE;
	        	f1.close();
	    	#endif

	        registerXABSL();
	  		start();
			
	    	#ifdef GC_IS_ON
				pthread_join(thread_id_gc,NULL);
			#endif
		
			#ifdef WALK_IS_ON
				pthread_join(thread_id_walk,NULL);
			#endif

	#ifdef SWITCH_IS_ON
		pthread_join(thread_id_switch,NULL);
	#endif
	
	return 0;
}
