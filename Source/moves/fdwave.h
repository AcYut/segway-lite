#ifndef FDWAVE_H
#define FDWAVE_H
#include "AcYut.h"
#include "communication.h"
#include "xsens/imu.h"
#include <fstream>

using namespace std;

float* generatespline(int gn,float gx[],float gy[]);

float scurve(float in,float fi,float t, float tot);


void wave();
#endif