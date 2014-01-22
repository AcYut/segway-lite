#ifndef COMMONDEFS_H
#define COMMONDEFS_H

#define SYMMETRIC_LANDMARKS

//enum Goal{BLUE,YELLOW};
enum BallReturns{BALLFOUND=0,BALLFINDING=1,TURNRIGHT,TURNLEFT};
enum GoalReturns{GOALFINDING,ENCIRCLER,ENCIRCLEL,GOALFOUND};
enum PathReturns{DOWALK,DOENCIRCLE,DOKICK,NOPATH,DOORIENT};

//Behaviour Local IMP--------------------------------------------------------------------
enum Ball{NOTFOUND,FOUND};
enum PathGenerate {GENERATE,DONTGENERATE};
enum Orientation {NOTORIENTED,ORIENTED};
enum FallStates {NO,FRONT,BACK};
typedef struct
{

	Ball b;
	PathGenerate p;
	Orientation o;
	double LOCALISED;
	int LocalizationState;
	FallStates fallen;

	void reset()
	{
		b=NOTFOUND;
		p=DONTGENERATE;
		o=NOTORIENTED;
		LOCALISED=0;
		LocalizationState=0;
		fallen=NO;
	}	
}Flags;

//---------------------------------------------------------------------------------------
typedef struct 
{
	float r;
	float theta;
	float theta2;
	int updated;
}MotionModel;

typedef struct 
{	float theta;
	float r;
}Coords;

typedef struct
{
	double x;
	double y;
}AbsCoords;

typedef struct
{
	double x;
	double y;
}PathCoords;//Coordinate frame is relative to Acyut, acyut faces +ve Xaxis and +ve Yaxis is to the right, convert to AbsCoords using selfangle
// ^ for communication

typedef struct 
{
	AbsCoords absObstacles[10];
	int n_obstacles;
	AbsCoords goal;
	AbsCoords ball;
}PathStructure;
//---------------------------------------------------------------------------------------
//These are the variables that must be present in CamControl class,
//And must store the corresponding data.
	// Coords bluegoal;
	// Coords yellowgoal;
	// Coords ball;

namespace LOCALIZE_INTERNALS
{
	enum LandmarkType {LAND_L, LAND_X, LAND_T, LAND_BYB, LAND_YBY, LAND_GPB, LAND_GPY};

	struct Particle
	{
		double x;
		double y;
		double angle;
	};

	struct Landmark
	{
		float distance;
		float angle;
		LandmarkType type;
		int counter;
	};

	struct Obstacle
	{
		float distance;
		float angle;
		int counter;
	};

	struct FieldLandmark
	{
		double x;
		double y;
	};
}



//-----------------------------WIFI Transmission-----------------------------------------
typedef struct 
{
	double selfX;
	double selfY;
	double selfAngle;
}LocalisationPacket;

typedef struct 
{
	Coords obstacles[10];
    int n_obstacles;
    Coords ball;
    LOCALIZE_INTERNALS::Landmark landmarks[20];
    int n_landmarks;
}FeaturesPacket;

typedef struct 
{
	int updated;
	int id;
	int no_of_points;
	PathCoords finalpath[30];
}PathPacket;

typedef struct
{
	int id;
	int no_of_points;
	Coords finalPath[30];
}WalkPacket;

typedef struct 
{
	/*data*/
}MotionPacket;

typedef struct 
{
    Flags flags;
}BehaviourPacket;

typedef struct 
{
	LocalisationPacket loc_pack;
	FeaturesPacket feat_pack;
	PathPacket path_pack;
	MotionPacket mot_pack;
	BehaviourPacket behav_pack;
}Packet;


#endif