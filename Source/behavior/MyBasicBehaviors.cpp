#include "MyBasicBehaviors.h"

void BasicBehaviorPrint::execute()
{
    #ifdef XABSL_PRINTING_IS_ON
    printf("\nu asked for %lf\n",o);
    #endif
}

void BasicBehaviorInitialize::execute()
{
    
    #ifdef IP_IS_ON
    printf("Initializing\n");
    

    p.hdmtr.bootup_files();
    

    while(!p.capture.init())
            {
                usleep(500000);
                continue;
            }
    p.globalflags.reset();
    p.conf=0;
    
    printf("Initialized\n");
    #endif
}
void BasicBehaviorUpdate::execute()
{
     
        #ifdef IP_IS_ON
        // p.hdmtr.update();
        printf("Entered update\n");
        int i=0;
        // int e=1;
        // while(e)
        //         {

        //             printf("lol\n");
        //             printf("received error %d from camcapture\n",i++);
        //             usleep(500000);
        //             e=!p.capture.getImage();
        //             printf("e is %d\n",e);     
        //                 if(e==11)
        //                     while(!p.capture.init())
        //     {
        //         usleep(500000);
        //         continue;
        //     }
                
//                }
                // {
                //     continue;
                // }
        p.capture.getImage();
        // usleep(500000);    
        p.fd->getLandmarks(p.capture, p.hdmtr, walkstr.mm);
        p.loc.doLocalize(*p.fd, p.mm, getImuAngle()); 
        p.conf = p.loc.confidence();
        printf("localization updated to %lf\n",p.conf);
        cvShowImage("aa", p.capture.rgbimg);
        cvShowImage("Localization", p.loc.dispImage);
        cvWaitKey(5);
        #endif

        #ifndef IP_IS_ON
        p.conf=1;
        #endif
}

void BasicBehaviorLocalize::execute()
{   
        
        #ifdef IP_IS_ON
        printf("Confidence %lf, localizing\n",p.conf);
        // int i=50000000;
        // while(i--)
        // {
        
        
        // p.hdmtr.update();
        
        while(!p.capture.getImage())
            {
                continue;
            }
        // {
        //     printf("worked\n");
        //     continue;
        // }

        p.fd->getLandmarks(p.capture, p.hdmtr, walkstr.mm);
        p.camcont->search(p.hdmtr);
        p.loc.doLocalize(*p.fd, p.mm, getImuAngle()); 
        cvShowImage("aa", p.capture.rgbimg);
        cvShowImage("Localization", p.loc.dispImage);
    
        p.conf = p.loc.confidence();
        cvWaitKey(5);
        // }
        #endif

        #ifndef IP_IS_ON
        p.conf=1;
        #endif
}

void BasicBehaviormoveAcYuttemp::execute()
{
    unsigned int _x=int(x);
    
    pthread_mutex_lock(&mutex_walkstr);    
        printf("to walk %c\n",_x);
        walkstr.instr = _x;
        walkstr.isFresh = true;
    pthread_mutex_unlock(&mutex_walkstr);
        
}

void BasicBehaviorMakePath::execute()
{
         // p.pathstr.n_obstacles = 2;
        // p.pathstr.absObstacles[0].x=20; 
        // p.pathstr.absObstacles[0].y=31;
        // p.pathstr.absObstacles[1].x=60 ;
        // p.pathstr.absObstacles[1].y=100;
        // p.pathstr.absObstacles[2].x=-40;
        // p.pathstr.absObstacles[2].y=-80;

    //     for(int i=0;i<fd.o.size();i++)//assuming right positive and left neagative for theta
    // {
    //     p.pathstr.absObstacles[i].x=(p.fd->o[i].distance)*cos(deg2rad(p.fd->o[i].angle));
    //     p.pathstr.absObstacles[i].y=(p.fd->o[i].distance)*sin(deg2rad(p.fd->o[i].angle));
    // }

    // for (int i = 0; i < pathstr.n_obstacles; ++i)
    // {
    //     printf("Passed-->> obstacle %d : %lf %lf\n", i, p.pathstr.absObstacles[i].x, p.pathstr.absObstacles[i].y);
    // }
    #ifdef IP_IS_ON
    AbsCoords goalcoords=p.loc.getGoalCoords(p.ACTIVE_GOAL);
    double tempx=goalcoords.x-p.loc.selfX;
    double tempy=goalcoords.y-p.loc.selfY;
    p.pathstr.goal.x= (tempx*cos(deg2rad(p.loc.selfAngle))) - (tempy* sin(deg2rad(p.loc.selfAngle)));//Rotating coordinate system.
    p.pathstr.goal.y= (tempx*sin(deg2rad(p.loc.selfAngle))) + (tempy* cos(deg2rad(p.loc.selfAngle)));
    printf("Passed:-->>>>goal coords x:%lf  y:%lf\n",p.pathstr.goal.x,p.pathstr.goal.y);

    //printf("goal coords y:%lf\n",pathstr.goal.x);
    p.pathstr.ball.x=p.fd->ball.r*cos(deg2rad(p.fd->ball.theta));
    p.pathstr.ball.y=p.fd->ball.r*sin(deg2rad(p.fd->ball.theta));
    
    printf("relative ball----> %f  %f\n",p.fd->ball.r,p.fd->ball.theta);
    printf("Passed:-->>>>ball coords x:%lf  y:%lf\n",p.pathstr.ball.x,p.pathstr.ball.y);
    p.pathreturn=p.path.path_return(p.pathstr);
    
    printf("Path Made\n");
    #endif

   
}

void BasicBehaviorPathToWalk::execute()
{
        #ifdef IP_IS_ON
        p.path.updatePathPacket();
        printf("Path updated\n");
        #endif

    #ifndef IP_IS_ON

    
    //printf("UPDATING PATHPACKVAR\n");
    

    fstream fil1;
    fil1.open("Source/path/paths1.data", ios::in|ios::binary);
    fil1.read((char*)&pathpackvar,sizeof(pathpackvar));
    fil1.close();
    

    #endif
}

void BasicBehaviorFindBall::execute()
{    
    #ifdef IP_IS_ON    
    printf("FINDING THE FUCKING BALL\n");
    p.ballreturn=p.camcont->findBall(*(p.fd),p.hdmtr);       
    #endif

    #ifndef IP_IS_ON
    p.ballreturn=BALLFOUND;
    #endif 
}

void BasicBehaviorReset::execute()
{
    p.conf=0;        
}

