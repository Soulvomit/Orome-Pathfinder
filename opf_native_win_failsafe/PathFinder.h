/*	
Interface descriptor for PathFinder class:
Written by:	Jonas Brown
Date:		08/04-2016
File: 		PathFinder.h
*/

//Headers:
#pragma once
#include "Node.h"
#include <vector>

class PathFinder
{
private:
	//Internal Members:
	std::vector<std::vector<Node>> mGridSnapshot;		//vector grid of input map snapshot
	std::list<Node*> mOpen;								//list of ptrs to open nodes
	std::deque<Node*> mShortestPath;					//deque of shortest path if found
	int mMapWidth = 0;									//map width in nodes
	int mMapHeight = 0;									//map height in nodes

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
	unsigned char fUpdateAdjecentNode(const int nOffsetX, const int nOffsetY, Node *pCurrentNode, 
		Node *pTargetNode, std::list<Node*> *pOpen);


public:
	//MS-Style Properties (Will only compile with MSCV++):
	__declspec (property (get = GetGridSnapshot)) std::vector<std::vector<Node>> GridSnapshot;
	std::vector<std::vector<Node>> GetGridSnapshot() { return mGridSnapshot; }
	__declspec (property (get = GetOpen)) std::list<Node*>* OpenPtr;
	std::list<Node*>* GetOpen() { return &mOpen; }
	__declspec (property (get = GetShortestPath)) std::deque<Node*>* ShortestPathPtr;
	std::deque<Node*>* GetShortestPath() { return &mShortestPath; }
	__declspec (property (get = GetDimensions)) std::pair<int, int> Dimensions;
	std::pair<int, int> GetDimensions() 
	{
		std::pair<int, int> dimensions = { mMapWidth, mMapHeight };
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
	int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, 
		const unsigned char *pMap, const int nMapWidth, const int nMapHeight, int *pOutBuffer, 
		const int nOutBufferSize, const bool nIncludeDiagonal = false, const int nNodeBaseCost = 1, 
		const bool nNewSnapshot = true);
};