/*
for using it
include this file and make a thread with the readGameController() function
then read data by using GCData, and putting mutex locks while doing so.

    pthread_t thread_id_gc;

    pthread_create (&thread_id_gc, NULL, readGameController, NULL);
    
    
    to close the thread after the main function is done-->
     void *status_gc; pthread_join (thread_id_gc, &status_gc);
*/

#include "gamecontrollerfunc.h"

//#include "RoboCupGameControlData.h"
//RoboCupGameControlData GCData; pranet: shifted to common.h as global

// //pranet: common.h   

//pthread_mutex_t mutex_GCData=PTHREAD_MUTEX_INITIALIZER; pranet: shifted to common.h,run.cpp

//Function used by readGameController
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
/////////
void* readGameController(void*)
{
    printf("Game controller thread made\n");
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;
    struct sockaddr_storage their_addr;
    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN];
    ;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP


    if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return (int*)1;
    }
    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1)
        {
            perror("listener: socket");
            continue;
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("listener: bind");
            continue;
        }
        break;
    }

    if (p == NULL)
    {
        fprintf(stderr, "listener: failed to bind socket\n");
        return (int*)2;
    }

    freeaddrinfo(servinfo);
    RoboCupGameControlData GCData1;

    int count1=0;
    //  printf("listener: waiting to recvfrom...\n");
    while(1)
    {
        addr_len = sizeof their_addr;

        if ((numbytes = recvfrom(sockfd, &GCData1,sizeof(RoboCupGameControlData), 0,(struct sockaddr *)&their_addr, &addr_len)) == -1)
        {   
            perror("recvfrom");
            printf("\nno Game Controller :(\n");
            //exit(1);
        }
        if(strncmp(GCData1.header,"RGme",4)==0)//compare first 4 characters
        {
            pthread_mutex_lock(&mutex_GCData);
            GCData=GCData1;printf("VALUE RECIEVED IS %d\n",GCData.state);
            pthread_mutex_unlock(&mutex_GCData);
        }
        else
            printf("[GameController] corrupt packet \n");
        usleep(50000);


    //printf("listener: got packet from %s\n",inet_ntop(their_addr.ss_family,get_in_addr((struct sockaddr *)&their_addr),s, sizeof s))
    //printf("listener: packet is %d bytes long\n", numbytes);
    }
    close(sockfd);
}
