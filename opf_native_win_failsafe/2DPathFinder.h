/*
Declarations for the MSVC++ failsafe 2DPathFinder class:
Written by:	Jonas Brown
Date:		11/01-2017
File: 		2DPathFinder.h
*/

//Headers:
#pragma once
#include "2DNode.h"
#include <vector>

class _2DPathFinder
{
private:
	//Internal Members:
	std::vector<std::vector<_2DNode>> mGridSnapshot;	//vector grid of input map snapshot
	std::list<_2DNode*> mOpen;							//list of ptrs to open nodes
	std::deque<_2DNode*> mShortestPath;					//deque of shortest path if found
	unsigned short mMapWidth = 0;						//map width in nodes
	unsigned short mMapHeight = 0;						//map height in nodes
	unsigned char mBaseCost;

	//Internal Functions:

	/* -------------------------------------------------------------------------------------------	
	** Helper function. Checks nodes adjecent to current node by offset. Checks if out-of-bounds. 
	** Checks if closed or non-traversable. Checks if node has parent.
	>> Params:
	--->	nOffsetX		=	Offset to adjecent on x-axis.
	--->	nOffsetY		=	Offset to adjecent on y-axis.
	--->	pTargetPoint	=	Ptr to target point.
	--->	pCurrentNode	=	Ptr to potential parent of adjecent node.
	--->	pOpen			=	Ptr to the open list
	<< Returns:
	<---	0				=	Adjecent node was out-of-bounds.
	<---	1				=	Adjecent node was closed or non traversable.
	<---	2				=	Adjecent node was NOT updated.
	<---	3				=	Adjecent node was updated.
	<---	4				=	Adjecent node was initialized.
	<---	5				=	Adjecent node is target node.
	------------------------------------------------------------------------------------------ */
	char fUpdateAdjecentNode(const char nOffsetX, const char nOffsetY, _2DNode *pCurrentNode,
		_2DNode *pTargetNode, std::list<_2DNode*> *pOpen);


public:
	//MS-Style Properties (Will only compile with MSCV++):
	__declspec (property (get = GetGridSnapshot)) std::vector<std::vector<_2DNode>> GridSnapshot;
	std::vector<std::vector<_2DNode>> GetGridSnapshot() { return mGridSnapshot; }
	__declspec (property (get = GetOpen)) std::list<_2DNode*>* OpenPtr;
	std::list<_2DNode*>* GetOpen() { return &mOpen; }
	__declspec (property (get = GetShortestPath)) std::deque<_2DNode*>* ShortestPathPtr;
	std::deque<_2DNode*>* GetShortestPath() { return &mShortestPath; }
	__declspec (property (get = GetBaseCost)) unsigned char BaseCost;
	unsigned char GetBaseCost() { return mBaseCost; }
	__declspec (property (get = GetDimensions)) std::pair<unsigned short, unsigned short> Dimensions;
	std::pair<unsigned short, unsigned short> GetDimensions()
	{
		std::pair<unsigned short, unsigned short> dimensions = { mMapWidth, mMapHeight };
		return dimensions;
	}

	//Public Functions:
	/* ---------------------------------------------------------------------------------------------
	** Finds the shortest path from start-point to target-point.
	** Allocates memory for a grid of nodes pointers and the actual nodes, based on input.
	** Initializes identifiers and topography.
	>> Params:
	--->	nStartX, nStartY		=	x,y coordinates of starting position	
	--->	nStartX, nStartY		=	x,y coordinates of target poaition
	--->	pMap					=	Ptr to buffer of topographic data for grid. 
	--->	nMapWidth, nMapHeight	=	Dimensions of grid in nodes.
	--->	pOutBuffer				=	Ptr to a buffer that will contain id of shortest path nodes.
	--->	nOutBufferSize			=	Maximum number of nodes allowed in path.
	--->	nNewSnapshot			=	Current snapshot will not be saved for this FindPath() call; default = true.
	<< Returns:
	<---	-1						=	No path found. pOutBuffer is "empty".
	<---	 n						=	Length of shortest path found.	
	---------------------------------------------------------------------------------------------- */
	int FindPath(const unsigned short nStartX, const unsigned short nStartY, const unsigned short nTargetX, 
		const unsigned int nTargetY, const unsigned char *pMap, const unsigned short nMapWidth, const unsigned short nMapHeight, 
		int *pOutBuffer, const unsigned int nOutBufferSize, const bool nIncludeDiagonal = false, 
		const unsigned char nNodeBaseCost = 1, const bool nNewSnapshot = true);
};