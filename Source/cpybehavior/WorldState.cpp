#include "WorldState.h"

playerstate* playerstate::theInstance =NULL;

playerstate::playerstate()
	{
	/* XABSL */	
	theInstance=this;
	

	/* Image */
	fd= new FeatureDetection(capture);
	camcont= new CamControl(capture);


	}

double playerstate::getTheta()
	{
		return (double)theInstance->fd->ball.theta;
	}


double playerstate::getConfidence()
	{
		return (double)theInstance->loc.confidence();
	}

double playerstate::getReset()
	{
		return (double)theInstance->resetflag;
	}
double playerstate::getRoboCupState()
	{
		return (double)theInstance->GCData.state;
	}
double playerstate::getDistance()
	{
		return (double)theInstance->fd->ball.r;
	}
double playerstate::getFace()
	{
		return (double)theInstance->face;
	}