/*
Definitions for oromë pathfinder native windows library:
Author:		Jonas Brown
Date:		18/12-2016
File: 		opf_native_interface_threaded.cpp
*/
#pragma once
#include "opf_native_interface_threaded.h"

PFTHREAD_INSTANCE_DATA* FindPathThreaded(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight, const int nOutBufferSize, const bool nUseFailsafe)
{
	PFTHREAD_INSTANCE_DATA* pTid = new PFTHREAD_INSTANCE_DATA();	//create new thread data
	pTid->POutBuffer = new int[nOutBufferSize];						//create new buffer
	pTid->Done = false;												//set done flag
	PFTHREAD_PARAMS* params = new PFTHREAD_PARAMS();				//create new thread params
	params->StartX = nStartX;										//set StartX thread param
	params->StartY = nStartY;										//set StartY thread param
	params->TargetX = nTargetX;										//set TargetX thread param
	params->TargetY = nTargetY;										//set TargetY thread param
	params->PMap = pMap;											//set map ptr thread param
	params->MapWidth = nMapWidth;									//set MapWidth thread param
	params->MapHeight = nMapHeight;									//set MapHeight thread param
	params->PTid = pTid;											//set thread data ptr thread param
	params->OutBufferSize = nOutBufferSize;							//set OutBufferSize thread param
	params->IncludeDiagonals = false;								//set IncludeDiagonals thread param
	params->NodeBaseCost = 1;										//set NodeBaseCost thread param
	//create new thread with the appropriate stack size and pass the thread params 
	if (!nUseFailsafe)
	{
		pTid->PInstance = CreateThread(NULL, (nMapWidth * nMapHeight * NODE_SIZE) + SHADOW_SIZE, PFThreadHandler, params, 0, NULL);
	}
	else
	{ 
		pTid->PInstance = CreateThread(NULL, (nMapWidth * nMapHeight * FAILSAFE_NODE_SIZE) + SHADOW_SIZE, PFThreadHandlerFailsafe, params, 0, NULL);
	}
	//set thread to highest priority
	SetThreadPriority(pTid->PInstance, THREAD_PRIORITY_HIGHEST);
	//return thread data
	return pTid;
}

PFTHREAD_INSTANCE_DATA* FindPathExThreaded(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight, const int nOutBufferSize, const bool nIncludeDiagonal, 
	const unsigned char nNodeBaseCost, const bool nUseFailsafe)
{
	PFTHREAD_INSTANCE_DATA* pTid = new PFTHREAD_INSTANCE_DATA();	//create new thread data
	pTid->POutBuffer = new int[nOutBufferSize];						//create new buffer
	pTid->Done = false;												//set done flag
	PFTHREAD_PARAMS* params = new PFTHREAD_PARAMS();				//create new thread params
	params->StartX = nStartX;										//set StartX thread param
	params->StartY = nStartY;										//set StartY thread param
	params->TargetX = nTargetX;										//set TargetX thread param
	params->TargetY = nTargetY;										//set TargetY thread param
	params->PMap = pMap;											//set map ptr thread param
	params->MapWidth = nMapWidth;									//set MapWidth thread param
	params->MapHeight = nMapHeight;									//set MapHeight thread param
	params->PTid = pTid;											//set thread data ptr thread param
	params->OutBufferSize = nOutBufferSize;							//set OutBufferSize thread param
	params->IncludeDiagonals = nIncludeDiagonal;					//set IncludeDiagonals thread param
	params->NodeBaseCost = nNodeBaseCost;							//set NodeBaseCost thread param
    //create new thread with the appropriate stack size and pass the thread params 
	if (!nUseFailsafe)
	{
		pTid->PInstance = CreateThread(NULL, (nMapWidth * nMapHeight * NODE_SIZE) + SHADOW_SIZE, PFThreadHandler, params, 0, NULL);
	}
	else
	{
		pTid->PInstance = CreateThread(NULL, (nMapWidth * nMapHeight * FAILSAFE_NODE_SIZE) + SHADOW_SIZE, PFThreadHandlerFailsafe, params, 0, NULL);
	}
	//set thread to highest priority
	SetThreadPriority(pTid->PInstance, THREAD_PRIORITY_HIGHEST);
	//return thread data
	return pTid;
}

int FindPathExProfilingThreaded(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const int nMapWidth, 
	const int nMapHeight, const int nOutBufferSize, double& nOutTimeMS, const int nPasses, const int nMaxThreads, const bool nIncludeDiagonal, 
	const unsigned char nNodeBaseCost, const bool nRandomData, const unsigned char nFrequency, const bool nUseFailsafe)
{
	int failures = 0;
	//create map deque
	std::deque<unsigned char*> map_deque;
	//create thread deque
	std::deque<PFTHREAD_INSTANCE_DATA*> thread_deque;
	//start timer
	std::clock_t start = std::clock();
	//create threaded work load
	for (int i = 0; i < nPasses; i++)
	{
		PFTHREAD_INSTANCE_DATA* pTid = new PFTHREAD_INSTANCE_DATA();
		thread_deque.push_back(pTid);
		pTid->POutBuffer = new int[nOutBufferSize];
		pTid->Done = false;
		PFTHREAD_PARAMS* params = new PFTHREAD_PARAMS();
		params->StartX = nStartX;
		params->StartY = nStartY;
		params->TargetX = nTargetX;
		params->TargetY = nTargetY;
		//create new map
		unsigned char* map = new unsigned char[nMapWidth*nMapHeight];
		//fill map with specified (random) data
		FillBuffer(map, nRandomData, nMapWidth*nMapHeight, nFrequency);
		//push map to deque
		map_deque.push_back(map);
		params->PMap = map;
		params->MapWidth = nMapWidth;
		params->MapHeight = nMapHeight;
		params->PTid = pTid;
		params->OutBufferSize = nOutBufferSize;
		params->IncludeDiagonals = nIncludeDiagonal;						//set IncludeDiagonals thread param
		params->NodeBaseCost = nNodeBaseCost;								//set NodeBaseCost thread param
		//thread deque size is above max threads 
		if (thread_deque.size() > nMaxThreads)
		{
			//wait for and join the first thread in deque
			PFThreadWaitJoin(thread_deque.front());
			//if the first threads pathlengt is 0 or less
			if (thread_deque.front()->PathLength <= 0)
			{
				//count it as a failure
				failures++;
			}
			//remove first thread from deque
			thread_deque.pop_front();
		}
		//create new thread with the appropriate stack size and pass the thread params
		if (!nUseFailsafe)
		{
			pTid->PInstance = CreateThread(NULL, (nMapWidth * nMapHeight * NODE_SIZE) + SHADOW_SIZE, PFThreadHandler, params, 0, NULL);
		}
		else
		{
			pTid->PInstance = CreateThread(NULL, (nMapWidth * nMapHeight * FAILSAFE_NODE_SIZE) + SHADOW_SIZE, PFThreadHandlerFailsafe, params, 0, NULL);
		}
		//set thread priority to highest
		SetThreadPriority(pTid->PInstance, THREAD_PRIORITY_HIGHEST);
	}
	//wait for and join the last active threads
	for (int i = 0; i < thread_deque.size(); i++)
	{
		PFThreadWaitJoin(thread_deque[i]);
		if (thread_deque[i]->PathLength <= 0)
		{
			failures++;
		}
	}
	//stop timer
	nOutTimeMS = ((std::clock() - start) / (double)CLOCKS_PER_SEC) * 1000.0;
	//delete map data at ptrs 
	for (int i = 0; i < map_deque.size(); i++)
	{
		delete[]  map_deque[i];
	}
	//transfer last outbuffer
	//int pathlenght = thread_deque[0]->PathLength;
	//delete all thread data at ptrs
	for (int i = 0; i < thread_deque.size(); i++)
	{
		PFThreadDeleteTID(thread_deque[i]);
	}
	return failures;
}

bool PFThreadJoin(PFTHREAD_INSTANCE_DATA* pTid)
{
	//if thread isnt done OR there is no running thread
	if (!pTid->Done || !pTid->PInstance)
	{
		//return false
		return false;
	}
	//else; join thread with no time-out
	WaitForSingleObject(pTid->PInstance, INFINITE);
	//close thread handle
	CloseHandle(pTid->PInstance);
	//null the thread handle ptr
	pTid->PInstance = nullptr;
	//return true
	return true;
}

bool PFThreadWaitJoin(PFTHREAD_INSTANCE_DATA* pTid)
{
	//there is no running thread
	if (!pTid->PInstance)
	{
		//return false
		return false;
	}
	//else; join thread with no time-out
	WaitForSingleObject(pTid->PInstance, INFINITE);
	//close thread handle
	CloseHandle(pTid->PInstance);
	//null the thread handle ptr
	pTid->PInstance = nullptr;
	//return true
	return true;
}

bool PFThreadDone(PFTHREAD_INSTANCE_DATA* pTid)
{
	//if thread is done
	if (pTid->Done)
	{
		//return true
		return true;
	}
	//if thread isn't done
	else
	{
		//return false
		return false;
	}
}

int* PFThreadGetPOutbuffer(PFTHREAD_INSTANCE_DATA* pTid)
{
	//if thread is done
	if (pTid->Done)
	{
		//return outbuffer with path data
		return pTid->POutBuffer;
	}
	//if thread isn't done
	else
	{
		//null ptr
		return nullptr;
	}
}

int PFThreadGetPathLength(PFTHREAD_INSTANCE_DATA* pTid)
{
	//if thread is done
	if (pTid->Done)
	{
		//return path lenght
		return pTid->PathLength;
	}
	//if thread isn't done
	else
	{
		//return errorcode: -10
		return -10;
	}
}

void PFThreadDeleteTID(PFTHREAD_INSTANCE_DATA* pTid)
{
	//if thread is running
	if (pTid->PInstance)
	{
		//close thread handle
		CloseHandle(pTid->PInstance);
		//null thread handle
		pTid->PInstance = nullptr;
	}
	//delete the outbuffer data
	delete[] pTid->POutBuffer;
	//null outbuffer
	pTid->POutBuffer = nullptr;
	//delete the thread data struct
	delete pTid;
	//null thread data
	pTid = nullptr;
}

DWORD WINAPI PFThreadHandler(LPVOID lpParam)
{
	//convert params to thread params
	PFTHREAD_PARAMS* params = (PFTHREAD_PARAMS*)lpParam;
	//call find path asm routine with passed thread params
	params->PTid->PathLength = FindPathASMRoutine(params->StartX, params->StartY, params->TargetX, 
		params->TargetY, params->PMap, params->MapWidth, params->MapHeight, params->PTid->POutBuffer, 
		params->OutBufferSize, params->IncludeDiagonals, params->NodeBaseCost);
	//set done flag to true
	params->PTid->Done = true;
	//return 0
	return 0;
}

DWORD WINAPI PFThreadHandlerFailsafe(LPVOID lpParam)
{
	//convert params to thread params
	PFTHREAD_PARAMS* params = (PFTHREAD_PARAMS*)lpParam;
	//call find path c++ failsafe routine with passed thread params
	params->PTid->PathLength = FindPathExFailsafe(params->StartX, params->StartY, params->TargetX,
		params->TargetY, params->PMap, params->MapWidth, params->MapHeight, params->PTid->POutBuffer,
		params->OutBufferSize, params->IncludeDiagonals, params->NodeBaseCost);
	//set done flag to true
	params->PTid->Done = true;
	//return 0
	return 0;
}