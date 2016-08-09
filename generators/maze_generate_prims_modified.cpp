/********************************************************************
File: maze_generate_prims_modified.cpp
Author: s3435406
********************************************************************/
#include "maze_generate_prims_modified.h"

#include <iostream>

using namespace generators;

/*

*/
MazeGeneratePrimsModified::MazeGeneratePrimsModified()
{

}

/*

*/
MazeGeneratePrimsModified::~MazeGeneratePrimsModified()
{

}



/*
	initCells():s
*/
void MazeGeneratePrimsModified::initCells()
{
	// Initialise Node States
	for (int32_t y = 0; y < _height; ++y)
	{
		for (int32_t x = 0; x < _width; ++x)
		{
			PrimNode node;
			node.visited = false;
			node.x = x;
			node.y = y;

			// Add Node
			_graph.addNode(node);
		}
	}
}



/*
	generate():
*/
bool MazeGeneratePrimsModified::generate(int32_t width, int32_t height)
{
	// Set Maze Dimensions
	_width = width;
	_height = height;

	// Initialise the Cells
	initCells();


	// Pick starting cell at random!
	int32_t startIndex = getIndex(rand() % _width, rand() % _height);
	PrimNode start = _graph.getNode(startIndex);
	pushCell(start);

	// While cells still exist in the open list
	while (! _graph.empty())
	{
		maze::MazeCell cell = _graph.pop();
		PrimNode node = _graph.getNode(getIndex(cell.x, cell.y));

		// Choose an Edge that connects to the maze
		if (node.adjacency.size() >= 1)
		{
			int32_t adjIndex = rand() % node.adjacency.size();

			maze::MazeEdge edge;
			edge.x1 = cell.x;
			edge.y1 = cell.y;
			edge.x2 = node.adjacency[adjIndex].x;
			edge.y2 = node.adjacency[adjIndex].y;

			_edges.push_back(edge);
		}

		// Push all child nodes
		pushCell(node);
	}

	return true;
}


/*

*/
void MazeGeneratePrimsModified::pushCell(PrimNode & node)
{
	// Flag as Connected
	_graph.connect(getIndex(node.x, node.y));

	pushCell(node, node.x - 1, node.y);
	pushCell(node, node.x + 1, node.y);
	pushCell(node, node.x, node.y - 1);
	pushCell(node, node.x, node.y + 1);
}


/*

*/
void MazeGeneratePrimsModified::pushCell(PrimNode & node
	, int32_t x, int32_t y)
{
	// Validate Dimensions
	if (x < 0 || x >= width())
		return;
	if (y < 0 || y >= height())
		return;

	// Get Node
	PrimNode & data = _graph.getNode(getIndex(x, y));

	// Add Adjacency to previous node which is already in the maze
	data.adjacency.push_back({ node.x, node.y });

	// Verify Flag : Don't need to visit the same node twice
	if (data.visited == true)
		return;

	// Set Flag
	data.visited = true;
	
	// Push the cell
	_graph.push({x, y});
}










