/********************************************************************
File: app.cpp
Author: s3435406
********************************************************************/
#include "app.h"

#include <cassert>
#include <iostream>

#include "maze/maze_builder.h"
#include "generators/maze_generate_recursive.h"


/*

*/
App::App()
{

}


/*

*/
App::~App()
{

}


/*
	Clears the Maze & Path
*/
void App::clear()
{
	_maze = nullptr;
	_path = nullptr;
}

/*
	generateMaze():

	Generates the Maze

	Move timing to the builder
*/
bool App::generate(int32_t width, int32_t height, 
	std::shared_ptr<maze::IMazeGenerator> generator)
{
	assert(generator);

	// Clear Current Maze
	clear();

	// Generate a Maze
	//_maze = MazeBuilder::generate(builder);
	_maze = maze::MazeBuilder::generate(width, height, generator);

	// Temp Traversal
//	auto traverse = std::make_shared<MazeTraverseWallFollow>();
//	MazeBuilder::traverse(0, 0, _maze->width() - 1, _maze->height() - 1, _maze, traverse);

	return !! _maze;
}


/*
	loadMaze():

	Load a Maze
*/
bool App::load(const std::string & filename)
{
	// Clear Current Maze
	clear();

	// Load / Import Maze
	_maze = maze::MazeBuilder::import(maze::MazeFormat::Binary, filename);

	// Return result
	return !!_maze;
}


/*
	saveMaze():

	Saves the Maze
*/
bool App::save(maze::MazeFormat format, const std::string & filename)
{
	// Validate Maze
	if (!_maze)
		return false;

	// Save Maze
	return maze::MazeBuilder::save(format, filename, _maze, _path);
}


/*
	traverse():

	Traverse the Maze
*/
bool App::traverse(std::shared_ptr<maze::IMazeTraverse> traversal)
{
	if (!_maze)
		return false;

	// Traverse Maze
	// Upper Left Corner to Lower Right Corner
	int32_t x2 = _maze->width() - 1;
	int32_t y2 = _maze->height() - 1;

	// Traverse
	_path = maze::MazeBuilder::traverse(0, 0, x2, y2, _maze, traversal);

	// Traversable ?
	// Currently Path is always nullptr
	// (_path != nullptr) ? true : false;
	return true;
}





