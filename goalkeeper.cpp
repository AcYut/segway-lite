#include <stdio.h>
#include <opencv2/opencv.hpp>
//#include <FlyCapture2.h>
#include "ueye.h"
#include "Source/imgProc/camcapture.h"
#include "Source/imgProc/headmotor.h"
#include "Source/imgProc/camcontrol.h"
#include "Source/imgProc/localize.h"

#include "Source/imgProc/imgproc.h"
#include "Source/imgProc/featuredetection.h"
#include <time.h>

using namespace cvb;
using namespace tbb;
using namespace LOCALIZE_INTERNALS;
using namespace std;

#define FRAME_DIFF 15		//
#define REGR_COUNT 7		//no. of points to be used for regression
#define deg2rad(x) x*3.14/180

double poi(AbsCoords*);
double tti(AbsCoords* ,double* ,double);

main( void )
{
	CamCapture cam(true, 100, 50);
	FeatureDetection fd(cam);
	HeadMotor hm(true);
	MotionModel mm;
	CamControl cc(cam);
	hm.bootup_files();

	if(cam.init()==CAM_FAILURE)
	{
		printf("\n Exiting after init error\n");
		return 0;
	}
	double impactpt,impacttime;
	int frameNew=0, frameLast=0;
	int count =0;
	AbsCoords ball[REGR_COUNT];
	double t[REGR_COUNT], init;			//time in sec
	timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	init = ts.tv_sec;
	while(1)
	{
		//hm.update();

		if(cam.getImage() == CAM_FAILURE)
		{
			cout<<"could not get image\n";
			continue;
		}
		
		fd.getLandmarks(cam, hm, mm);
		cc.findBall(fd, hm);
		if(fd.ballFound() == false)
		{
			cout<<"ball not found\n";
		 	continue;
		}
		cvShowImage("live", cam.rgbimg);
		cvWaitKey(5);
		frameNew++;
		if(frameNew - frameLast >= FRAME_DIFF || frameNew == 1)
		{
			clock_gettime(CLOCK_REALTIME, &ts);
			//save ball position
			t[count] = ts.tv_sec + ts.tv_nsec * pow(10, -9) - init;
			ball[count].x = fd.ball.r * cos(deg2rad(fd.ball.theta));
			ball[count].y = fd.ball.r * sin(deg2rad(fd.ball.theta));
			frameLast = frameNew;	
			count++;
			cout<<"count="<<count<<endl;	
				
		}
		else
		{
			cout<<"processing...\n";
			continue;
		}

		if(count >= REGR_COUNT)
		{
			//Point Of Impact
			impactpt=poi(ball);
			//Time to Impact
			impacttime=tti(ball,t,impactpt);
			cvWaitKey();
			count = 0;
			frameNew = 0;
			frameLast = 0;
			clock_gettime(CLOCK_REALTIME, &ts);
			init = ts.tv_sec;
			continue;
		}
	} 
}

double poi(AbsCoords* p)
{
	for (int i = 0; i < REGR_COUNT; ++i)
	{
		printf("x=%lf\ty=%lf\n",p[i].x,p[i].y);
	}
	//point of impact
	
    double sumx=0, sumxsq=0, sumy=0, sumxy=0;
    double a0, a1, d;

    for(int i=0;i<REGR_COUNT;i++)
    {
	    sumx+=p[i].x;
	    sumxsq+=pow(p[i].x,2);
	    sumy+=p[i].y;
	    sumxy+=p[i].x*p[i].y;
    }
    d=REGR_COUNT*sumxsq-(pow(sumx,2));
    a0=(sumy*sumxsq-sumx*sumxy)/d;
    //a1=(n*sumxy-sumx*sumy)/d;
    //printf("y= %lfx + %lf\n",a1,a0);
    printf("Point Of Impact = %lf\n",a0);
    return a0;
}
double tti(AbsCoords* p,double* t,double a0)
{
	//time to impact
    /*	//constant velocity
	double dx,dy,dt,dd,v=0,dist;
	for(int i=0;i<n-1;i++)
	{
		dx=(p[i+1].x-p[i].x);

		dy=(p[i+1].y-p[i].y);
		dt=t[i+1]-t[i];
		dd=pow((pow(dx,2)+pow(dy,2)),0.5);
		v+=dd/dt;
	}
	*/
	for (int i = 0; i < REGR_COUNT; ++i)
	{
		printf("%lf\t",t[i]);
	}
	printf("\n");
	int n = REGR_COUNT;
		//constant accel
	double dx,dy,dt,dd,v,prev=0,vsum,dist,a=0,tti,tti1,tti2;
	for(int i=0;i<n-1;i++)
	{
		dx=(p[i+1].x-p[i].x);
		dy=(p[i+1].y-p[i].y);
		dt=t[i+1]-t[i];

		dd=pow((pow(dx,2)+pow(dy,2)),0.5);
		if(p[i+1].x<p[i].x)
			dd=-dd;
		v=dd/dt;
		if(i)
			a+=(v-prev)/dt;
		prev=v;
		vsum+=v;
	}

	a/=n-1;
	v=vsum/(n-1);
	printf("Velocity  used  = %lf\n",v);
	printf("acceler   used  = %lf\n",a);
	if(v<0)
	{	
		dist= -pow(pow((p[n-1].y-a0),2)+pow(p[n-1].x,2),0.5);

	}
	else
	{
		printf("no threat\n");
		return -1;
	}
	printf("Impact Distance = %lf\n",dist);

	//double tti=dist/v
	double det=pow((v*v+2*a*dist),0.5);
//	printf("%lf\n",det);
	if(a)
	{	tti1=((-v+(det))/a);
		tti2=((-v-(det))/a);
//		printf("%lf\t%lf\n",tti1,tti2);
		if((tti1<tti2)&&(tti1>0))
		{	
//			printf("first root\n");
			tti=tti1;
		}
		
		else
		{
//			printf("second root\n");
			tti=tti2;
		}


	}
	else
	{
		printf("too perfect\n");
		tti=dist/v;	
	}

//	printf("%lf\n%lf\n",dx,dd);
	if((tti<0)||(isnan(tti)))
	{
		printf("too slow\n");
		return -1;
	}
		printf("Time To Impact  = %lf s\n",tti);
	return tti;
}
