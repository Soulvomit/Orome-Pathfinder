/*
Declarations for the MSVC++ failsafe 2DNode class:
Written by:	Jonas Brown
Date:		11/01-2017
File: 		2DNode.h
*/

//Headers:
#pragma once
#include "2DPoint.h"
#include <list>
#include <deque>

class _2DNode
{
private:
	//Internal Members:
	unsigned int mID;				//identifier of node, corrosponds to place on grid
	unsigned char mResistance;		//resistance multiplier of traversing through this node
	_2DPoint mPosition;				//ptr to this nodes 2d point on a grid
	bool mTraversable;				//set if node is non-traversable
	bool mClosed = false;			//set if node has been checked
	_2DNode *pParent = NULL;		//ptr to next node in the best path, from this node to start
	unsigned int mGCost = 0;		//cost of this nodes current path to start
	unsigned int mHCost = 0;		//cost of manhattan distance to target
	unsigned int mFCost = 0;		//g + h = combined cost

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
	char fSortedInsert(std::list<_2DNode*> *pOpen);

public:
	//Constructor:
	_2DNode(unsigned short X, unsigned short Y, unsigned int ID, bool traversable = true, unsigned char resistance = 1)
	{
		mPosition.X = X;
		mPosition.Y = Y;
		mID = ID;
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
	__declspec (property (put = SetParent, get = GetParent)) _2DNode *ParentPtr;
	void SetParent(_2DNode *pValue) { pParent = pValue; }
	_2DNode *GetParent() const { return pParent; }
	__declspec (property (put = SetPosition, get = GetPosition)) _2DPoint Position;
	void SetPosition(_2DPoint mValue) { mPosition = mValue; }
	_2DPoint GetPosition() const { return mPosition; }
	__declspec (property (put = SetID, get = GetID)) unsigned int ID;
	void SetID(unsigned int value) { mID = value; }
	unsigned int GetID() const { return mID; }
	__declspec (property (put = SetResistance, get = GetResistance)) unsigned char Resistance;
	void SetResistance(unsigned char value) { mResistance = value; }
	unsigned char GetResistance() const { return mResistance; }
	__declspec (property (get = GetG)) unsigned int G;
	unsigned int GetG() const { return mGCost; }
	__declspec (property (get = GetH)) unsigned int H;
	unsigned int GetH() const { return mHCost; }
	__declspec (property (get = GetF)) unsigned int F;
	unsigned int GetF() const { return mFCost; }

	//Public Functions:
	/* ---------------------------------------------------------------------
	** Traces back all nodes from this node to starting node and deque them.
	>> Params:
	--->	pShortestPath	=	Pointer to output deque of shortest path.
	<< Returns:
	<---	void			=	Void ptr.
	---------------------------------------------------------------------- */
	void Traceback(std::deque<_2DNode*> *pShortestPath);
	/* ----------------------------------------------------------------------------
	** Initializes g, h and f costs and parent for this node, and opens it.
	>> Params:
	--->	pTargetPoint	=	Ptr to target point.
	--->	pCurrentNode	=	Ptr to parent for this node.
	--->	pOpen			=	Ptr to the open list.
	<< Returns:
	<---	false			=	Node was not target, fully initialized and opened.
	<---	true			=	Node was target node, not fully initialized.	
	----------------------------------------------------------------------------- */
	bool Initialize(_2DPoint *pTargetPoint, _2DNode *pCurrentNode, std::list<_2DNode*> *pOpen, const unsigned char nBaseCost);
	/* --------------------------------------------------------------------------------------
	** Updates g, h and f costs and parent for this node, if f costs are lower then before.
	** Uses g costs as tie-breaker. Does not update if g costs are tied.
	>> Params:
	--->	pCurrentNode	=	Ptr potential new parent for this node.
	<< Returns:
	<---	false			=	No update was necessary.
	<---	true			=	Node was updated.	
	--------------------------------------------------------------------------------------- */
	bool Update(_2DNode *pCurrentNode, const unsigned char nBaseCost);
};