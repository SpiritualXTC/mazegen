/********************************************************************
File: maze_path.cpp
Author: s3435406
********************************************************************/
#include "maze_path.h"

#include <iostream>

using namespace maze;

/*

*/
MazePath::MazePath()
{

}


/*

*/
MazePath::~MazePath()
{

}


/*
	addPath():

	Adds the next node in the path
*/
bool MazePath::addPath(const MazeCell & cell)
{
	// Get the last node in the path
	int32_t last = _path.size() - 1;

	// Isn't the first node in the list
	if (last > 0)
	{
		MazeCell & lastNode = _path[last];

		// Validate the Node: It MUST be 
		// adjacent to the top-level node
		if ((labs(lastNode.x - cell.x) + 
			labs(lastNode.y - cell.y)) != 1)
			return false;
	}

	// Add the Next Node in the Path
	_path.push_back(cell);

	return true;
}


/*
	printPath():

	Prints path to console
*/
void MazePath::printPath()
{
	// Print the Path
	std::cout << "Path Finding:" << std::endl;

	std::cout << "START" << std::endl;
	for (auto cell : _path)
	{
		std::cout << "PATH: " << cell.x << ", " 
			<< cell.y << std::endl;
	}
	std::cout << "FINISH" << std::endl;
}