#include "imu.h"
#include "unistd.h"

int main()
{
	Imu i;
	i.init();
	while(1)
	{
		// i.flush();
		// i.update();
		printf("%lf %lf %lf\n", i.roll, i.pitch, i.yaw);
		usleep(80000);
	}
}