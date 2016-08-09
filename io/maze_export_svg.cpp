/********************************************************************
File: maze_export_svg.cpp
Author: s3435406
********************************************************************/

#include "maze_export_svg.h"

#include <cassert>
#include <fstream>

#include "../exception.h"


using namespace io;

// Flag for drawing only maze edges.
// (as per Assignment 1 requirements)
// Unset to draw the maze properly :)
#define DRAW_MAZE_EDGES_ONLY
#undef DRAW_MAZE_EDGES_ONLY

/*

*/
MazeExportSVG::MazeExportSVG()
{

}

/*

*/
MazeExportSVG::~MazeExportSVG()
{

}

/*
	save():

	Save the Maze as an SVG file.
*/
bool MazeExportSVG::save(const std::string & filename, 
	const std::shared_ptr<maze::Maze> maze,
	const std::shared_ptr<maze::MazePath> path)
{
	assert(maze);

	// Build the XML File Stream
	std::ofstream file(filename);

	if (! file.is_open())
	{
		throw MazeException("Unable to open file");
	}

	std::stringstream stream;

	// Output SVG Header
	stream << "<svg viewBox='0 0 1 1' width='500' height='500' "
		<< "xmlns='http://www.w3.org/2000/svg'>" << std::endl;
	stream << "<rect width='1' height='1' style='fill: black' />" 
		<< std::endl;

	// Output Walls
	svgWalls(stream, maze);

	// Output Edges
	svgEdges(stream, maze);

	// Output the Path
	if (path != nullptr)
		svgPath(stream, maze, path);

	// Close SVG
	stream << "</svg>" << std::endl;

	// Send to File
	file << stream.str();

	// Close the File
	file.close();

	return true;
}


/*
	svgWalls():
*/
void MazeExportSVG::svgWalls(std::stringstream & stream,
	const std::shared_ptr<maze::Maze> maze)
{

	// Get Node List
	auto nodes = maze->nodes();

	// Loop through Nodes
	for (const auto & n : nodes)
	{
		bool left = false;
		bool bottom = false;

		// Determine what edges needs to be draw in relation to this node.
		for (const maze::MazeCell & adj : n.adjacent)
		{
			// Check for Right Path
			if (n.x + 1 == adj.x && n.y == adj.y)
				left = true;

			// Check for Bottom Path
			if (n.y + 1 == adj.y && n.x == adj.x)
				bottom = true;
		}

		// Output Walls to the Left of this edge
		if (!left)
		{
			float x = (n.x + 1) / (float)maze->width();
			float y1 = (n.y) / (float)maze->height();
			float y2 = (n.y + 1) / (float)maze->height();

			// Output the Line
			svgLine(stream, "blue", 0.01f, x, y1, x, y2);
		}

		// Output Walls at the Bottom of this edge.
		if (!bottom)
		{
			float x1 = (n.x) / (float)maze->width();
			float x2 = (n.x + 1) / (float)maze->width();

			float y = (n.y + 1) / (float)maze->height();

			// Output Line
			svgLine(stream, "blue", 0.01f, x1, y, x2, y);
		}
	}
}

/*
	svgEdges():

	Draw the Cell Edges / Adjacency
*/
void MazeExportSVG::svgEdges(std::stringstream & stream,
	const std::shared_ptr<maze::Maze> maze)
{
	// Get Edge List
	auto edges = maze->edges();

	// Output Each Edge
	for (const auto & e : edges)
	{
		svgEdge(stream, "white", 0.005f, e.x1, e.y1, e.x2, e.y2
			, maze->width(), maze->height());
	}
}


/*
	svgPath():

	Draw the Path taken to the Goal
*/
void MazeExportSVG::svgPath(std::stringstream & stream,
	const std::shared_ptr<maze::Maze> maze,
	const std::shared_ptr<maze::MazePath> path)
{
	assert(path);

	// Get Path
	auto cells = path->path();

	// Validate: Not enough cells to display path
	if (cells.size() <= 1)
		return;

	// Select first cell
	auto start = cells.begin();

	// Iterate through path, exclude the first
	for (auto next = cells.begin() + 1; next < cells.end(); ++next)
	{
		// Draw Line from start to next
		svgEdge(stream, "red", 0.01f, start->x, start->y, next->x, next->y
			, maze->width(), maze->height());

		// Update Start
		start = next;
	}

}


/*

*/
void MazeExportSVG::svgEdge(std::stringstream & stream,
	const std::string & color, float strokeWidth,
	int32_t x1, int32_t y1, int32_t x2, int32_t y2,
	int32_t mazeWidth, int32_t mazeHeight)
{
	float nx = x1 / (float)mazeWidth + (0.5f / mazeWidth);
	float ny = y1 / (float)mazeHeight + (0.5f / mazeHeight);

	// Adjacent Node Position
	float ax = nx;
	float ay = ny;

	// Add In Offset Correctly
	if (x1 == x2)
		ay = y2 / (float)mazeHeight + (0.5f / mazeHeight);
	else if (y1 == y2)
		ax = x2 / (float)mazeWidth + (0.5f / mazeWidth);
	else
		return;

	// Output Line
	svgLine(stream, color, strokeWidth, nx, ny, ax, ay);
}




/*
	svgLine():

	Add a line to the stream
*/
void MazeExportSVG::svgLine(std::stringstream & stream,
	const std::string & color, float strokeWidth,
	float x1, float y1, float x2, float y2)
{
	stream << "<line ";
	stream << "stroke = '" << color << "' ";
	stream << "stroke-width='" << strokeWidth << "' ";
	stream << "x1='" << x1 << "' ";
	stream << "y1='" << y1 << "' ";
	stream << "x2='" << x2 << "' ";
	stream << "y2='" << y2 << "'/>";
	stream << std::endl;
}