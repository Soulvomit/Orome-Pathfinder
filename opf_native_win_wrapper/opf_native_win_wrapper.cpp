/*
Definitions for oromë pathfinder native windows library:
Author:		Jonas Brown
Date:		18/12-2016
File: 		opf_native_interface_threaded.cpp
*/
#pragma once
#include "opf_native_win_wrapper.h"

//global type defined pointer to FindPath routine 
ASM_INTERFACE FindPathASMRoutine = (ASM_INTERFACE)0x0;
//global unstance ptr to opf.dll
HINSTANCE hPathfinder = nullptr;

BOOL APIENTRY DllMain(HMODULE hModule, WORD ul_reason_for_call, LPVOID lpReserved)
{
	int result = 0;
	if (!lpReserved)
	{
		//was dynamic load
		result = 1;
	}
	if (!hModule)
	{
		//this module not loaded
		result = 0;
	}
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//when a process attaches to .dll
		result = LoadResources();
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		//when a process detaches to .dll
		result = FreeResources();
		break;
	}
	return TRUE;
}

bool LoadResources() 
{
	//try to load opf.dll library
	hPathfinder = LoadLibrary(L"opf.dll");
	//if load fails
	if (!hPathfinder)
	{
		//don't load resources
		return false;
	}
	//else; set FindPath ptr to address of FindPath assembly routine
	FindPathASMRoutine = (ASM_INTERFACE)GetProcAddress(hPathfinder, "FindPath");
	//if we can't locate routine
	if (!FindPathASMRoutine)
	{
		//free loaded opf.dll library
		FreeLibrary(hPathfinder);
		//don't load resources
		return false;
	}
	//else; everything loaded, all good!
	return true;
}

bool FreeResources()
{
	//if opf.dll is not loaded
	if (!hPathfinder)
	{
		//fon't try to free
		return false;
	}
	//else; set FindPath ptr to null
	FindPathASMRoutine = (ASM_INTERFACE)0x0;
	//free opf.dll library
	FreeLibrary(hPathfinder);
	return true;
}

void FillBuffer(unsigned char* map, bool randomly, unsigned int size, unsigned char frequency)
{
	//if we want to generete random data
	if (randomly)
	{
		//initialize random seed
		srand((unsigned int)time(NULL));
		//foreach byte in buffer
		for (unsigned int i = 0; i < size; i++)
		{
			//set byte to traversable
			map[i] = 1;
			//generate random number between 0 and frequency
			int rng = rand() % frequency;
			//if 0 is rolled
			if (rng == 0)
			{
				//set byte to non-traversable (blocked)
				map[i] = 0;
			}
		}
	}
	//else; we want non-random data
	else
	{
		//foreach byte in buffer
		for (unsigned int i = 0; i < size; i++)
		{
			//set byte to traversable
			map[i] = 1;
		}
	}
}