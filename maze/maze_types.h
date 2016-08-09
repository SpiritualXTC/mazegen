#pragma once
/********************************************************************
File: maze_types.h
Author: s3435406
Desc: Type definitions common for a maze
********************************************************************/


#include <cstdint>

namespace maze
{
	/*
		Defines an "edge" between 2 cells
	*/
	struct MazeEdge
	{
		int32_t x1;
		int32_t y1;
		int32_t x2;
		int32_t y2;
	};

	/*
		Defines the cell that is a adjacent to another cell.
		Used for traversal
	*/
	struct MazeCell
	{
		int32_t x;
		int32_t y;
	};

	//typedef MazeAdj MazeCell;


	/*
		Defines a Maze Cell / Node
	*/
	struct MazeNode
	{
		int32_t x;
		int32_t y;

		// Can be used for Faster Traversal, than needing to lookup the 
		// edge data from a master list. Not needed for assignment 1 :)
		std::vector<MazeCell> adjacent;
	};
}