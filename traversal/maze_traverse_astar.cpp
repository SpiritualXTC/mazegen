/********************************************************************
File: maze_traverse_astar.cpp
Author: s3435406
********************************************************************/
#include "maze_traverse_astar.h"

#include <cassert>

using namespace traversal;


/*

*/
MazeTraverseAStar::MazeTraverseAStar()
{

}



/*

*/
MazeTraverseAStar::~MazeTraverseAStar()
{

}


/*
	traverse():
*/
bool MazeTraverseAStar::traverse(int32_t startX, int32_t startY
	, int32_t finishX, int32_t finishY
	, const std::shared_ptr<maze::Maze> maze)
{
	assert(maze);

	_finish.x = finishX;
	_finish.y = finishY;

	// Get Maze Width
	_width = maze->width();
	_height = maze->height();
	//bool found = false;


	// Initialise sCell States
	_cells.reserve(_width * _height);
	
	for (uint32_t i = 0; i < _cells.capacity(); ++i)
	{
		AStarCell cell;
		//cell.queued = false;
		cell.visited = false;
		cell.pathX = -1;
		cell.pathY = -1;
		cell.bestCost = -1;

		_cells.push_back(cell);
	}

	// Push Starting Node
	pushStart(startX, startY, 0);

	// Continue while Nodes are still available :)
	while (!_queue.empty())
	{
		// Get First Node
		const AStarPriority & priority = pop();
		
		// Is this the finsh Node? Set Found Flag
		if (priority.x == finishX && priority.y == finishY)
		{
		//	found = true;

		//	std::cout << "ASTAR: Path is found : " << std::endl;
			break;
		}
		
		// Get Maze Node
		const maze::MazeNode & node = maze->getNode(priority.x, priority.y);

		// Push Adjacent Nodes
		for (const maze::MazeCell & adjacent : node.adjacent)
		{
			// Push Node Onto Queue
			push(priority, adjacent.x, adjacent.y, 1);
		}
	}

	// Build the Path Edges
	buildPath();

	return true;
}


/*
	push():

	Pushes the Start the Next Node
*/
void MazeTraverseAStar::pushStart(int32_t x, int32_t y, int32_t cost)
{
	AStarCell & cell = getCell(x, y);
	cell.bestCost = 0;

	push(x, y, cost);
}


/*
	push():

	Updates the Cell State
*/
void MazeTraverseAStar::push(const AStarPriority & last
	, int32_t x, int32_t y, int32_t cost)
{
	// Set Visited Flag
	AStarCell & cell = getCell(x, y);
	if (cell.visited == true)
		return;
	
	// Calculate Total Cost to get to this Cell
	int32_t totalCost = last.cost + cost;

	// Already has a better option.... 
	if (cell.bestCost != -1 && cell.bestCost < totalCost)
		return;

	// Update Cell
	cell.pathX = last.x;
	cell.pathY = last.y;
	cell.bestCost = totalCost;

	// Push
	push(x, y, totalCost);
}


/*
	push():

	Pushes the Node to the Queue
*/
void MazeTraverseAStar::push(int32_t x, int32_t y, int32_t totalCost)
{
	AStarPriority priority;

	// Calculate Heuristic
	//int32_t heuristic = _heuristic->heuristic(x, y, 
	//	_finish.x, _finish.y);
	priority.x = x;
	priority.y = y;
	priority.cost = totalCost;
	priority.priority = totalCost + heuristic(x, y, 
		_finish.x, _finish.y);

	// Add Priority Value to Queue
	_queue.push(priority);
}



/*
	pop():
*/
const AStarPriority MazeTraverseAStar::pop()
{
	// Get Topmost Priority Value
	AStarPriority priority = _queue.top();

	// Pop Priority Value
	_queue.pop();

	// Get Cell, Set Visited Flag
	AStarCell & cell = getCell(priority.x, priority.y);
	cell.visited = true;


	return priority;
}


/*
	buildPath():

	Builds the path by backtracking from the finish node to the start
*/
void MazeTraverseAStar::buildPath()
{
	// Get Finishing Cell
	AStarCell & cell = getCell(_finish.x, _finish.y);

	// Add Finish Cell
	_path.insert(_path.begin(), _finish);

	// Backtrack to the Starting Cell
	while (cell.pathX != -1 && cell.pathY != -1)
	{
		// Add Cell to the Path
		maze::MazeCell path;
		path.x = cell.pathX;
		path.y = cell.pathY;

		_path.insert(_path.begin(), path);

		// Backtrack
		cell = getCell(cell.pathX, cell.pathY);
	}
}










