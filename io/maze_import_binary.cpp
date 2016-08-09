/********************************************************************
File: maze_import_binary.cpp
Author: s3435406
********************************************************************/
#include "maze_import_binary.h"

#include <fstream>
#include <sstream>
#include <cstdint>
#include <vector>

#include "../exception.h"


using namespace io;

const int MazeImportBinary::HEADER_ELEMENTS = 3;
const int MazeImportBinary::HEADER_SIZE = 
	MazeImportBinary::HEADER_ELEMENTS * sizeof(int32_t);


/*
	Constructor():

	Imports the maze from the given filename
*/
MazeImportBinary::MazeImportBinary()
{

}


/*

*/
MazeImportBinary::~MazeImportBinary()
{

}



/*
	import():
*/
bool MazeImportBinary::import(const std::string & filename)
{
	/*
	Maze Format:
	<width><height><edge_count><edge[]<x1, y1, x2, y2>>
	*/


	// Open File
	std::ifstream file(filename, std::ifstream::binary);

	// Set Exception State
	file.exceptions(std::ifstream::badbit | std::ifstream::failbit
		| std::ifstream::eofbit);

	// Check for open file
	if (!file.is_open())
	{
		throw MazeException("Error Loading File");
	}

	// Get File Length
	file.seekg(0, file.end);
	int32_t length = (int32_t)file.tellg();
	file.seekg(0, file.beg);

	// Validate File length. 
	// Length must be long enough to contain the "header" data.
	if (length < HEADER_SIZE)
	{
		throw MazeException("Invalid Maze Header");
	}

	// Read Header
	int32_t edges = 0;
	file.read((char*)&_width, sizeof(int32_t));
	file.read((char*)&_height, sizeof(int32_t));
	file.read((char*)&edges, sizeof(int32_t));

	// Validate Dimensions
	if (_width < maze::Maze::MIN_SIZE || _height < maze::Maze::MIN_SIZE)
	{
		throw MazeException("Maze Dimensions are invalid");
	}

	// Validate Edges
	if (edges < 0)
	{
		throw MazeException("Invalid number of edges");
	}

	// Validate File Length, relative to the number of edges.
	if (edges * (int32_t)sizeof(maze::MazeEdge) + HEADER_SIZE != length)
	{
		throw MazeException("Edge count mismatch.");
	}

	// Reserve enough space in the vector to store all the edges 
	// without the need to resize the vector multiple times
	_edges.reserve(edges);

	// Read Edge Data
	for (int i = 0; i < edges; ++i)
	{
		maze::MazeEdge e;

		file.read((char*)&e.x1, sizeof(int32_t));
		file.read((char*)&e.y1, sizeof(int32_t));
		file.read((char*)&e.x2, sizeof(int32_t));
		file.read((char*)&e.y2, sizeof(int32_t));

		// Validate Edge!
		if (e.x1 < 0 || e.y1 < 0
			|| e.x1 >= _width || e.y1 >= _height
			|| e.x2 < 0 || e.y2 < 0
			|| e.x2 >= _width || e.y2 >= _height)
		{
			throw MazeException("Edge Exceeds Dimensions");
		}

		// Add Edge to Vector
		_edges.push_back(e);
	}

	// Validate Edge Count
	// The length of the vector should be
	// exactly the same length as the number read from the header
	// This is unlikely to ever be called now as the file length
	// validation should pick up pretty much any error situation.
	if ((int32_t)_edges.size() != edges)
	{
		std::stringstream excp;
		excp << "Invalid number of edges read. Read = "
			<< _edges.size() << ", expected = "
			<< edges << "." << std::endl;
		throw MazeException(excp.str());
	}

	// Close the File
	file.close();

	return true;
}




#if 0
/*
	generate():

	Generates the Maze, by copying the loaded data to the maze
*/
bool MazeImportBinary::generate(std::shared_ptr<Maze> maze)
{
	// Copy Edges across
	for (auto edge : _edges)
		maze->addEdge(edge);

	return true;
}
#endif

