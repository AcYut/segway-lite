#include "imu.h"
#include "unistd.h"
#include <fstream>

using namespace std;

int main()
{
	Imu imu;
	imu.init();
	int i=500000;
	double value;
	while(i--)
	{
		
		value=imu.yaw;
		printf("%lf\n",value);
		
	}
	fstream f1;
	f1.open("Source/xsens/imuyaw.angle",std::ios::out);
	f1<<value;
	f1.close();
	printf("Value written to file is %lf",value);
	return 0;
}
