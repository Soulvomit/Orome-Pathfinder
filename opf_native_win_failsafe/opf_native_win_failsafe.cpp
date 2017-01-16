/*
Logical descriptor for FindPath Library:
Written by:	Jonas Brown
Date:		11/04-2016
File: 		FindPath.h::FindPath.cpp
*/

#include "opf_native_win_failsafe.h"

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

int FindPathFailsafe(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
	const unsigned char *pMap, const int nMapWidth, const int nMapHeight, int *pOutBuffer,
	const int nOutBufferSize)
{
	PathFinder* pPathFinder = new PathFinder();
	int pathlength = pPathFinder->FindPath(nStartX, nStartY, nTargetX, nTargetY, pMap,
		nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize);
	delete pPathFinder;
	return pathlength;
}

int FindPathExFailsafe(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
	const unsigned char *pMap, const int nMapWidth, const int nMapHeight, int *pOutBuffer,
	const int nOutBufferSize, const bool nIncludeDiagonal, const int nNodeBaseCost)
{
	PathFinder* pPathFinder = new PathFinder();
	int pathlength = pPathFinder->FindPath(nStartX, nStartY, nTargetX, nTargetY, pMap,
		nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize, nIncludeDiagonal, nNodeBaseCost);
	delete pPathFinder;
	return pathlength;
}

int FindPathExNoCleanupFailsafe(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
	const unsigned char *pMap, const int nMapWidth, const int nMapHeight, int *pOutBuffer,
	const int nOutBufferSize, PathFinder *&pPathFinder, const bool nIncludeDiagonal,
	const int nNodeBaseCost, const bool nNewSnapshot)
{
	int pathlength;
	if (pPathFinder != NULL && !nNewSnapshot)
	{
		pathlength = pPathFinder->FindPath(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight,
			pOutBuffer, nOutBufferSize, nIncludeDiagonal, nNodeBaseCost, false);
	}
	else
	{
		pPathFinder = new PathFinder();
		pathlength = pPathFinder->FindPath(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight,
			pOutBuffer, nOutBufferSize, nIncludeDiagonal, nNodeBaseCost, true);
	}
	return pathlength;
}
