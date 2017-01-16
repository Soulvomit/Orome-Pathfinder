/*	
Interface descriptor for Node class:
Written by:	Jonas Brown
Date:		08/04-2016
File: 		Node.h
*/

//Headers:
#pragma once
#include "Point2D.h"
#include <list>
#include <deque>

class Node
{
private:
	//Internal Members:
	int mID;						//identifier of node, corrosponds to place on grid
	unsigned char mResistance;				//resistance multiplier of traversing through this node
	Point2D mPosition;				//ptr to this nodes 2d point on a grid
	bool mTraversable;				//set if node is non-traversable
	bool mClosed = false;			//set if node has been checked
	Node *pParent = NULL;			//ptr to next node in the best path, from this node to start
	int mGCost = 0;					//cost of this nodes current path to start
	int mHCost = 0;					//cost of manhattan distance to target
	int mFCost = 0;					//g + h = combined cost

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
	char fSortedInsert(std::list<Node*> *pOpen);

public:
	//Constructor:
	Node(int X, int Y, int ID, bool traversable = true, unsigned char resistance = 1)
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
	__declspec (property (put = Traversable, get = GetTraversable)) bool Traversable;
	void SetTraversable(bool value) { mTraversable = value; }
	bool GetTraversable() const { return mTraversable; }
	__declspec (property (put = SetParent, get = GetParent)) Node *ParentPtr;
	void SetParent(Node *pValue) { pParent = pValue; }
	Node *GetParent() const { return pParent; }
	__declspec (property (put = SetPosition, get = GetPosition)) Point2D Position;
	void SetPosition(Point2D mValue) { mPosition = mValue; }
	Point2D GetPosition() const { return mPosition; }
	__declspec (property (put = SetID, get = GetID)) int ID;
	void SetID(int value) { mID = value; }
	int GetID() const { return mID; }
	__declspec (property (put = SetResistance, get = GetResistance)) unsigned char Resistance;
	void SetResistance(unsigned char value) { mResistance = value; }
	unsigned char GetResistance() const { return mResistance; }
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
	void Traceback(std::deque<Node*> *pShortestPath);
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
	bool Initialize(Point2D *pTargetPoint, Node *pCurrentNode, std::list<Node*> *pOpen);	
	/* --------------------------------------------------------------------------------------
	** Updates g, h and f costs and parent for this node, if f costs are lower then before.
	** Uses g costs as tie-breaker. Does not update if g costs are tied.
	>> Params:
	--->	pTargetPoint	=	Ptr to target point.
	--->	pCurrentNode	=	Ptr potential new parent for this node.
	<< Returns:
	<---	false			=	No update was necessary.
	<---	true			=	Node was updated.	
	--------------------------------------------------------------------------------------- */
	bool Update(Point2D *pTargetPoint, Node *pCurrentNode);
};