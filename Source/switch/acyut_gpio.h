#include <stdio.h>
#include <unistd.h>
#include <sys/io.h>
#include <stdlib.h>
#include "../common/common.h"
#define Superio2_Addr 0x2E

void outportb(unsigned char aa, unsigned char bb);

void enter_Superio2_CFG();


void exit_Superio2_CFG();


void Set_CFG2(unsigned char Addr2,unsigned char Value2);

unsigned char Get_CFG2(unsigned char Addr2);

int read_switch(int switch_num);

void led(int led_num,int led_state);

void* switchupdate( void*);