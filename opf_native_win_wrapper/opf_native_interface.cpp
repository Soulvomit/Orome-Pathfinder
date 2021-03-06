/*
Definitions for orom� pathfinder native windows library:
Author:		Jonas Brown
Date:		18/12-2016
File: 		opf_native_interface.cpp
*/
#pragma once
#include "opf_native_interface.h"

int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char *pMap, const int nMapWidth,
	const int nMapHeight, int *pOutBuffer, const int nOutBufferSize)
{
	//call find path asm routine
	int pathlength = FindPathASMRoutine(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight, pOutBuffer, 
		nOutBufferSize, false);
	//return path length
	return pathlength;
}

int FindPathEx(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char *pMap, const int nMapWidth,
	const int nMapHeight, int *pOutBuffer, const int nOutBufferSize, const bool nIncludeDiagonal)
{
	//call find path asm routine
	int pathlength = FindPathASMRoutine(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize, 
		nIncludeDiagonal);
	//return path length
	return pathlength;
}

int FindPathFailsafe(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char *pMap, const int nMapWidth,
	const int nMapHeight, int *pOutBuffer, const int nOutBufferSize)
{
	//call find path msvc++ routine
	int pathlength = FindPathMSVC(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize);
	//return path length
	return pathlength;
}

int FindPathExFailsafe(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char *pMap, const int nMapWidth,
	const int nMapHeight, int *pOutBuffer, const int nOutBufferSize, const bool nIncludeDiagonal)
{
	//call find path msvc++ routine
	int pathlength = FindPathExMSVC(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize,
		nIncludeDiagonal);
	//return path length
	return pathlength;
}

int FindPathExProfiling(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const int nMapWidth, 
	const int nMapHeight, const int nOutBufferSize, double& nOutTimeMS, const int nPasses, const bool nIncludeDiagonal, 
	const bool nRandomData, const unsigned char nFrequency, const bool nUseFailsafe)
{
	int pathlength = 0;
	int failures = 0;
	//start timer
	std::clock_t start = std::clock();
	//foreach pass
	for (int i = 0; i < nPasses; i++)
	{
		//create a new map
		unsigned char* map = new unsigned char[nMapWidth*nMapHeight];
		//fill the map with specified (random) data
		FillBuffer(map, nRandomData, nMapWidth*nMapHeight, nFrequency);
		//create new out buffer for path
		int* pOutBuffer = new int[nOutBufferSize];
		//call find path asm routine
		if (!nUseFailsafe)
		{
			pathlength = FindPathASMRoutine(nStartX, nStartY, nTargetX, nTargetY, map, nMapWidth, nMapHeight, pOutBuffer,
				nOutBufferSize, nIncludeDiagonal);
		}
		else
		{
			pathlength = FindPathExMSVC(nStartX, nStartY, nTargetX, nTargetY, map, nMapWidth, nMapHeight, pOutBuffer,
				nOutBufferSize, nIncludeDiagonal);
		}
		//count path failures
		if (pathlength <= 0)
		{
			failures++;
		}
		//delete map data
		delete[] map;
		//delete path data
		delete[] pOutBuffer;
	}
	//stop timer
	nOutTimeMS = ((std::clock() - start) / (double)CLOCKS_PER_SEC) * 1000.0;
	//return path failure counter
	return failures;
}