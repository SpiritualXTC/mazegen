/********************************************************************
File: maze_generate_prims.cpp
Author: s3435406
********************************************************************/

#include "maze_generate_prims.h"

using namespace generators;

/*

*/
MazeGeneratorPrims::MazeGeneratorPrims()
{

}

/*

*/
MazeGeneratorPrims::~MazeGeneratorPrims()
{

}


/*
	
*/
bool MazeGeneratorPrims::generate(int32_t width, int32_t height)
{
	// Set Dimensions
	_width = width;
	_height = height;

	return true;
}