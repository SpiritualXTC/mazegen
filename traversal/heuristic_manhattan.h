#pragma once

/********************************************************************
File: heuristic_manhattan.h
Author: s3435406
Desc: Classes for Manhattan Heuristic Distance
********************************************************************/

#include <cmath>

#include "heuristic.h"
#include "maze_traverse_astar.h"

namespace traversal
{
#if 0
	/*
		Policy Based Heuristc
	*/
	class ManhattanHeuristic
	{
	public:
		ManhattanHeuristic() {}
		virtual ~ManhattanHeuristic() {}

		/*
			Calculate Manhattan Distance
		*/
		inline int32_t heuristic(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
		{
			return labs(x2 - x1) + labs(y2 - y1);
		}
	};
#endif


	/*
		TEMP
	*/
	class MazeTraversalAStarManhattan : public MazeTraverseAStar
	{
	public:
		int32_t heuristic(int32_t x1, int32_t y1, int32_t x2, int32_t y2) override
		{
			return labs(x2 - x1) + labs(y2 - y1);
		}
	};

}
