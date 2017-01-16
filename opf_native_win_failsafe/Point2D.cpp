/*
Logical descriptor for Point2D class:
Written by:	Jonas Brown
Date:		08/04-2016
File: 		Point2D.h::Point2D.cpp
*/

#include "Point2D.h"

int Point2D::_BaseCost;

float Point2D::CalcEuclideanDistance(Point2D *pTargetPoint)
{
	//square root of ((x2 - x1)^2 + (y2 - x1)^2)
	int a = pTargetPoint->X - X;
	int b = pTargetPoint->Y - Y;
	return (float)sqrt((a*a) + (b*b));
}
int Point2D::CalcManhattanDistance(Point2D *pTargetPoint)
{
	//(absolut value of (x2 - x1) + absolut value of (y2 - y1)) * cost of moving one point
	int a = pTargetPoint->X - X;
	int b = pTargetPoint->Y - Y;
	return (abs(a) + abs(b)) * _BaseCost;
}
