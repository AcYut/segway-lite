#include "../common/common.h" 
#include "walk.h"

#include <signal.h>
#include <fstream>
#include <opencv2/opencv.hpp>  
#include <ncurses.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <cstring>
#include <set>
#include <unistd.h>
#include <sys/ioctl.h>	
#include <sys/types.h>
#include <inttypes.h>
#include <sys/time.h>
#include <termios.h>

void* walk_thread(void*);