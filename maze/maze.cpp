/********************************************************************
File: maze.cpp
Author: s3435406
********************************************************************/

#include "maze.h"

#include <cassert>
#include <algorithm>

using namespace maze;

/*

*/
Maze::Maze(int32_t width, int32_t height)
	: _width(width)
	, _height(height)
{
	assert(_width != 0 && _height != 0);

	_width = width;
	_height = height;

	// Size the Vector
	_nodes.reserve(_width * _height);

	// Create Nodes
	for (int32_t y = 0; y < _height; ++y)
	{
		for (int32_t x = 0; x < _width; ++x)
		{
			MazeNode n;
			n.x = x;
			n.y = y;

			_nodes.push_back(n);
		}
	}
}

/*

*/
Maze::~Maze()
{

}


/*
	addEdge():

	Adds an edge between too nodes.
*/
bool Maze::addEdge(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
	// Construct Edge
	MazeEdge edge;
	edge.x1 = x1;
	edge.x2 = x2;
	edge.y1 = y1;
	edge.y2 = y2;

	// Add to Edge List
	return addEdge(edge);
}


/*
	addEdge():

	Adds an edge between to nodes
*/
bool Maze::addEdge(const MazeEdge & edge)
{
	// Can't be adjacent to itself
	if (edge.x1 == edge.x2 && edge.y1 == edge.y2)
		return false;

	// Check Node Against Dimensions
	if (edge.x1 < 0 || edge.x1 >= width() 
		|| edge.y1 < 0 || edge.y1 >= height())
		return false;

	// Check Adjacent Node Against Dimensions
	if (edge.x2 < 0 || edge.x2 >= width() 
		|| edge.y2 < 0 || edge.y2 >= height())
		return false;

	// Has to be adjcacent to a direct neighbor
	if ((labs(edge.x1 - edge.x2) + labs(edge.y1 - edge.y2)) != 1)
		return false;

	// Get the Node!
	MazeNode & n1 = _nodes[edge.x1 + edge.y1 * width()];
	MazeNode & n2 = _nodes[edge.x2 + edge.y2 * width()];

	// Is this Edge Already Present ?
	

	// Add Edge
	_edges.push_back(edge);

	// Add Adjacency for both Nodes
	addAdjacency(n1, edge.x2, edge.y2);
	addAdjacency(n2, edge.x1, edge.y1);

	return true;
}


/*
	addAdjacency():
*/
bool Maze::addAdjacency(MazeNode & node, int32_t adjX, int32_t adjY)
{
	// Has to be adjcacent to a direct neighbor
	if ( (labs(node.x - adjX) + labs(node.y - adjY)) != 1)
		return false;

	// Can't already be in the adjaceny list
	auto it = std::find_if(node.adjacent.begin(), node.adjacent.end(),
		[adjX, adjY]
		(const MazeCell & adj)
		{
			return adj.x == adjX && adj.y == adjY;
		});

	if (it != node.adjacent.end())
		return false;

	// Add Adjacent Node
	MazeCell adj;
	adj.x = adjX;
	adj.y = adjY;

	node.adjacent.push_back(adj);

	return true;
}

