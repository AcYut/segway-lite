#include "walk.h"



// #define WHEELDIAmm 100.0 //mm
// #define WHEELDIST 240.0 //mm
#define tbFORWARD 0
#define tbBACKWARD 1
#define tbLEFT 3
#define tbRIGHT 2
#define tbSTOP 0,0

struct ftdi_context ftdi;
byte packet[18];
byte packet_recieved[18];
int packet_length;
int len_to_read;


Walk::Walk(testBot* bot)
{
	this->bot=bot;
	WHEELDIAmm=this->bot->wheelDiameter;
	WHEELDIST=this->bot->wheelDistance;
	omega=this->bot->angularVelocity;
	// ftdi_bootup();	
	// start2();
	printf("START completed\n\n\n");
};


void Walk::move(float walkr,float walktheta)
{
	double deltaR;
	double deltaTheta;
	double arclen;
	//printf("[walkthread]   walk cmd received angle=%f",enAngle);
		deltaR = (2*walkr/WHEELDIAmm/omega)*1000000;
	
		if(walktheta<0)
		{
			walktheta*=-1;
			arclen=(walktheta/180.0)*3.1415*WHEELDIST/2;

			// delta=(arclen/(2*3.1415*WHEELDIAmm*MSPEED/360))*1000000;
			deltaTheta = (2*arclen/WHEELDIAmm/omega)*1000000;
			this->sync_write_data_motor(tbLEFT,512);
			// testBotWalk1(tbLEFT,512);
			usleep((int)deltaTheta);
			// testBotWalk1(tbSTOP);
			// pthread_mutex_lock(&mutex_walkstr);
			// walkstr.mm.theta=-walktheta;
			// pthread_mutex_unlock(&mutex_walkstr);
		}
		else if(walktheta>0)
		{
			// pthread_mutex_lock(&mutex_walkstr);
			// walkstr.mm.theta=walktheta;
			// pthread_mutex_unlock(&mutex_walkstr);
			// arclen=(walktheta/180.0)*2*3.1415*WHEELDIST;
			// delta=(arclen/(2*3.1415*WHEELDIAmm*MSPEED/360))*1000000;
			arclen=(walktheta/180.0)*3.1415*WHEELDIST/2;
			printf("Calculated arc length is %f\n",arclen);
			deltaTheta = (2*arclen/WHEELDIAmm/omega)*1000000;
			this->sync_write_data_motor(tbRIGHT,512);
			// testBotWalk1(tbRIGHT,512);
			usleep((int)deltaTheta);
			// testBotWalk1(tbSTOP);
		}
		
		

		this->sync_write_data_motor(tbBACKWARD,512);
		
		usleep((int)(deltaR));

		this->sync_write_data_motor(tbSTOP);

		
		// pthread_mutex_lock(&mutex_walkstr);
		// walkstr.mm.r=walkr;
		// walkstr.mm.updated=1;
		// pthread_mutex_unlock(&mutex_walkstr);
		return ;
	
}


// void testBotWalk1(int cmd,int speed)
// {
// 		printf("[testbotcallwalk]cmd=%d with speed=%d\n",cmd,speed);

// 	sync_write_data_motor(cmd,speed);
// }

int Walk::sync_write_data_motor(int mode, int speed)
{	
	
		byte mot1_lowdata,mot1_highdata,mot2_lowdata,mot2_highdata;
	if(mode==tbFORWARD)	//fwd	
	{	
		mot1_lowdata=speed&0xff;
		mot1_highdata=speed>>8;
		
		mot2_lowdata=(speed+1024)&0xff;
		mot2_highdata=(speed+1024)>>8;

		

			
	}
	
	else if(mode==tbBACKWARD)	//backwd	
	{	
		mot1_lowdata=(speed+1024)&0xff;
		mot1_highdata=(speed+1024)>>8;
		
		mot2_lowdata=speed&0xff;
		mot2_highdata=speed>>8;
	}
	
	 
	else if(mode==2)	//right	
	{	
		mot1_lowdata=speed&0xff;
		mot1_highdata=speed>>8;
		// mot1_highdata=0;
		// mot1_lowdata=0;
		
		mot2_lowdata=speed&0xff;
		mot2_highdata=speed>>8;
	}
	else if(mode==3)	//left	
	{	mot1_lowdata=(speed+1024)&0xff;
		mot1_highdata=(speed+1024)>>8;
		
		mot2_lowdata=(speed+1024)&0xff;
		mot2_highdata=(speed+1024)>>8;
	}


	

	byte data[2];
		
		data[0]=mot1_lowdata;
		data[1]=mot1_highdata;
		this->bot->comm->addSyncWrite(0x20,2,data,0);
		
		data[0]=mot2_lowdata;
		data[1]=mot2_highdata;
		this->bot->comm->addSyncWrite(0x20,2,data,1);


	this->bot->comm->syncFlush();
	// packet[0]=0xff;		//header
	// packet[1]=0xff;		//header
	// packet[2]=broadcast_id;		//id
	// packet[3]=10;		//length
	// packet[4]=0x83;		//instruction
	// packet[5]=0x20;		//Start address to write Data
	// packet[6]=0x02;		//Length of Data to write
	// packet[7]=id1;		//First ID of RX-28
	// packet[8]=mot1_lowdata;		//First data of the first RX-28
	// packet[9]=mot1_highdata;		//Second data of the first RX-28
	// packet[10]=id2;		//ID of the second RX-28
	// packet[11]=mot2_lowdata;		//First data of the second RX-28
	// packet[12]=mot2_highdata;		//Second data of the second RX-28
	
	// packet[13]=checksum(13);		//checksum
	
	// packet_length=14;	
	// write_packet(packet,packet_length);



}


// int checksum(int size)
// {
// 	int result=0;
// 	int i=2;
// 	while(i<size)
// 	{		
// 		result+=packet[i];
// 		i++;	
// 	}
// //	printf("result=%d\n",result);
// //	if(result>255)
// //	{
// //		result=result%100;	
// //	}
	
// 	result=~result;	
	
// //	printf("result2=%d\n",result);
// 	return result;
// }


// int write_packet(byte *packet, int length)
// {	int a=0,i;	
// 	printf("[testbot]Writing data...\n");
// 	//for(i=0;i<length;i++)			
// 	//	printf("%x\t",packet[i]);
	
// 	//printf("\n");

// 	for(int i=0;i<length;++i)
// 			printf("%d\n",packet[i]);

// 	printf("Packet length: %d ",length);
	
// 	a=ftdi_write_data(&ftdi,packet,length);	

// 	if(a>0)	
// 		printf("[testbot]bytes written(no error):%d\n",a);
// 	else 
// 		printf("[testbot]write error.\n");

// 	sleep(500);
// }

// void ftdi_bootup()
// {

// 	if(ftdi_init(&ftdi)!=0)
// 	{
// 		printf("[testbot]ftdi - could not be opened.\n");
// 	}
// 	else
// 		printf("[testbot]booting up.\n");

	
// //	int ftdi_usb_open_desc	(	struct ftdi_context * 	ftdi,int vendor,int product,const char * description,const char * serial )		

// 	if(ftdi_usb_open_desc(&ftdi,0x0403, 0x6001,NULL/*description*/,usb_serial)!=0)
// 	{
// 		printf("[testbot]ftdi error.\n");
// 	}
// 	else
// 	{
// 		printf("[testbot]ftdi opened.\n");
// 		ftdi_set_baudrate(&ftdi,1000000);
// 	}

// }