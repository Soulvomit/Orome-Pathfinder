/*
Declarations for oromë pathfinder native windows library:
Author:		Jonas Brown
Date:		18/12-2016
File: 		opf_native_win_wrapper.h
*/

#pragma once
#include "stdafx.h"
#include <deque>
#include <ctime>

//typedef for FindPath assembly routine interface
typedef int(*ASM_INTERFACE)(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap,
	const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize, const bool nIncludeDiagonals, 
	const unsigned char nNodeBaseCost);

//entrypoint of the FindPath assembly routine
extern ASM_INTERFACE FindPathASMRoutine;
//instance of pathfinder library
extern HINSTANCE hPathfinder;

//entry point runs before executable is loaded by system, unless dynamically loaded.
BOOL APIENTRY DllMain(HMODULE hModule, WORD  ul_reason_for_call, LPVOID lpReserved);
//loads resources; pathfinder library, finds FindPath asm routine, returns false if failure.
bool LoadResources();
//frees resources; pathfinder library, nulls FindPath asm routine, returns false if failure. 
bool FreeResources();
//helper function; fills a buffer with 1's or a random sequence of 1's and 0's
void FillBuffer(unsigned char* map, bool randomly, unsigned int size, unsigned char frequency = 2);