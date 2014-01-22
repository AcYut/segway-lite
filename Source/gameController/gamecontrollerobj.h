#ifndef GAMECONOBJ_H
#define GAMECONOBJ_H
#define myteamnumber 2 //ask ROBOCUP organisers for this during competition
//#include "RoboCupGameControlData.h"
#include <stdio.h>
#include "RoboCupGameControlData.h"
class GameControllerAcyut
{
    
public:
    RoboCupGameControlData localgcdata;
    inline void update(RoboCupGameControlData gcd)
    {   
        localgcdata=gcd;
    }
    inline int getTeamIndex()
    {
        if(localgcdata.teams[0].teamNumber==myteamnumber)
            return 0;
        else
            return 1;
    }
    inline int updateGoal(int teamindex)
    {
        return localgcdata.teams[teamindex].goalColour;
    }
    inline int isMyKickOff()
    {
        if(localgcdata.teams[localgcdata.kickOffTeam].teamNumber==myteamnumber)
            return 1;
        else
            return 0;
    }
};
#endif
