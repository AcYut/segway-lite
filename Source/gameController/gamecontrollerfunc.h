/*
for using it
include this file and make a thread with the readGameController() function
then read data by using GCData, and putting mutex locks while doing so.

	pthread_t thread_id_gc;

    pthread_create (&thread_id_gc, NULL, readGameController, NULL);
	
	
	to close the thread after the main function is done-->
     void *status_gc; pthread_join (thread_id_gc, &status_gc);
*/
#ifndef GAMECONTFUNC_H
#define GAMECONTFUNC_H
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "../common/common.h"
#include <pthread.h>
#include <string.h>
#include "RoboCupGameControlData.h" 
//RoboCupGameControlData GCData; pranet: shifted to common.h as global

// //pranet: common.h	

//pthread_mutex_t mutex_GCData=PTHREAD_MUTEX_INITIALIZER; pranet: shifted to common.h,run.cpp

//Function used by readGameController
void *get_in_addr(struct sockaddr *sa);
/////////
void* readGameController(void*);

#endif