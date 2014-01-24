#ifndef WSTATE_H
#define WSTATE_H

#include "../../Xabsl/XabslEngine/XabslSymbols.h"

#include "../imgProc/camcapture.h"
#include "../imgProc/camcontrol.h"
#include "../imgProc/featuredetection.h"
#include "../imgProc/headmotor.h"
#include "../imgProc/localize.h"
#include "../path/path.hpp"
#include "../common/common.h"
#include "../common/commondefs.h"
#include "../testwalk/commondefswalk.h"



class playerstate

	{
	    public:


                        /* To register XABSL input symbols */
                        static double getTheta();
                        static double getConfidence();
                        static playerstate* theInstance;
						static double getRoboCupState();
                        static double getDistance();      

                        /* If true resets all XABSL parameters */
                        int resetflag;
                        static double getReset();

                        playerstate();
                
                        BallReturns ballreturn;
                        
                        
                        double ACTIVE_GOAL;
		       

                        Flags globalflags;
		        MotionModel mm;
		        //InitState initstate;
        
                        /* Image */ 
                        CamCapture capture;
                        FeatureDetection *fd;
                        HeadMotor hdmtr;
                        CamControl *camcont;
                
       

        Localize loc;
        float bwt,lmwt;
        int ballnotinframe;
        MotionModel localmm;
        double conf;
        
        float prevballr,velocity;
        
        

        

        /* Path Variables */
        Path path;
        PathStructure pathstr; 
        PathReturns pathreturn;

        /*Game Controller */
        GameControllerAcyut GC;
        RoboCupGameControlData GCData;

        


                        
                       
                        



	};


#endif
