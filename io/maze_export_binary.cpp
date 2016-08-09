/********************************************************************
File: maze_export_binary.h
Author: s3435406
********************************************************************/
#include "maze_export_binary.h"

#include <cassert>
#include <fstream>

#include "../exception.h"

using namespace io;

/*

*/
MazeExportBinary::MazeExportBinary()
{

}


/*

*/
MazeExportBinary::~MazeExportBinary()
{

}


/*
	save():
	
	Save the File!
*/
bool MazeExportBinary::save(const std::string & filename, 
	const std::shared_ptr<maze::Maze> maze,
	const std::shared_ptr<maze::MazePath> path)
{
	assert(maze);

	// Open the File
	std::ofstream file(filename, std::ofstream::binary);

	if (! file.is_open())
	{
		throw MazeException("Unable to open file");
	}
	
	// Output Header
	int32_t width = maze->width();
	int32_t height = maze->height();


	auto edges = maze->edges();
	int32_t edge_count = edges.size();

	// Output Maze Header
	file.write((char*)&width, sizeof(int32_t));
	file.write((char*)&height, sizeof(int32_t));
	file.write((char*)&edge_count, sizeof(int32_t));

	// Output Edges
	for (auto & edge : edges)
	{
		file.write((char*)&edge.x1, sizeof(int32_t));
		file.write((char*)&edge.y1, sizeof(int32_t));
		file.write((char*)&edge.x2, sizeof(int32_t));
		file.write((char*)&edge.y2, sizeof(int32_t));
	}

	// Close the file
	file.close();

	return true;
}