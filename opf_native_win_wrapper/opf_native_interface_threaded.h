/*
Declarations for oromë pathfinder native windows library:
Author:		Jonas Brown
Date:		18/12-2016
File: 		opf_native_interface_threaded.h
*/

#pragma once
#include "opf_native_win_wrapper.h"
#define FAILSAFE_NODE_SIZE 50	//size of the internal node of the failsafe in bytes; don't change
#define NODE_SIZE 58			//size of the internal node of the opf.dll in bytes; don't change
#define SHADOW_SIZE 1000		//size of shadow space, must be atleast 88 bytes for thread local storage

//defines thread instance data; all data is threadsafe if accessed through interface functions 
struct PFTHREAD_INSTANCE_DATA
{
	bool Done = true;				//true if thread instance is done working
	HANDLE PInstance = nullptr;		//ptr to the thread instance internal thread
	int* POutBuffer = nullptr;		//ptr to the thread instance outbuffer
	int PathLength = -10;			//-2 if the thread instance is still working, else pathlength > -2 
};
//defines thread parameter list 
struct PFTHREAD_PARAMS 
{
	int StartX = 0;
	int StartY = 0;
	int TargetX = 0;
	int TargetY = 0;
	const unsigned char* PMap = nullptr;
	int MapWidth = 0;
	int MapHeight = 0;
	PFTHREAD_INSTANCE_DATA* PTid = nullptr;
    int OutBufferSize = 0;
	bool IncludeDiagonals = true;
	unsigned char NodeBaseCost = 1;
};

/***************************************************************************************************************************
** Starts a thread which finds the shortest path from start-point to target-point. Diagonals are excluded.
>> Params:
--->	nStartX, nStartY		=	X,Y coordinates of starting position.
--->	nStartX, nStartY		=	X,Y coordinates of target poaition.
--->	pMap					=	Char buffer ptr to map topographic data. 0 = non-traversable. 1 = traversable.
--->	nMapWidth, nMapHeight	=	Dimensions of grid in nodes.
--->	nOutBufferSize			=	Maximum number of nodes allowed in path.
<< Returns:
<---	pTid						=	Ptr to data that is specific for this thread instance.
***************************************************************************************************************************/
extern "C" __declspec(dllexport) PFTHREAD_INSTANCE_DATA* FindPathThreaded(const int nStartX, const int nStartY, 
	const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, 
	const int nOutBufferSize, const bool nUseFailsafe = false);

/***************************************************************************************************************************
** Starts a thread which extends on the functionality of FindPathThreaded(). Diagonals; optional.
** Increased diagonal cost; optional. Custom base cost and resistance multiplier; optional.
>> Changed/Added Params:
--->	pMap					=	Char buffer with topographic data. !0 = resistance. 0 = non-traversable.
--->	nIncludeDiagonal		=	Diagonal movement is enabled; default = false.
--->	nNodeBaseCost			=	Base cost of traversing a node; default = 1
***************************************************************************************************************************/
extern "C" __declspec(dllexport) PFTHREAD_INSTANCE_DATA* FindPathExThreaded(const int nStartX, const int nStartY, 
	const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, 
	const int nOutBufferSize, const bool nIncludeDiagonal = false, const unsigned char nNodeBaseCost = 1, 
	const bool nUseFailsafe = false);

/**************************************************************************************************************************
** Extends on the functionality of FindPathEx(). Provides profiling options to let the caller benchmark
** the pathfinding algorithm.
>> Changed/Added Params:
--->	nPasses					=	Times to run algorithm on static data.
--->	nRandomdata				=	Toggles whether random or static data should be used for profiling.
--->	nFrequency				=	How often a tiles is randomly blocked. 1/frequency is bocked.
<> Out Params:
<-->	nOutTimeMS				=	Time in MS it took to run the algorithm on static data nPasses times.
<< Returns:
<---	n				=	How many times a profiling thread/pass failed to find a path. 
***************************************************************************************************************************/
extern "C" __declspec(dllexport) int FindPathExProfilingThreaded(const int nStartX, const int nStartY, const int nTargetX,
	const int nTargetY, const int nMapWidth, const int nMapHeight, const int nOutBufferSize, double& nOutTimeMS, 
	const int nPasses = 1, const int nMaxThreads = 4, const bool nIncludeDiagonal = false, const unsigned char  nNodeBaseCost = 1, 
	const bool nRandomData = true, const unsigned char nFrequency = 2, const bool nUseFailsafe = false);

//check if thread is ready to join; joins thread if ready, else returns false
extern "C" __declspec(dllexport) bool PFThreadJoin(PFTHREAD_INSTANCE_DATA* pTid);
//waits for thread to finish and joins when it is finished
extern "C" __declspec(dllexport) bool PFThreadWaitJoin(PFTHREAD_INSTANCE_DATA* pTid);
//returns true if thread is done; false if thread is still working
extern "C" __declspec(dllexport) bool PFThreadDone(PFTHREAD_INSTANCE_DATA* pTid);
//gets the returned outbuffer if thread is done; else returns false
extern "C" __declspec(dllexport) int* PFThreadGetPOutbuffer(PFTHREAD_INSTANCE_DATA* pTid);
//gets the returned path length if thread is done; else returns false
extern "C" __declspec(dllexport) int  PFThreadGetPathLength(PFTHREAD_INSTANCE_DATA* pTid);
//stops thread and does cleanup, if thread is not done results data will be lost
extern "C" __declspec(dllexport) void PFThreadDeleteTID(PFTHREAD_INSTANCE_DATA* pTid);

//the winapi thread handler interface
DWORD WINAPI PFThreadHandler(LPVOID lpParam);
//the winapi failsafe thread handler interface
DWORD WINAPI PFThreadHandlerFailsafe(LPVOID lpParam);