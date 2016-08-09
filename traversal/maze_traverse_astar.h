#pragma once
/********************************************************************
File: maze_traverse_wall_astar.h
Author: s3435406
Desc: Traverse a maze using he A* algorithm
********************************************************************/

#include <cstdint>
#include <vector>
#include <queue>


#include "../maze/maze_builder.h"

#include "heuristic.h"

namespace traversal
{
	/*
	
	*/
	struct AStarPriority
	{
		int32_t x;
		int32_t y;

		int32_t priority;	// Priority Value
		int32_t cost;
	};

	/*
	
	*/
	struct AStarCell
	{
		int32_t bestCost;
		int32_t pathX;
		int32_t pathY;

		bool visited;		// I Have been visited
		//bool queued;		// I am currently queued
	};



	/*
		
	*/
	struct AStarPriorityCost
	{
		bool operator()(const AStarPriority & lhs
			, const AStarPriority & rhs) const
		{
			return lhs.priority > rhs.priority;
		}
	};



	/*
		
	*/
	class MazeTraverseAStar : public maze::IMazeTraverse
	{
	public:
		MazeTraverseAStar();
		virtual ~MazeTraverseAStar();

		bool traverse(int32_t startX, int32_t startY, int32_t finishX,
			int32_t finishY, const std::shared_ptr<maze::Maze> maze) override;


		const std::vector<maze::MazeCell> & path() const override
		{
			return _path; 
		}

	private:
		inline int32_t getIndex(int32_t x, int32_t y) 
		{ 
			return x + y * _width; 
		}

		

		/*
			getCell():

			Gets the Cell at (x, y)
		*/
		inline AStarCell & getCell(int32_t x, int32_t y)
		{
			return _cells[getIndex(x, y)];
		}

		void pushStart(int32_t x, int32_t y, int32_t cost);
		void push(const AStarPriority & last, int32_t x, int32_t y
			, int32_t cost);
		void push(int32_t x, int32_t y, int32_t totalCost);

		void buildPath();


		const AStarPriority pop();


		int32_t _width;
		int32_t _height;
		maze::MazeCell _finish;
	


		//std::shared_ptr<IHeuristic> _heuristic;


		std::vector<AStarCell> _cells;
		std::priority_queue<AStarPriority, 
			std::vector<AStarPriority>, AStarPriorityCost> _queue;
	
		std::vector<maze::MazeCell> _path;	// Final Path
		


		// Heuristic [Temporary Method]
		virtual int32_t heuristic(int32_t x1, int32_t y1
			, int32_t x2, int32_t y2) = 0;
	};
}