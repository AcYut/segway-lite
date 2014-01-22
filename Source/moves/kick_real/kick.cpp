#include "AcYut.h"
#include "communication.h"
#include "xsens/imu.h"
#include <fstream>

using namespace std;

float output[480];
float* generatespline(int gn,float gx[],float gy[])
{
	
	  float ga[gn+1];
	  float gb[gn];
	  float gd[gn];
	
	  float gh[gn];
	  float gal[gn];
	  float gc[gn+1],gl[gn+1],gmu[gn+1],gz[gn+1];
	
	  //1..............................
	 // ga[]=new float[gn+1];
		int gi; 
	  for(gi=0;gi<gn+1;gi++)
	    ga[gi]=gy[gi];
	  //2.................................
	  //gb[]=new float[gn];
	  //gd[]=new float[gn];
	  //3.................................
	  //gh[]=new float[gn];
	  for(gi=0;gi<gn;gi++)
	    gh[gi]=gx[gi+1]-gx[gi];
	  //4...................................
	  //gal[]=new float[gn];
	  for(gi=1;gi<gn;gi++)
	    gal[gi]=3*((((float)ga[gi+1]-(float)ga[gi])/(float)gh[gi])-(((float)ga[gi]-(float)ga[gi-1])/(float)gh[gi-1]));
	  //5......................................
	  //gc[]=new float[gn+1];
	  //gl[]=new float[gn+1];
	  //gmu[]=new float[gn+1];
	  //gz[]=new float[gn+1];
	  //6........................................
	  gl[0]=1;
	  gmu[0]=0;
	  gz[0]=0;
	  //7.........................................
	  for(gi=1;gi<gn;gi++)
	  {
	    gl[gi]=2*(gx[gi+1]-gx[gi-1])-(gh[gi-1]*gmu[gi-1]);
	    gmu[gi]=(float)gh[gi]/(float)gl[gi];
	    gz[gi]=((float)gal[gi]-(float)gh[gi-1]*gz[gi-1])/(float)gl[gi];
	  }
	  //8.........................................
	  gl[gn]=1;
	  gz[gn]=0;
	  gc[gn]=0;
	  //9.............................................
	  int gj;
	  for(gj=gn-1;gj>=0;gj--)
	  {
	    gc[gj]=gz[gj]-gmu[gj]*gc[gj+1];
	    gb[gj]=(((float)ga[gj+1]-(float)ga[gj])/(float)gh[gj])-(((float)gh[gj]*((float)gc[gj+1]+2*(float)gc[gj]))/(float)3);
	    gd[gj]=((float)gc[gj+1]-(float)gc[gj])/(float)(3*gh[gj]);
	  }
	  //10......................................................
	
	
	  int tp=0,gt;
	  for(gt=0;gt<gn;gt++)
	  {
//	    printf("eqn");
	    output[tp]=ga[gt];
//	    printf("%f    ",ga[gt]);
	    tp++;
	    output[tp]=gb[gt];
	    //printf("%f    ",gb[gt]);
	    tp++;
	    output[tp]=gc[gt];
	    //printf("%f    ",gc[gt]);
	    tp++;
	    output[tp]=gd[gt];
	    //printf("%f    \n",gd[gt]);
	    tp++;
	  }
	  return output;
}

float scurve(float in,float fi,float t, float tot)
{
	float frac=(float)t/(float)tot;
	if(frac>1)
	frac=1;
	float retfrac=frac*frac*(3-2*frac);
	float mval=in + (fi-in)*retfrac;
	return mval;
}


int main()
{

	/* left leg up(390 - x) and out(+ve z). right leg inward. right arm outward. change in order of tens
	*/
	Imu imu;
	imu.init();
	
	Communication comm;
	AcYut bot(&comm,NULL);

	// LEFT HAND
	float mot07[]={4096-2172,4096-2500,4096-2172,4096-2500,4096-2172,4096-2500,4096-2172};//float mot07[]={4096-2048,4096-2048,4096-2048,4096-2048,4096-2048,4096-2048,4096-2048};
	float mot08[]={4096-1040,4096-1040,4096-1040,4096-1040,4096-1040,4096-1040,4096-1040};//float mot08[]={4096-1040,4096-1040,4096-1040,4096-1040,4096-1040,4096-1040,4096-1040};
	float mot10[]={4096-2198,4096-2700,4096-3198,4096-2700,4096-3198,4096-2700,4096-3198};//float mot10[]={4096-2048,4096-2048,4096-2048,4096-2048,4096-2048,4096-2048,4096-2048};
	
	//RIGHT HAND
	float mot27[]={2172,2500,2172,2500,2172,2500,2172};		//float mot27[]={2048,3072,3072,3072,3072,2048,2048};
	float mot28[]={1040,1140,1040,1040,1040,1040,1040};     //float mot28[]={1100,2048,2048,2048,2048,1100,1100};
	float mot30[]={2048,2550,3048,2550,3048,2550,3048};		//float mot30[]={2048,2048,3072,2048,3072,2048,2048};

	//LEFT LEG
	float llegx[]={390,370,360,350,340,340,340};
	float llegy[]={0,0,0,0,0,0,0};
	float llegz[]={0,10,20,20,20,20,20};
	
	//RIGHT LEG
	float rlegx[]={390,390,390,390,390,390,390};
	float rlegy[]={0,0,0,0,0,0,0};
	float rlegz[]={0,-50,-60,-60,-60,-60,-60};
	
	//TIME
	float t1[]={0,1.5,2,3.5};
	float t=6.0;
	int fps=60;
	
	int vm7,vm8,vm10,vm27,vm28,vm30; 
	float vlx,vly,vlz,vrx,vry,vrz;
	
	int i;
	
	int t3;
	
	int arr_l[4],arr_r[4];
		for(t3=0;t3<360;t3+=1)
		{
			int j= (int)(t3/60.0);
			arr_l[0]=vm7=(int)scurve(mot07[j],mot07[j+1],t3%60, 60);
			arr_l[1]=vm8=(int)scurve(mot08[j],mot08[j+1],t3%60, 60);
			arr_l[3]=vm10=(int)scurve(mot10[j],mot10[j+1],t3%60, 60);
			arr_r[0]=vm27=(int)scurve(mot27[j],mot27[j+1],t3%60, 60);
			arr_r[1]=vm28=(int)scurve(mot28[j],mot28[j+1],t3%60, 60);
			arr_r[3]=vm30=(int)scurve(mot30[j],mot30[j+1],t3%60, 60);
			vlx=scurve(llegx[j],llegx[j+1],t3%60, 60);
			vly=scurve(llegy[j],llegy[j+1],t3%60, 60);
			vlz=scurve(llegz[j],llegz[j+1],t3%60, 60);
			vrx=scurve(rlegx[j],rlegx[j+1],t3%60, 60);
			vry=scurve(rlegy[j],rlegy[j+1],t3%60, 60);
			vrz=scurve(rlegz[j],rlegz[j+1],t3%60, 60);
			arr_l[2]=arr_r[2]=0;
			bot.left_hand->setGoalPositionSync(arr_l);
			bot.right_hand->setGoalPositionSync(arr_r);
			bot.left_leg->runIK(vlx,vly,vlz,0);
			bot.left_leg->setGoalPositionSync();
			bot.right_leg->runIK(vrx,vry,vrz,0);
			bot.right_leg->setGoalPositionSync();
			comm.syncFlush();
			usleep(16666);
			printf("%d %d %d %d %d %d %f %f %f %f %f %f\n",vm7,vm8,vm10,vm27,vm28,vm30,vlx,vly,vlz,vrx,vry,vrz);
		}					
	
	
	return 0;	
}	


