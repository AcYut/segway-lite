#ifndef __MyBasicBehaviors_h_
#define __MyBasicBehaviors_h_

#include <cstdio>

#include "../../Xabsl/XabslEngine/XabslBasicBehavior.h"
#include "WorldState.h"
class BasicBehaviorPrint: public xabsl::BasicBehavior
{

	public:
	double o;
	BasicBehaviorPrint(xabsl::ErrorHandler& errorHandler,playerstate &p):xabsl::BasicBehavior("printmsg",errorHandler),p(p)
		{
		}
	  virtual void registerParameters()
  {

    if (!parameters->decimal.exists("printmsg.o"))
    {
      parameters->registerDecimal("printmsg.o",o);
    }
  }
	virtual void execute();
	private:
        playerstate &p;
};


class BasicBehaviorInitialize: public xabsl::BasicBehavior
{

	public:
	BasicBehaviorInitialize(xabsl::ErrorHandler& errorHandler,playerstate &p):xabsl::BasicBehavior("doInitialize",errorHandler),p(p)
		{
		}

	virtual void execute();
    private:
            playerstate &p;
};

class BasicBehaviormoveAcYuttemp: public xabsl::BasicBehavior
{
	double x;
	public:
	BasicBehaviormoveAcYuttemp(xabsl::ErrorHandler& errorHandler,playerstate &p):xabsl::BasicBehavior("moveAcYuttemp",errorHandler),p(p)
		{
		}

		virtual void registerParameters()
  {

    if (!parameters->decimal.exists("moveAcYuttemp.x"))
    {
      parameters->registerDecimal("moveAcYuttemp.x",x);
    }
  }


	virtual void execute();
    private:
            playerstate &p;
};
class BasicBehaviorUpdate: public xabsl::BasicBehavior
{

	public:
	BasicBehaviorUpdate(xabsl::ErrorHandler& errorHandler,playerstate &p):xabsl::BasicBehavior("doUpdate",errorHandler),p(p)
		{
		}

	virtual void execute();
    private:
            playerstate &p;
};
class BasicBehaviorLocalize: public xabsl::BasicBehavior
{

	public:
	BasicBehaviorLocalize(xabsl::ErrorHandler& errorHandler,playerstate &p):xabsl::BasicBehavior("doLocalize",errorHandler),p(p)
		{
		}

	virtual void execute();
    private:
            playerstate &p;
};

class BasicBehaviorPathToWalk: public xabsl::BasicBehavior
{
	public:
	BasicBehaviorPathToWalk(xabsl::ErrorHandler& errorHandler,playerstate &p):xabsl::BasicBehavior("doPathToWalk",errorHandler),p(p)
		{

		}
	virtual void execute();
private:
		playerstate &p;

};

class BasicBehaviorMakePath: public xabsl::BasicBehavior
{
	public:
	BasicBehaviorMakePath(xabsl::ErrorHandler& errorHandler,playerstate &p):xabsl::BasicBehavior("doMakePath",errorHandler),p(p)
		{

		}
	virtual void execute();
private:
		playerstate &p;

};

class BasicBehaviorFindBall: public xabsl::BasicBehavior
{
	public:
	BasicBehaviorFindBall(xabsl::ErrorHandler& errorHandler,playerstate &p):xabsl::BasicBehavior("doFindBall",errorHandler),p(p)
		{

		}
	virtual void execute();
private:
		playerstate &p;

};


class BasicBehaviorReset: public xabsl::BasicBehavior
{
	public:
	BasicBehaviorReset(xabsl::ErrorHandler& errorHandler,playerstate &p):xabsl::BasicBehavior("doReset",errorHandler),p(p)
		{

		}
	virtual void execute();
private:
		playerstate &p;

};
#endif
