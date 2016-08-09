/********************************************************************
File: maze_generate_prims_classic.cpp
Author: s3435406
********************************************************************/

#include "maze_generate_prims_classic.h"

#include <iostream>

using namespace generators;


/*

*/
MazeGeneratePrimsClassic::MazeGeneratePrimsClassic()
{

}


/*

*/
MazeGeneratePrimsClassic::~MazeGeneratePrimsClassic()
{

}




/*
	initCells():

	Setup Nodes
*/
void MazeGeneratePrimsClassic::initCells()
{
	// Initialise Cell States

	// Custom Set
	for (int32_t y = 0; y < _height; ++y)
	{
		for (int32_t x = 0; x < _width; ++x)
		{
			// Add Node
			_nodes.addNode({ x, y });
		}
	}
}


/*
	generate():
*/
bool MazeGeneratePrimsClassic::generate(int32_t width, int32_t height)
{
	_width = width;
	_height = height;

	// Init Cells
	initCells();

	// Pick a cell at random!
	int32_t index = getIndex(rand() % _width, rand() % _height);
	//pushCell(_cells.at(index));
	pushCell(_nodes.getNode(index));

	// Push Starting Cell
	//while (!_walls.empty())
	while (!_nodes.empty())
	{
		maze::MazeEdge wall = _nodes.pop();



		// Look at the Walls Cells: Are they both NOT in the maze ??		
		int32_t index1 = getIndex(wall.x1, wall.y1);
		int32_t index2 = getIndex(wall.x2, wall.y2);

		// Determine whether this edge will form a connection or not
		if (! (_nodes.isConnected(index1) 
			&& _nodes.isConnected(index2)))
		{
			// Add to edge list
			_edges.push_back(wall);

			// Push the cell that isn't connected already
			if (! _nodes.isConnected(index1))
				pushCell(_nodes.getNode(index1));
			else if (! _nodes.isConnected(index2))
				pushCell(_nodes.getNode(index2));
		}
	}

	return true;
}



/*

*/
void MazeGeneratePrimsClassic::pushCell(maze::MazeCell & cell)
{
	// Sets the Connected Flag
	_nodes.connect(getIndex(cell.x, cell.y));

	// Add Adjacent Nodes
	pushWall(cell, cell.x - 1, cell.y);
	pushWall(cell, cell.x + 1, cell.y);
	pushWall(cell, cell.x, cell.y - 1);
	pushWall(cell, cell.x, cell.y + 1);
}

/*
	pushWall():

	Push a wall to the set.
*/
void MazeGeneratePrimsClassic::pushWall(maze::MazeCell & cell
	, int32_t x, int32_t y)
{
	// Validate Dimensions
	if (x < 0 || x >= width())
		return;
	if (y < 0 || y >= height())
		return;

	// Add Wall
	_nodes.push({ cell.x, cell.y, x, y });
}
