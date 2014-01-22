#include "acyut_gpio.h"

void outportb(unsigned char aa, unsigned char bb)
{
	outb_p(bb,aa);
}

void enter_Superio2_CFG()
{
	outportb(Superio2_Addr, 0x87);
	outportb(Superio2_Addr, 0x87);
}

void exit_Superio2_CFG()
{
	outportb(Superio2_Addr, 0xAA);
}

void Set_CFG2(unsigned char Addr2,unsigned char Value2)
{
	unsigned char d2;
	outportb(Superio2_Addr, Addr2);
	usleep(2000);
	outportb(Superio2_Addr +1, Value2);
	#ifdef DEBUG
	d2 = inb_p(Superio2_Addr+1);//**checking value at given port and returning
	printf("\nWrite %x to CR%x, read back is:%x",Value2,Addr2,d2);
	#endif /*DEBUG*/
	usleep(2000);
}

unsigned char Get_CFG2(unsigned char Addr2)
{
	unsigned char d2;
	outportb(Superio2_Addr, Addr2);
	usleep(2000);
	d2 = inb_p(Superio2_Addr+1);
	#ifdef DEBUG
	printf("\nGet data %x from CR%x",d2,Addr2);
	#endif /*DEBUG*/
	usleep(2000);
	return(d2);
}


int read_switch(int switch_num)
{
	iopl(3);
 	unsigned char d2;
 	enter_Superio2_CFG();
 	/*Initialising...*/
	d2 = Get_CFG2(0x2A);
	d2 = (d2 & 0x7F) | 0x80;
	Set_CFG2(0x2A, d2);
	Set_CFG2(0x07, 0x08); /* Select logic device 08*/
	Set_CFG2(0x30, 0x02); /* Enable GPIO !!Port 5!! */
	/*first four bits of E0,E1,E2 represent pins 2,4,6,8,respctvly, and next four bits represent pins 7,5,3,1*/
	/*Setting configuration of gpio(E0=Sets Input(1) or Output(0) for that particular pin)*/
	Set_CFG2(0x07, 0x08);
	Set_CFG2(0xE0, 0xf0);
	Set_CFG2(0xE2, 0x0f);//Sets Inverted(1) or Normal(0) for that pin
	/*running code to read switch*/
	Set_CFG2(0x07, 0x08);
	d2 = Get_CFG2(0xE1);
	switch(switch_num)
	{	
	case 1:
		if(d2&0x80)//binary AND operator on d2 with 1000 0000 ,ie checking if switch 1 is on
		return 1;
		else
		return 0;
		break;
	case 2:
		if(d2&0x40)//binary AND operator on d2 with 0100 0000 , ie checking if switch 2 is on
		return 1;
		else
		return 0;
		break;
	case 3:
		if(d2&0x20)//binary AND operator on d2 with 0010 0000 , ie checking if switch 3 is on
		return 1;
		else
		return 0;
		break;
	case 4:
		if(d2&0x10)//binary AND operator on d2 with 0001 0000 , ie checking if switch 4 is on
		return 1;
		else
		return 0;
		break;
	}
}

void led(int led_num,int led_state)
{
	iopl(3);
	unsigned char d2;
	/*Initialising...*/
	enter_Superio2_CFG();

	d2 = Get_CFG2(0x2A);
	d2 = (d2 & 0x7F) | 0x80;
	Set_CFG2(0x2A, d2);

	Set_CFG2(0x07, 0x08); /* Select logic device 08*/
	Set_CFG2(0x30, 0x02); /* Enable GPIO !!Port 5!! */
	
	
	/*first four bits of E0,E1,E2 represent pins 2,4,6,8,respctvly, and next four bits represent pins 7,5,3,1*/
	
	
	/*Setting configuration of gpio(E0=Sets Input(1) or Output(0) for that particular pin)*/
	Set_CFG2(0x07, 0x08);
	Set_CFG2(0xE0, 0xf0);	//setting first 4 as input, next 4 as output
	Set_CFG2(0xE2, 0x0f);//Sets Inverted(1) or Normal(0) for that pin
	d2 = Get_CFG2(0xE1);

	//Set_CFG2(0x07, 0x08);
	//Set_CFG2(0xE1,0x00);
	if(led_state==1)
	{
	switch(led_num)
	{
		
	case 1:
		//printf("in switch 1");	
		d2 = Get_CFG2(0xE1);
		d2|=0x01;
		Set_CFG2(0x07, 0x08);
		Set_CFG2(0xE1,d2);
		break;
	case 2:
		//printf("in switch 2");
		d2 = Get_CFG2(0xE1);
		d2|=0x02;
		Set_CFG2(0x07, 0x08);
		Set_CFG2(0xE1,d2);
		break;
	case 3:
		//printf("in switch 3");
		d2 = Get_CFG2(0xE1);
		d2|=0x04;
		Set_CFG2(0x07, 0x08);
		Set_CFG2(0xE1,d2);
		break;
	case 4:
		//printf("in switch 4");
		d2 = Get_CFG2(0xE1);
		d2|=0x08;
		Set_CFG2(0x07, 0x08);
		Set_CFG2(0xE1,d2);
		break;
	}
	}
	else if(led_state==0)
	{
	switch(led_num)
	{	
	case 1:
		//printf("in switch 1");	
		d2 = Get_CFG2(0xE1);
		d2&=0xFE;//11111110
		Set_CFG2(0x07, 0x08);
		Set_CFG2(0xE1,d2);
		break;
	case 2:
		//printf("in switch 2");
		d2 = Get_CFG2(0xE1);
		d2&=0xFc;//11111101
		Set_CFG2(0x07, 0x08);
		Set_CFG2(0xE1,d2);
		break;
	case 3:
		//printf("in switch 3");
		d2 = Get_CFG2(0xE1);
		d2&=0xFb;//11111011
		Set_CFG2(0x07, 0x08);
		Set_CFG2(0xE1,d2);
		break;
	case 4:
		//printf("in switch 4");
		d2 = Get_CFG2(0xE1);
		d2&=0xf7;//11110111
		Set_CFG2(0x07, 0x08);
		Set_CFG2(0xE1,d2);
		break;
	}
	}
	
}
int switch1;
void* switchupdate( void*)
{
    while(1)
    {
        pthread_mutex_lock(&mutex_switch);
     	 	switch1 = read_switch(1);
    	    
    	    if(switch1==0)
        	{
        		exit(0);
        	}
		pthread_mutex_unlock(&mutex_switch);
        
        sleep(1);
    }
}
