/********************************************************************
File: maze_traverse_tremaux.h
Author: s3435406
********************************************************************/
#include "maze_traversal_tremaux.h"

using namespace traversal;

/*

*/
MazeTraversalTremaux::MazeTraversalTremaux()
{

}

/*

*/
MazeTraversalTremaux::~MazeTraversalTremaux()
{

}


/*
	traverse():
*/
bool MazeTraversalTremaux::traverse(int32_t startX, int32_t startY
	, int32_t finishX, int32_t finishY
	, const std::shared_ptr<maze::Maze> maze)
{
//	std::cout << "TREMAUX: START" << std::endl;

	// Set Dimensions
	_width = maze->width();
	_height = maze->height();

	// Create Tremaux Cell Map
	_cells.reserve(maze->width() * maze->height());
	for (uint32_t i = 0; i < _cells.capacity(); ++i)
		_cells.push_back(0);
	
	// Push Opening Cell
	push(startX, startY);

	// Loop while things remain in the stack
	while (! _stack.empty())
	{
		// Set Previous Cell
		//previous = cell;

		// Get the topmost Cell
		maze::MazeCell cell = _stack.top();
		
		// Get the Cell Data
		const maze::MazeNode & node = maze->getNode(cell.x, cell.y);

		// Finished ?
		if (node.x == finishX && node.y == finishY)
			break;
		
		// Determine Available Pathways
		std::vector<maze::MazeCell> paths;

		for (const maze::MazeCell & adj : node.adjacent)
		{
			TremauxCell & tremauxAdj = getCell(adj.x, adj.y);

			if (tremauxAdj == UNVISITED)
				paths.push_back(adj);
		}

		// Decide what to do from here.
		if (paths.size() == DEADEND)
		{
			// Is this a dead-end ?? Requires 1 adjacent cell

			// This is a dead-end.
			// Nowhere new to travel. 
			// Backtracking
			// Pop the Cell

			pop();
		}
		else
		{
			// Is this a Junction ?? Requires 3 or more adjacent 
			// cells, that haven't already been travelled : Push Cell

			// Is this a pathway ?? Requires 2 adjacent cells 
			// that haven't already been travelled : Push Cell

			// Choose which path go down
			int32_t index = rand() % paths.size();

			push(paths[index].x, paths[index].y);
		}
	}

	// Path not found
	if (_stack.empty())
	{
		return false;
	}

	// Backtrack along the path...
	while (! _stack.empty())
	{
		// Get topmost cell
		maze::MazeCell & cell = _stack.top();

		// Add to path list
		_path.insert(_path.begin(), cell);

		// Pop Cell
		_stack.pop();
	}

	return true;
}

/*
	push():
*/
void MazeTraversalTremaux::push(int32_t x, int32_t y)
{
	// Increment
	TremauxCell & tremaux = getCell(x, y);
	tremaux++;

	// Create Cell
	maze::MazeCell cell;
	cell.x = x;
	cell.y = y;

	_stack.push(cell);
}

/*
	pop():
*/
void MazeTraversalTremaux::pop()
{
	// Get Cell
	maze::MazeCell & cell = _stack.top();
	
	// Increments
	TremauxCell & tremaux = getCell(cell.x, cell.y);
	tremaux++;

	// Pop
	_stack.pop();
}
