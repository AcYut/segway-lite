#include "walk_thread.h"

#define distance(x1,y1,x2,y2)	sqrt(pow(y2-y1,2) + pow(x2-x1,2))
#define convdegrad(p)	p*acos(-1)/180
 
const double pi = acos(-1);
//	c1, c2... are constants for equations which are outlined below 	
//	vd = Current velocity, vf = Final velocity, delta_y = Step length of the foot when it moves from back to front
													//	vd is taken as velocity at the beginning of the step and vf as vlocity at the end of the step

											//	vf_max = c1*vd			Maximum possible velocity at the end of the step
const double c1=1.981991;							// For zmax = 65 ,  1.8367262
const double c2=(c1 - pow(pow(c1,2)-1,0.5));		//	vf_min = c2*vd			Minimum possible velocity at the beginning of the step
// const double c5=7.853317745/2;						// 	vf + vd = c5*delta_y 	Generalised equation which connects the above equations
const double c5=3.523127;						//	For zMax = 65 , 7.445192041/2
const double c3=(c1+1)/c5;				//	delta_y_max = c3*vd		Maximum step length possible, this corresponds to equation 1
const double c4=(c2+1)/c5;				//	delta_y_min	= c4*vd		Minimum step length possible, this corresponds to equation 2
const double v_initial = 10;				 //	Velocity when bot begins to move
const double first_delta_y= 2*v_initial/c5;//	Initial step length is calculated by using equation 4 and given initial velocity which is assumed constant, i.e, vf=vd=vi
const double max_velocity = 90;//	Maximum velocity corresponding to above delta y assuming step length is constant for the motion	
const double max_delta_y  = 2*max_velocity/c5;				 //	Maximum length of a step (read delta y), from back to front. This is a limitation of stability; if bot moves more farther than this, it will be unstable
const double foot_width  = 100;				 //	Width of the foot, might not be used
const double foot_separation = 130;			 //	Standard Length between centers of the feet during linear motion
const double max_delta_x = 30;	
const double max_delta_theta = 15;	
const double min_delta_y = 6;				 //	This is an arbitrary value chosen to put a lower limit on the bot's step length such that the step length oscillates between
											 //	these maximum and minimum values of delta x. This will be changed for fine-tuning the motion.

const double OBSTACLE_RADIUS = 200;


using namespace std;

bool quit = false;






WalkPacket convertPathPacket(PathPacket p)
{
	WalkPacket w;
	w.id=p.id;
	w.no_of_points=p.no_of_points;

	for(int i=0;i<p.no_of_points;++i)
		printf("Packet before conversion is %f %f\n",p.finalpath[i].x,p.finalpath[i].y);

	double x,y;
	double theta;
	for(int i=0;i<w.no_of_points;++i)
		{
			x=p.finalpath[i].x;
			y=p.finalpath[i].y;
			w.finalPath[i].r     = sqrt(x*x+y*y);

			if(fabs(x)<0.0001)
				{
					if(y>0)
						theta=pi/2;
					else 
						theta=-pi/2;
				}
			else
			{
			theta = atan(y/x);

				if(y<0 && x<0)
						theta-=pi;
				else if(x<0 && y>0)
						theta+=pi;
			}

			w.finalPath[i].theta=theta;	
		}
	return w;
}



void* walk_thread(void*)
{
	
	

	Communication comm;
	testBot bot(&comm);
	Walk walk(&bot);
	
	PathPacket pathpackvarlocal;
	WalkPacket walkpacket;
	Coords coords;

	walkpacket.no_of_points=30;
	int fps=30.0;
	while (1)
	{
			// printf("Size is %d\n",pathpackvar.no_of_points);

			pthread_mutex_lock(&mutex_pathpacket);
					if(pathpackvar.updated==1)
						{
							walkpacket=convertPathPacket(pathpackvar);
							pathpackvar.updated=0;
						}		
			pthread_mutex_unlock(&mutex_pathpacket);


		for(int i=0;i<walkpacket.no_of_points;++i)
		{

			pthread_mutex_lock(&mutex_pathpacket);
					if(pathpackvar.updated==1)
						{
							walkpacket=convertPathPacket(pathpackvar);
							i=0;
							pathpackvar.updated=0;
						}		
			pthread_mutex_unlock(&mutex_pathpacket);
			// #ifndef ALL_PRINTING_OFF
			printf("Size is %d\n",pathpackvar.no_of_points);
			printf("Path sent signal %f %f\n",walkpacket.finalPath[i].r,walkpacket.finalPath[i].theta);
			// #endif
			walk.move(walkpacket.finalPath[i].r,walkpacket.finalPath[i].theta);

		}

	}



	
	return 0;
	
	
};



