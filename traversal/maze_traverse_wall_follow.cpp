/********************************************************************
File: maze_traverse_wall_follow.cpp
Author: s3435406
********************************************************************/
#include "maze_traverse_wall_follow.h"

#include <stack>
#include <vector>


using namespace traversal;


/*

*/
MazeTraverseWallFollow::MazeTraverseWallFollow()
{

}


/*

*/
MazeTraverseWallFollow::~MazeTraverseWallFollow()
{

}


/*
	traverse():
	
	Traverse the maze by following the left most wall!
*/
bool MazeTraverseWallFollow::traverse(int32_t startX, int32_t startY
	, int32_t finishX, int32_t finishY
	, const std::shared_ptr<maze::Maze> maze)
{
	// Follow Me :)
	std::stack<maze::MazeCell> stack;

	// Create Visited Map
	_visited.reserve(maze->width() * maze->height());
	for (uint32_t i = 0; i < _visited.capacity(); ++i)
		_visited.push_back(false);
		
	// Push Starting Node
	maze::MazeCell start;
	start.x = startX;
	start.y = startY;
	stack.push(start);

	// Set Visited Flag
	_visited[start.x + start.y * maze->width()] = true;

	// Hug the wall to the left!
	while (! stack.empty())
	{
		const maze::MazeCell & top = stack.top();

		// Get Reference to the Node
		const maze::MazeNode & node = maze->getNode(top.x, top.y);
		
		// At the End ?
		if (top.x == finishX && top.y == finishY)
			break;

		// Select the "Left" Node
		maze::MazeCell adjacent;
		if (selectAdjacent(node, maze->width(), adjacent) == true)
		{
			// Set Visited Flag
			_visited[adjacent.x + adjacent.y * maze->width()] = true;

			// Push Adjacent Nodes		
			// Can travel somewhere i haven't been before! 
			
			// Push it!
			stack.push(adjacent);
		}
		else
		{
			// Backtracking.......... I dun know where to go :(
			// So Lost

			// Pop Last Node
			stack.pop();
		}
	}


	// Determine Path
	if (stack.empty() == true)
		return false;
	

	// Setup the path
	while (!stack.empty())
	{
		const maze::MazeCell & cell = stack.top();

		// Insert Cell at the Start
		_path.insert(_path.begin(), cell);

		stack.pop();
	}

	return true;
}


/*
	selectAdjacent():

	Does Naive selection of the path that keeps the wall to the left
*/
bool MazeTraverseWallFollow::selectAdjacent(const maze::MazeNode & node
	, int32_t mazeWidth, maze::MazeCell & nodeOut)
{
	// Basic Always turn left most

	enum DIR
	{
		LEFT = 0,
		UP = 1,
		RIGHT = 2,
		DOWN = 3,
		UNKNOWN = 4,
	};

	DIR direction = UNKNOWN;

	// Loop through cells
	for (const maze::MazeCell & adj : node.adjacent)
	{
		// Has the Adjacent Node Been Visited Yet?
		if (_visited[adj.x + adj.y * mazeWidth] == true)
		{
			continue;
		}

		// Look for Left/West ?
		if (direction > LEFT 
			&& node.x - 1 == adj.x && node.y == adj.y)
		{
			direction = LEFT;
			nodeOut = adj;
		}

		// Look for Up/North ?
		if (direction > UP 
			&& node.x == adj.x && node.y - 1 == adj.y)
		{
			direction = UP;
			nodeOut = adj;
		}

			// Look for Right/East ?
		if (direction > RIGHT 
			&& node.x + 1== adj.x && node.y == adj.y)
		{
			direction = RIGHT;
			nodeOut = adj;
		}

		// Look for Down/Bottom ?
		if (direction > DOWN 
			&& node.x == adj.x && node.y + 1 == adj.y)
		{
			direction = DOWN;
			nodeOut = adj;
		}
	}

	return direction != UNKNOWN;
}

