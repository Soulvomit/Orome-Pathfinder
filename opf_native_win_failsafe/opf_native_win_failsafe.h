/*
Interface descriptor for FindPath Library:
Written by:	Jonas Brown
Date:		11/04-2016
File: 		FindPath.h
*/

//Headers:
#pragma once
#include "stdafx.h"
#include "PathFinder.h"

/****************************************************************************************************
** Finds the shortest path from start-point to target-point. Diagonals are excluded.
>> Params:
--->	nStartX, nStartY		=	X,Y coordinates of starting position
--->	nStartX, nStartY		=	X,Y coordinates of target poaition
--->	pMap					=	Char buffer ptr to map topographic data. 0 = non-traversable.
--->	nMapWidth, nMapHeight	=	Dimensions of grid in nodes.
--->	pOutBuffer				=	Ptr to a buffer that will contain id of shortest path nodes.
--->	nOutBufferSize			=	Maximum number of nodes allowed in path.
<< Returns:
<---	-1						=	No path found. pOutBuffer is "empty".
<---	 n						=	Length of shortest path found.
****************************************************************************************************/
extern "C" __declspec(dllexport) int FindPathFailsafe(const int nStartX, const int nStartY, const int nTargetX, 
	const int nTargetY, const unsigned char *pMap, const int nMapWidth, const int nMapHeight, int *pOutBuffer,
	const int nOutBufferSize);

/*******************************************************************************************************
** Extends on the functionality of FindPath(). Diagonals; optional. Increased diagonal cost; optional.
** Custom base cost and resistance multiplier; optional. 
>> New params:
--->	pMap					=	Float buffer ptr to map topographic data. 
								--------	0 = Non-traversable. !0 = resistance multiplier.
--->	nIncludeDiagonal		=	Diagonal movement is enabled; default = false.
								--------	Resistance multiplier set by pMap[index] value.
--->	nNodeBaseCost			=	Base cost of traversing a node; default = 1
*******************************************************************************************************/
extern "C" __declspec(dllexport) int FindPathExFailsafe(const int nStartX, const int nStartY, const int nTargetX,
	const int nTargetY, const unsigned char *pMap, const int nMapWidth, const int nMapHeight, int *pOutBuffer,
	const int nOutBufferSize, const bool nIncludeDiagonal = false, const int nNodeBaseCost = 1);

/**********************************************************************************************************
** Extends on the functionality of FindPathEx(). Memory will not be freed and will be pointed to by
** pPathFinder input ptr. If pPathFinder is already initialized, you can re-use the current snapshot by
** nNewSnapshot = false. When re-using the current snapshot there is no need to pass any new pMap 
** topographical data. You may leave the pMap ptr as null. Changes to pMap data must be done directly on
** the snapshot nodes. The usage of nNewSnapshot = false will reduce memory i/o operation, but requires
** a degree of map uniformity (eg. the map topography is fairly static has few changes) to stay 
** effecient. 
>> New params:
--->	pPathFinder		=	Ptr to the a path finder. Will be used as i/o.
--->	nNewSnapshot	=	Current snapshot will not be saved for this FindPath() call; default = true.
**********************************************************************************************************/
extern "C" __declspec(dllexport) int FindPathExNoCleanupFailsafe(const int nStartX, const int nStartY, const int nTargetX,
	const int nTargetY, const unsigned char *pMap, const int nMapWidth, const int nMapHeight, int *pOutBuffer,
	const int nOutBufferSize, PathFinder *&pPathFinder, const bool nIncludeDiagonal = false,
	const int nNodeBaseCost = 1, const bool nNewSnapshot = true);