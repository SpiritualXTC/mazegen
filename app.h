#pragma once
/********************************************************************
File: app.h
Author: s3435406
Desc: Application.
********************************************************************/

#include <cstdint>
#include <string>
#include <memory>

#include "maze/maze_builder.h"
#include "maze/maze_path.h"

/*
	Application Class
	Provides a layer of persistance... not much else since the refactor...
*/
class App
{
public:
	App();
	virtual ~App();


	/*
		Generate the Maze
	*/
	bool generate(int32_t width, int32_t height, 
		std::shared_ptr<maze::IMazeGenerator> generator);
	
	/*
		Traverse the Maze
	*/
	bool traverse(std::shared_ptr<maze::IMazeTraverse> traversal);

	/*
		Load a Maze
	*/
	bool load(const std::string & filename);
	

	/*
		Save the Maze
	*/
	bool save(maze::MazeFormat format, const std::string & filename);

private:
	/*
		Clears the Maze & Paths
	*/
	void clear();

	std::shared_ptr<maze::Maze> _maze;
	std::shared_ptr<maze::MazePath> _path;
};