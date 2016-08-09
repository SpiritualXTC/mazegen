/********************************************************************
File: maze_builder.cpp
Author: s3435406
********************************************************************/
#include "maze_builder.h"

#include <cassert>
#include <iostream>

#include "../exception.h"

#include "../io/maze_import_binary.h"
#include "../io/maze_export_binary.h"
#include "../io/maze_export_svg.h"

#include "../util/timer.h"

using namespace maze;

/*
	import():
		
	Import Helper
*/
std::shared_ptr<Maze> MazeBuilder::import(MazeFormat format
	, const std::string & filename)
{
	if (format == MazeFormat::Binary)
	{
		return import(std::make_shared<io::MazeImportBinary>()
			, filename);
	}

	return nullptr;
}


/*
	import():

	Importer
*/
std::shared_ptr<Maze> MazeBuilder::import(
	std::shared_ptr<IMazeImport> importer,
	const std::string & filename)
{
	assert(importer);

	// Import
	if (! importer->import(filename))
		return nullptr;

	return build(importer);
}


/*
	build():

	Build & returns the Maze
*/
std::shared_ptr<Maze> MazeBuilder::build(
	std::shared_ptr<IMazeBuilder> builder)
{
	// Create Instance of the Maze
	std::shared_ptr<Maze> maze = std::make_shared<Maze>(builder->width(),
		builder->height());

	// Copy Edges to Maze
	const std::vector<MazeEdge> edges = builder->edges();

	for (const MazeEdge edge : edges)
		maze->addEdge(edge);

	return maze;
}


/*
	generate():
*/
std::shared_ptr<Maze> MazeBuilder::generate(int32_t width, int32_t height,
	std::shared_ptr<IMazeGenerator> generator)
{
	assert(generator);

	if (width < Maze::MIN_SIZE || height < Maze::MIN_SIZE)
	{
		throw MazeException("Invalid Maze Dimensions");
	}


	util::Timer timer;
	
	timer.time();

	// Generate the Maze
	if (! generator->generate(width, height))
		return nullptr;

	float time = timer.time();
	std::cout << "Generation Time: " << time << " ms" << std::endl;

	return build(generator);
}




/*
	traverse():

	Traverse the maze
*/
std::shared_ptr<MazePath> MazeBuilder::traverse(
	int32_t startX, int32_t startY, int32_t finishX, int32_t finishY,
	const std::shared_ptr<Maze> maze, 
	std::shared_ptr<IMazeTraverse> traversal)
{
	assert(maze);
	assert(traversal);

	// Create resulting path
	std::shared_ptr<MazePath> path = std::make_shared<MazePath>();

	// Start Timer
	util::Timer timer;
	timer.time();

	// Traverse
	bool result = traversal->traverse(startX, startY, finishX, finishY, maze);
	
	// End Timer
	float time = timer.time();
	std::cout << "Pathfinding Time: " << time << " ms" << std::endl;


	// Output No Path
	if (! result)
	{
		std::cout << "No Path Found" << std::endl;
		return nullptr;
	}

	auto cells = traversal->path();

	


	// Build the Path
	for (auto cell : cells)
	{
		path->addPath(cell);
	}
	//path->printPath();

	return path;
}


/*
	save():

	Export the maze using the supported formats
	This can be part of App
*/
bool MazeBuilder::save(MazeFormat format, const std::string & filename, 
	const std::shared_ptr<Maze> maze, const std::shared_ptr<MazePath> path)
{
	if (format == MazeFormat::Binary)
	{
		return save(std::make_shared<io::MazeExportBinary>(),
			filename, maze, path);
	}
	else if (format == MazeFormat::SVG)
	{
		return save(std::make_shared<io::MazeExportSVG>(), 
			filename, maze, path);
	}
	return false;
}


/*
	save():

	Export the Maze using any format
*/
bool MazeBuilder::save(std::shared_ptr<IMazeExport> exporter, 
	const std::string & filename, const std::shared_ptr<Maze> maze,
	const std::shared_ptr<MazePath> path)
{
	assert(exporter);

	// Start Timer
	util::Timer timer;
	timer.time();


	bool b = exporter->save(filename, maze, path);

	// End Timer
	float time = timer.time();
	std::cout << "Export Time: " << time << " ms" << std::endl;


	return b;
}


