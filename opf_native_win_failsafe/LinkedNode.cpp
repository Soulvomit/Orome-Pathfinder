/*
Definitions for the MSVC++ failsafe LinkedNode class:
Written by:	Jonas Brown
Date:		11/01-2017
File: 		LinkedNode.cpp
*/

#include "LinkedNode.h"

bool LinkedNode::Initialize(LinkedNode *pTargetNode, LinkedNode *pCurrentNode, std::list<LinkedNode*> *pOpen)
{
	//set current node as this nodes parent
	pParent = pCurrentNode;
	//initialize g cost 
	mGCost = pParent->G + mResistance;
	//check if this node is target node; return true
	if (pTargetNode == pCurrentNode) return true;
	//else initialize f costs
	mFCost = mGCost + mHCost;
	//open node and sort it
	int debugcode = fSortedInsert(pOpen);
	return false;
}
bool LinkedNode::Update(LinkedNode *pCurrentNode)
{
	//compute new g costs
	unsigned int newGCost = pCurrentNode->G + mResistance;
	//compute new f costs
	unsigned int newFCost = newGCost + mHCost;
	//if updated f cost is larger then current f cost, or f costs are equal and path is longer; don't update
	if (newFCost > mFCost || (newFCost == mFCost && newGCost >= mGCost)) return false;
	//else update all costs and set new parent; return true
	pParent = pCurrentNode;
	mGCost = newGCost;
	//mHCost = newHCost;
	mFCost = newFCost;
	return true;
}
void LinkedNode::Traceback(std::deque<LinkedNode*> *pShortestPath)
{
	//NOTE: Implement some kind of check to avoid recursion ad infinitum.

	//if current traceback nodes parent is not null, we have not reached start node
	if (pParent != NULL)
	{
		//front push node to shortest path to get a "reverse effect"
		pShortestPath->push_front(this);
		//recursively trace back through parents 
		pParent->Traceback(pShortestPath);
	}
}
char LinkedNode::fSortedInsert(std::list<LinkedNode*> *pOpen)
{
	//NOTE: For larger maps consider using a binary tree (std::multiset?) for faster lookup. 	

	//if there are no open nodes or this node is cheaper then first open node
	if (pOpen->empty() || pOpen->front()->F >= F)
	{
		//push this node to front
		pOpen->push_front(this);
		return 0;
	}
	//if this node is more expensive then last node to check 
	if (pOpen->back()->F < F)
	{
		//push this node to back
		pOpen->push_back(this);
		return 1;
	}
	//for all open nodes
	for (std::list<LinkedNode*>::iterator current = pOpen->begin(); current != pOpen->end(); current++)
	{
		//if this node is cheaper then current lookup
		if ((*current)->F > F)
		{
			//insert this node before current lookup
			pOpen->insert(current, this);
			return 2;
		}
		//if costs are the same and this node is closer to target node then current lookup
		else if ((*current)->F == F && (*current)->H >= H)
		{
			//insert this node before current lookup
			pOpen->insert(current, this);
			return 3;
		}
		//lookup next node; current++
	}
	//error: this should never be reached; for testing
	return -1;
}