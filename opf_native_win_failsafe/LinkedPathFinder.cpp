/*
Definitions for the MSVC++ failsafe LinkedPathFinder class:
Written by:	Jonas Brown
Date:		11/01-2017
File: 		LinkedPathFinder.cpp
*/

#include "LinkedPathFinder.h"

int LinkedPathFinder::FindPath(const unsigned int nStartID, const unsigned int nTargetID, const unsigned char *pLinkCountBuffer, 
	const unsigned char *pResistanceBuffer, const unsigned int *pLinkIDBuffer,  int *pOutBuffer, const unsigned int nBufferSize, 
	const unsigned int nOutBufferSize, const bool nNewSnapshot)
{
	//initialize the map with given parameters
	if (nNewSnapshot || !mSnapshot.empty())
	{
		for (unsigned int i = 0; i < nBufferSize; i++)
		{
			mSnapshot.push_back(LinkedNode(i, pResistanceBuffer[i],(pResistanceBuffer[i] > 0)));
		}
		//link nodes from given data
		unsigned int counter = 0;
		for (unsigned int i = 0; i < nBufferSize; i++)
		{
			for (unsigned int j = 0; j < pLinkCountBuffer[i]; j++)
			{
				LinkedNode *temp = &mSnapshot[pLinkIDBuffer[counter]];
				mSnapshot[i].Links[j] = temp;
				counter++;
			}
		}
		//calculate heuristic for all nodes
		
	}
	//clear any old data
	mOpen.clear();
	mShortestPath.clear();
	//create a reference to target node from given parameters, and open it
	LinkedNode* pTargetNode = &mSnapshot[nTargetID];
	mOpen = { &mSnapshot[nStartID] };
	//if starting or target node is non-traversable, terminate
	if (!mOpen.front()->Traversable || !pTargetNode->Traversable) return -1;
	//while buffer size has not been exceeded
	for (int i = 0; i < INT32_MAX; i++)
	{
		LinkedNode* pCurrentNode = mOpen.front();		//node we are currently checking
		mOpen.pop_front();								//remove it from open list
		pCurrentNode->Closed = true;					//set the current node to closed
														//for each adjecent node
		for (unsigned char i = 0; i < pCurrentNode->Links.size(); i++)
		{
			//check if adjecent should be updated/initialized 
			char debugcode = fUpdateAdjecentNode(pCurrentNode->Links[i], pCurrentNode, pTargetNode, &mOpen);
			//if adjecent node = target node node has been located
			if (debugcode == 5)
			{
				//create the shortest path
				pTargetNode->Traceback(&mShortestPath);
				//copy id of shortest path nodes to buffer
				for (unsigned int i = 0; i < mShortestPath.size(); i++) pOutBuffer[i] = mShortestPath[i]->ID;
				//return the length of shortest path
				return (int)mShortestPath.size();
			}
		}
		//if there are no more nodes to set as current, path is blocked
		if (mOpen.empty()) return -1;
	}
	//buffer size exceeded = path is to long
	return -1;
}

char LinkedPathFinder::fUpdateAdjecentNode(LinkedNode *pAdjecentNode, LinkedNode *pCurrentNode,
	LinkedNode *pTargetNode, std::list<LinkedNode*> *pOpen)
{
	//if it is closed and is non-traversable 
	if (pAdjecentNode->Closed || !pAdjecentNode->Traversable)
	{
		return 1; //adjecent node closed or untraversable
	}
	//if adjecent node has a parent
	if (pAdjecentNode->ParentPtr)
	{
		//try update, if returns true, node updated; else not update
		if (pAdjecentNode->Update(pCurrentNode))
		{
			return 3; //adjecent node updated
		}
		return 2; //adjecent node not updated
	}
	//else if adjecent node doesn't have a parent; initialize, and check if target found
	if (pAdjecentNode->Initialize(pTargetNode, pCurrentNode, pOpen))
	{
		pTargetNode->ParentPtr = pCurrentNode;
		return 5; //target node found
	}
	return 4; //target node not found
}