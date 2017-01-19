/*
Definitions for the MSVC++ failsafe 2DPoint class:
Written by:	Jonas Brown
Date:		11/01-2017
File: 		2DPoint.cpp
*/

#include "2DPoint.h"

float _2DPoint::CalcEuclideanDistance(_2DPoint *pTargetPoint)
{
	//square root of ((x2 - x1)^2 + (y2 - x1)^2)
	int a = pTargetPoint->X - X;
	int b = pTargetPoint->Y - Y;
	return (float)sqrt((a*a) + (b*b));
}
unsigned int _2DPoint::CalcManhattanDistance(_2DPoint *pTargetPoint)
{
	//(absolut value of (x2 - x1) + absolut value of (y2 - y1)) * cost of moving one point
	int a = pTargetPoint->X - X;
	int b = pTargetPoint->Y - Y;
	return (abs(a) + abs(b));
}
