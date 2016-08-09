#pragma once

/********************************************************************
File: heuristic_euclidean.h
Author: s3435406
Desc: Classes for Euclidean Heuristic Distance
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
	class EuclideanHeuristic
	{
	public:
		EuclideanHeuristic() {}
		virtual ~EuclideanHeuristic() {}

		/*
			Calculate Euclidean Distance
		*/
		inline int32_t heuristic(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
		{
			int32_t dx = x2 - x1;
			int32_t dy = y2 - y1;

			return sqrtl(dx * dx + dy * dy);
		}
	};
#endif

	/*
		TEMP
	*/
	class MazeTraversalAStarEuclidean : public MazeTraverseAStar
	{
	public:
		int32_t heuristic(int32_t x1, int32_t y1, int32_t x2, int32_t y2) override
		{
			int32_t dx = x2 - x1;
			int32_t dy = y2 - y1;

			
			return (int32_t)sqrt(dx * dx + dy * dy);
		}
	};

}
