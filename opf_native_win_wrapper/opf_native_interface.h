/*
Declarations for oromë pathfinder native windows library:
Author:		Jonas Brown
Date:		18/12-2016
File: 		opf_native_interface.h
*/

#pragma once
#include "opf_native_win_wrapper.h"

/***************************************************************************************************************************
** Finds the shortest path from start-point to target-point. Diagonals are excluded.
>> Params:
--->	nStartX, nStartY		=	X,Y coordinates of starting positio.n
--->	nStartX, nStartY		=	X,Y coordinates of target poaition.
--->	pMap					=	Char buffer ptr to map topographic data. 0 = non-traversable. 1 = traversable.
--->	nMapWidth, nMapHeight	=	Dimensions of grid in nodes.
--->	nOutBufferSize			=	Maximum number of nodes allowed in path.
<> Out Params:
--->	pOutBuffer				=	Ptr to a buffer that will contain id of shortest path nodes.
<< Returns:
<---	-1						=	No path found. pOutBuffer is "empty".
<---	 n						=	Length of shortest path found.
***************************************************************************************************************************/
extern "C" __declspec(dllexport) int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int *pOutBuffer, const int nOutBufferSize);

/***************************************************************************************************************************
** Extends on the functionality of FindPath(). Diagonals; optional. Increased diagonal cost; optional.
** Custom base cost and resistance multiplier; optional.
>> Changed/Added Params:
--->	pMap					=	Char buffer with topographic data. !0 = resistance. 0 = non-traversable.
--->	nIncludeDiagonal		=	Diagonal movement is enabled; default = false.
--->	nNodeBaseCost			=	Base cost of traversing a node; default = 1
***************************************************************************************************************************/
extern "C" __declspec(dllexport) int FindPathEx(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize,
	const bool nIncludeDiagonal = false, const unsigned char nNodeBaseCost = 1);

/**************************************************************************************************************************
** Extends on the functionality of FindPathEx(). Provides profiling options to let the caller benchmark
** the pathfinding algorithm.
>> Changed/Added Params:
--->	nPasses					=	Times to run algorithm on static data.
--->	nRandomdata				=	Toggles whether random or static data should be used for profiling.
--->	nFrequency				=	How often a tiles is randomly blocked. 1/frequency is bocked. 
<> Changed/Added Out Params:
<-->	nOutTimeMS				=	Time in MS it took to run the algorithm on static or random data nPasses times.
<< Returns:
<---	n						=	How many times a profiling pass failed to find a path.
***************************************************************************************************************************/
extern "C" __declspec(dllexport) int FindPathExProfiling(const int nStartX, const int nStartY, const int nTargetX,
	const int nTargetY, const int nMapWidth, const int nMapHeight, const int nOutBufferSize, double& nOutTimeMS, 
	const int nPasses = 1, const bool nIncludeDiagonal = false, const unsigned char nNodeBaseCost = 1, 
	const bool nRandomData = true, const unsigned char nFrequency = 2);