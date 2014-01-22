#include "MyBasicBehaviors.h"

void BasicBehaviorPrint::execute()
{
    printf("\nu asked for %lf\n",o);
}

void BasicBehaviorInitialize::execute()
{
        printf("Initializing\n");
        p.hdmtr.bootup_files();
        p.capture.init();
        p.globalflags.reset();
        //p.conf=0;
        printf("Initialized\n");
}

void BasicBehaviorUpdate::execute()
{
        // p.capture.getImage();
        // p.face=0;

        // p.face=faceDetect(p.capture);
        
        while(1)
                {
                    printf("In infinite loop\n");
                    p.camcont->search(p.hdmtr);
                    p.hdmtr.update();
                }

        // p.camcont->search(p.hdmtr);
        // p.hdmtr.update();

                
        // cvWaitKey(5);
        //p.fd->getLandmarks(p.capture, p.hdmtr, walkstr.mm);
        //p.loc.doLocalize(*p.fd, p.mm, getImuAngle()); 
        //p.conf = p.loc.confidence();
        //printf("localization updated to %lf\n",p.conf);
        // cvShowImage("aa", p.capture.rgbimg_full);
        //cvShowImage("Localization", p.loc.dispImage);
}


void BasicBehaviorLocalize::execute()
{   
        printf("Confidence %lf, localizing\n",p.conf);
        int i=2000;
        while(i--)
        {
        p.capture.getImage();
        p.fd->getLandmarks(p.capture, p.hdmtr, walkstr.mm);
        p.loc.doLocalize(*p.fd, p.mm, getImuAngle()); 
        p.conf = p.loc.confidence();
        p.camcont->search(p.hdmtr);//p.camcont->search(p.hdmtr);    
        p.hdmtr.update();
       // usleep(500);
        cvWaitKey(5);
        cvShowImage("aa", p.capture.rgbimg_full);
        // cvShowImage("Localization", p.loc.dispImage);
        }
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
}

void BasicBehaviorPathToWalk::execute()
{
    p.path.updatePathPacket();
    printf("Path updated\n");
}

void BasicBehaviorFindBall::execute()
{
    //printf("FINDING THE FUCKING BALL\n");
    p.ballreturn=p.camcont->findBall(*(p.fd),p.hdmtr);
}

void BasicBehaviorReset::execute()
{
    p.conf=0;        
}

void BasicBehaviorSearch::execute()
{
        //int i = 500;
        // while(i--)
        // {
            printf("searching\n");
            p.camcont->search(p.hdmtr);
            p.hdmtr.update();
        // }
        // usleep(1000000);

                
        // cvWaitKey(5);
        //p.fd->getLandmarks(p.capture, p.hdmtr, walkstr.mm);
        //p.loc.doLocalize(*p.fd, p.mm, getImuAngle()); 
        //p.conf = p.loc.confidence();
        //printf("localization updated to %lf\n",p.conf);
        //cvShowImage("aa", p.capture.rgbimg);
        //cvShowImage("Localization", p.loc.dispImage);
}

void BasicBehaviorMove::execute()
{
        cvShowImage("face",p.capture.rgbimg_full);
        cvWaitKey(1000);
        wave();
}