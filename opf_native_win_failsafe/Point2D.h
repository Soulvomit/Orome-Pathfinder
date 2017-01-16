/*	
Interface descriptor for Point2D class:
Written by:	Jonas Brown
Date:		08/04-2016
File: 		Point2D.h
*/

//Headers:
#pragma once
#include <cmath>

class Point2D
{
private:
	//Internal Members:
	unsigned short mCoordinates[2];	//array with the two ints representing x and y coordinates in 2d

public:
	//Constructor:
	Point2D(unsigned short X, unsigned short Y) { mCoordinates[0] = X; mCoordinates[1] = Y; }
	Point2D() = default;
	//Public Stactic Mambers:
	static int _BaseCost;	//base cost of traversing one point

	//MS-Style Properties (Will only compile with MSVC++):
	__declspec (property (put = SetX, get = GetX)) unsigned short X;
	void SetX(unsigned short value) { mCoordinates[0] = value; }
	unsigned short GetX() const { return mCoordinates[0]; }
	__declspec (property (put = SetY, get = GetY)) unsigned short Y;
	void SetY(unsigned short value) { mCoordinates[1] = value; }
	unsigned short GetY() const { return mCoordinates[1]; }

	//Public Functions:
	/* ---------------------------------------------------------------
	** Calculates euclidean distance from this point to target point.
	>> Params:
	--->	pTargetPoint	=	Ptr to taget point.
	<< Returns: 
	<---	Euclidean distance to target point.	
	---------------------------------------------------------------- */
	float CalcEuclideanDistance(Point2D *pTargetPoint);
	/* ---------------------------------------------------------------	
	** Calculates manhattan distance from this point to target point.
	>> Params:
	--->	pTargetPoint	=	Ptr to taget point.
	<< Returns: 
	<---	Manhattan distance to target point.	
	---------------------------------------------------------------- */
	int CalcManhattanDistance(Point2D *pTargetPoint);
};