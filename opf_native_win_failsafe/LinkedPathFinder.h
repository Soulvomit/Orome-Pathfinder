/*
Declarations for the MSVC++ failsafe LinkedPathFinder class:
Written by:	Jonas Brown
Date:		11/01-2017
File: 		LinkedPathFinder.h
*/

//Headers:
#pragma once
#include "LinkedNode.h"

class LinkedPathFinder
{
private:
	//Internal Members:
	std::vector<LinkedNode> mSnapshot;					//vector grid of input map snapshot
	std::list<LinkedNode*> mOpen;						//list of ptrs to open nodes
	std::deque<LinkedNode*> mShortestPath;				//deque of shortest path if found

	//Internal Functions:
	/* -------------------------------------------------------------------------------------------
	** Helper function. Checks nodes adjecent to current node by offset. Checks if out-of-bounds.
	** Checks if closed or non-traversable. Checks if node has parent.
	>> Params:
	--->	pAdjecentNode	=	Ptr to adjecent node.
	--->	pCurrentNode	=	Ptr to potential parent of adjecent node.
	--->	pTargetNode		=	Ptr to target point.
	--->	pOpen			=	Ptr to the open list
	<< Returns:
	<---	0				=	Adjecent node was out-of-bounds.
	<---	1				=	Adjecent node was closed or non traversable.
	<---	2				=	Adjecent node was NOT updated.
	<---	3				=	Adjecent node was updated.
	<---	4				=	Adjecent node was initialized.
	<---	5				=	Adjecent node is target node.
	------------------------------------------------------------------------------------------ */
	char fUpdateAdjecentNode(LinkedNode *pAdjecentNode, LinkedNode *pCurrentNode,
		LinkedNode *pTargetNode, std::list<LinkedNode*> *pOpen);


public:
	//MS-Style Properties (Will only compile with MSCV++):
	__declspec (property (get = GetSnapshot)) std::vector<LinkedNode> Snapshot;
	std::vector<LinkedNode> GetSnapshot() { return Snapshot; }
	__declspec (property (get = GetOpen)) std::list<LinkedNode*>* OpenPtr;
	std::list<LinkedNode*>* GetOpen() { return &mOpen; }
	__declspec (property (get = GetShortestPath)) std::deque<LinkedNode*>* ShortestPathPtr;
	std::deque<LinkedNode*>* GetShortestPath() { return &mShortestPath; }

	//Public Functions:
	/* ---------------------------------------------------------------------------------------------
	** Finds the shortest path from start-point to target-point.
	** Allocates memory for nodes pointers and the actual nodes, based on input.
	** Initializes identifiers and topography.
	>> Params:
	--->	nStartID				=	ID of starting position
	--->	nTargetID				=	ID of target poaition
	--->	pIDBuffer				=	Ptr to buffer of topographic data.
	--->	pLinkCountBuffer		=	Ptr to buffer of link counts.
	--->	pLinkIDBuffer			=	Ptr to buffer of link counts.
	--->	pOutBuffer				=	Ptr to a buffer that will contain id of shortest path nodes.
	--->	nOutBufferSize			=	Maximum number of nodes allowed in path.
	--->	nNewSnapshot			=	Current snapshot will not be saved for this FindPath() call; default = true.
	<< Returns:
	<---	-1						=	No path found. pOutBuffer is "empty".
	<---	 n						=	Length of shortest path found.
	---------------------------------------------------------------------------------------------- */
	int FindPath(const unsigned int nStartID, const unsigned int nTargetID, const unsigned char *pLinkCountBuffer, 
		const unsigned char *pResistanceBuffer, const unsigned int *pLinkIDBuffer, int *pOutBuffer, const unsigned int nBufferSize, 
		const unsigned int nOutBufferSize, const bool nNewSnapshot = true);
};
