/*
Declarations for the MSVC++ failsafe 2DPoint class:
Written by:	Jonas Brown
Date:		11/01-2017
File: 		2DPoint.h
*/

//Headers:
#pragma once
#include <cmath>

class _2DPoint
{
private:
	//Internal Members:
	unsigned short mCoordinates[2];	//array with the two ints representing x and y coordinates in 2d

public:
	//Constructor:
	_2DPoint(unsigned short X, unsigned short Y) { mCoordinates[0] = X; mCoordinates[1] = Y; }
	_2DPoint() = default;

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
	float CalcEuclideanDistance(_2DPoint *pTargetPoint);
	/* ---------------------------------------------------------------	
	** Calculates manhattan distance from this point to target point.
	>> Params:
	--->	pTargetPoint	=	Ptr to taget point.
	<< Returns: 
	<---	Manhattan distance to target point.	
	---------------------------------------------------------------- */
	unsigned int CalcManhattanDistance(_2DPoint *pTargetPoint);
};