/********************************************************************
File: maze_generate_recursive.cpp
Author: s3435406
********************************************************************/
#include "maze_generate_recursive.h"

#include <cassert>

#include "../exception.h"
#include "../util/random.h"


using namespace generators;

/*
	Constructor():

	Generates the Maze
*/
MazeRecursiveDivision::MazeRecursiveDivision()
{

}


/*

*/
MazeRecursiveDivision::~MazeRecursiveDivision()
{

}

/*
	generate():

	Generates the Maze
*/
bool MazeRecursiveDivision::generate(int32_t width, int32_t height)
{
	// Set Dimensions
	_width = width;
	_height = height;

	// Start Subdivision Recursion
	subdivide(0, 0, _width - 1, _height - 1);

	return true;
}

/*
	subdivide():

	Subdivide a region of the maze into 2 sections by a "wall"
	Create an edge joining the cells, at a random location 
	along the division/wall
*/
void MazeRecursiveDivision::subdivide(
	int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
	int32_t w = x2 - x1 + 1;
	int32_t h = y2 - y1 + 1;

	// Recursion Escape!
	if (w < 2 || h < 2)
	{
		// Fill in straight line "pathways" as edges
		if (w < 2)
		{
			for (int y = y1; y < y2; ++y)
				addEdge(x1, y, x1, y + 1);
			//	maze->addEdge(x1, y, x1, y + 1);
		}
		else if (h < 2)
		{
			for (int x = x1; x < x2; ++x)
				addEdge(x, y1, x + 1, y1);
			//	maze->addEdge(x, y1, x + 1, y1);
		}

		return;
	}

	int32_t wall = -1;
	int32_t gap = -1;

	// Negative Subdivision
	int32_t xn1 = x1;
	int32_t yn1 = y1;
	int32_t xn2 = x2;
	int32_t yn2 = y2;

	// Positive Subdivision
	int32_t xp1 = x1;
	int32_t yp1 = y1;
	int32_t xp2 = x2;
	int32_t yp2 = y2;


	bool vertical = true;

	// Choose Orientation
	if (w > h)
		vertical = true;
	else if (h > w)
		vertical = false;
	else
	{
	//	vertical = _rng() % 2 == 0;
		vertical = util::Random::generate(2) == 0;
	}

	// Subdivision Parameters
	if (vertical)
	{
		// Divide Vertically
	//	wall = (_rng() % (w - 1)) + 1 + x1;
	//	gap = _rng() % h + y1;
		wall = util::Random::generate(w - 1) + 1 + x1;	// should be generate(w, 1)
		gap = util::Random::generate(h) + y1;

		// Add Edge
		//maze->addEdge(wall - 1, gap, wall, gap);
		addEdge(wall - 1, gap, wall, gap);

		// Alter Subdivisions
		xn2 = wall - 1;
		xp1 = wall;
	}
	else
	{
		// Divide Horizontally
	//	wall = (_rng() % (h - 1)) + 1 + y1;
	//	gap = _rng() % w + x1;
		
		wall = util::Random::generate(h - 1) + 1 + y1;	//should be generate(h, 1)
		gap = util::Random::generate(w) + x1;

		// Add Edge
		//maze->addEdge(gap, wall - 1, gap, wall);
		addEdge(gap, wall - 1, gap, wall);

		// Alter Subdivisions
		yn2 = wall - 1;
		yp1 = wall;
	}

	// Subdivide "negative" side of wall
	subdivide(xn1, yn1, xn2, yn2);

	// Subdivide "positive" side of wall
	subdivide(xp1, yp1, xp2, yp2);

	return;
}

/*
	addEdge():
*/
bool MazeRecursiveDivision::addEdge(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
	maze::MazeEdge edge;
	edge.x1 = x1;
	edge.y1 = y1;
	edge.x2 = x2;
	edge.y2 = y2;

	_edges.push_back(edge);

	return true;
}
