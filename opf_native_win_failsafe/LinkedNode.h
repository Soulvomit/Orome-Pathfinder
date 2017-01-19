/*
Declarations for the MSVC++ failsafe LinkedNode class:
Written by:	Jonas Brown
Date:		11/01-2017
File: 		LinkedNode.h
*/

//Headers:
#pragma once
#include <list>
#include <deque>
#include <vector>

class LinkedNode
{
private:
	//Internal Members:
	bool mTraversable;							//set if node is non-traversable
	bool mClosed = false;						//set if node has been checked
	unsigned int mID;
	unsigned char mResistance;
	std::vector<LinkedNode*> mLinks;
	LinkedNode *pParent = NULL;					//ptr to next node in the best path, from this node to start
	unsigned int mGCost = 0;					//cost of this nodes current path to start
	unsigned int mHCost = 0;					//cost of manhattan distance to target
	unsigned int mFCost = 0;					//g + h = combined cost

	//Internal Functions:
	/* ------------------------------------------------------------------------------
	** Searches the open list fand finds the approiately place to incert this node.
	** Sorting is based on lowest f cost.
	** If f costs are equal, h costs are used as a tiebreaker.
	>> Params:
	--->	pOpen	=	Ptr to the open list used for insertion.
	<< Returns:
	<---   -1		=	Error: Node was not inserted.
	<---	0		=	Node was pushed to open lists front.
	<---	1		=	Node was pushed to open lists back.
	<---	2		=	Node was inserted using f-costs to determine insertion point.
	<---	3		=	Node was inserted using h-costs to determine insertion point.
	------------------------------------------------------------------------------- */
	char fSortedInsert(std::list<LinkedNode*> *pOpen);

public:
	//Constructor:
	LinkedNode(unsigned int id, unsigned char resistance, bool traversable = true)
	{
		mID = id;
		mResistance = resistance;
		mTraversable = traversable;
	}

	//MS-Style Properties (Will only compile with MSVC++):
	__declspec (property (put = SetClosed, get = GetClosed)) bool Closed;
	void SetClosed(bool value) { mClosed = value; }
	bool GetClosed() const { return mClosed; }
	__declspec (property (put = SetTraversable, get = GetTraversable)) bool Traversable;
	void SetTraversable(bool value) { mTraversable = value; }
	bool GetTraversable() const { return mTraversable; }
	__declspec (property (put = SetID, get = GetID)) unsigned int ID;
	void SetID(unsigned int value) { mID = value; }
	unsigned int GetID() const { return mID; }
	__declspec (property (get = GetLinks)) std::vector<LinkedNode*> Links;
	std::vector<LinkedNode*> GetLinks() const { return mLinks; }
	__declspec (property (put = SetParent, get = GetParent)) LinkedNode *ParentPtr;
	void SetParent(LinkedNode *pValue) { pParent = pValue; }
	LinkedNode *GetParent() const { return pParent; }
	__declspec (property (get = GetG)) int G;
	int GetG() const { return mGCost; }
	__declspec (property (get = GetH)) int H;
	int GetH() const { return mHCost; }
	__declspec (property (get = GetF)) int F;
	int GetF() const { return mFCost; }

	//Public Functions:
	/* ---------------------------------------------------------------------
	** Traces back all nodes from this node to starting node and deque them.
	>> Params:
	--->	pShortestPath	=	Pointer to output deque of shortest path.
	<< Returns:
	<---	void			=	Void ptr.
	---------------------------------------------------------------------- */
	void Traceback(std::deque<LinkedNode*> *pShortestPath);
	/* ----------------------------------------------------------------------------
	** Initializes g, h and f costs and parent for this node, and opens it.
	>> Params:
	--->	pTargetNode	=	Ptr to target node.
	--->	pCurrentNode	=	Ptr to parent for this node.
	--->	pOpen			=	Ptr to the open list.
	<< Returns:
	<---	false			=	Node was not target, fully initialized and opened.
	<---	true			=	Node was target node, not fully initialized.
	----------------------------------------------------------------------------- */
	bool Initialize(LinkedNode *pTargetNode, LinkedNode *pCurrentNode, std::list<LinkedNode*> *pOpen);
	/* --------------------------------------------------------------------------------------
	** Updates g, h and f costs and parent for this node, if f costs are lower then before.
	** Uses g costs as tie-breaker. Does not update if g costs are tied.
	>> Params:
	--->	pCurrentNode	=	Ptr potential new parent for this node.
	<< Returns:
	<---	false			=	No update was necessary.
	<---	true			=	Node was updated.
	--------------------------------------------------------------------------------------- */
	bool Update(LinkedNode *pCurrentNode);
};
