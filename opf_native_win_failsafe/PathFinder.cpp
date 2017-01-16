/*	
Logical descriptor for PathFinder class:
Written by:	Jonas Brown
Date:		08/04-2016
File: 		PathFinder.h::PathFinder.cpp	
*/

#include "PathFinder.h"

int PathFinder::FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, 
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, 
	const int nOutBufferSize, const bool nIncludeDiagonal, const int nNodeBaseCost,
	const bool nNewSnapshot)
{
	//if out-of-bounds on x-axis or out-of-bounds on y-axis or base cost is invalid
	if (nStartX < 0 || nTargetX < 0 || nStartY  < 0 || nTargetY < 0 || nStartX >= nMapWidth || nTargetX >= nMapWidth || 
		nStartY >= nMapHeight || nTargetY >= nMapHeight || nNodeBaseCost < 1) return -1;
	//set the base cost of traversing one point
	Point2D::_BaseCost = nNodeBaseCost;							
	//initialize the map with given parameters
	if (nNewSnapshot || !mGridSnapshot.empty()) 
	{
		//move map width and map height to internal storage
		mMapWidth = nMapWidth;
		mMapHeight = nMapHeight;
		//froeach node array ptr** at 2d array ptr***
		for (int x = 0; x < nMapWidth; ++x)
		{
			std::vector<Node> temp;
			//allocate heap memory for node array ptr**
			mGridSnapshot.push_back(temp);
		}
		//node counter
		int i = 0;
		//foreach node array ptr** at 2d array ptr***
		for (int y = 0; y < nMapHeight; y++)
		{
			//foreach node ptr* at node array ptr**
			for (int x = 0; x < nMapWidth; x++)
			{
				//if using resistance multi; allocate stack memory for nodes and link them 
				//within 2d array and init node resistance
				mGridSnapshot[x].push_back(Node(x, y, i, (pMap[i] > 0), pMap[i]));
				//increment counter
				i++;
			}
		}
	}
	//clear any old data
	mOpen.clear();
	mShortestPath.clear();
	//create a reference to target node from given parameters, and open it
	Node* pTargetNode = &mGridSnapshot[nTargetX][nTargetY];		
	mOpen = { &mGridSnapshot[nStartX][nStartY] };					
	//if starting or target node is non-traversable, terminate
	if (!mOpen.front()->Traversable || !pTargetNode->Traversable) return -1;	
	//adjecent offsets; adjecent offsets size is 8 if diagonals are excluded, else size is 4
	std::vector<std::pair<int, int>> adjecentOffsets = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
	if (nIncludeDiagonal)
	{
		std::vector<std::pair<int, int>> diagonalOffsets = { { 1, 1 }, { 1, -1 }, { -1, 1 }, {-1, -1 } };
		adjecentOffsets.insert(adjecentOffsets.end(), diagonalOffsets.begin(), diagonalOffsets.end());
	}
	int k = 0;
	//while buffer size has not been exceeded
	for (int i = 0; i < nOutBufferSize - 1; i++)
	{
		Node* pCurrentNode = mOpen.front();				//node we are currently checking
		mOpen.pop_front();								//remove it from open list
		pCurrentNode->Closed = true;					//set the current node to closed
		//for each adjecent node
		for (unsigned int i = 0; i < adjecentOffsets.size(); i++)
		{
			//check if adjecent should be updated/initialized 
			char debugcode = fUpdateAdjecentNode(adjecentOffsets[i].first, adjecentOffsets[i].second, pCurrentNode, pTargetNode, &mOpen);
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
		
		k++;
		if (mOpen.empty()) return -1;
	}
	//buffer size exceeded = path is to long
	return -1;
}

unsigned char PathFinder::fUpdateAdjecentNode(const int nOffsetX, const int nOffsetY, Node* pCurrentNode, 
	Node* pTargetNode, std::list<Node*> *pOpen)
{
	//x,y position for adjecent node
	int adjecentX = pCurrentNode->Position.X + nOffsetX;
	int adjecentY = pCurrentNode->Position.Y + nOffsetY;
	//if adjecent node is out-of-bounds
	if (!(adjecentX < mMapWidth && adjecentX >= 0 && adjecentY < mMapHeight && adjecentY >= 0))
	{
		return 0; //adjecent node oob
	}
	//reference node adjecent to current
	Node* pAdjecentNode = &mGridSnapshot[adjecentX][adjecentY];
	//if it is closed and is non-traversable 
	if (pAdjecentNode->Closed || !pAdjecentNode->Traversable)
	{
		return 1; //adjecent node closed or untraversable
	}
	//if adjecent node has a parent
	if (pAdjecentNode->ParentPtr)
	{
		//try update, if returns true, node updated; else not update
		if (pAdjecentNode->Update(&pTargetNode->Position, pCurrentNode))
		{
			return 3; //adjecent node updated
		}
		return 2; //adjecent node not updated
	}
	//else if adjecent node doesn't have a parent; initialize, and check if target found
	if (pAdjecentNode->Initialize(&pTargetNode->Position, pCurrentNode, pOpen))
	{
		pTargetNode->ParentPtr = pCurrentNode;
		return 5; //target node found
	}
	return 4; //target node not found
}