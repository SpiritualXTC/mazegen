#pragma once
/********************************************************************
File: maze_traverse_tremaux.h
Author: s3435406
Desc: Traverse a maze using the Tremaux algorithm
********************************************************************/
#include <vector>
#include <stack>

#include "../maze/maze_builder.h"

namespace traversal
{
	/*
	
	*/
	class MazeTraversalTremaux : public maze::IMazeTraverse
	{
	private:
		enum TremauxPath
		{
			UNVISITED = 0,
			MARKED = 1,
			TRAVELLED = 2,
		};

		enum Tremaux
		{
			DEADEND = 0,	// This is a dead end
			PATH = 1,		// There is a path
			JUNCTION = 2,	// This is a junction

			//
			// The algorithm can treat paths & junctions identically
			//
		};

		typedef int32_t TremauxCell;


		bool traverse(int32_t startX, int32_t startY
			, int32_t finishX, int32_t finishY
			, const std::shared_ptr<maze::Maze> maze) override;


		const std::vector<maze::MazeCell> & path() const override 
		{
			return _path; 
		}

	public:
		MazeTraversalTremaux();
		virtual ~MazeTraversalTremaux();


	private:
		inline int32_t getIndex(int32_t x, int32_t y) 
		{ 
			return x + y * _width; 
		}

		inline TremauxCell & getCell(int32_t x, int32_t y)
		{
			return _cells[getIndex(x, y)];
		}

		void pop();
		void push(int32_t x, int32_t y);

		int32_t _width = 0;
		int32_t _height = 0;


		std::vector<TremauxCell> _cells;	// Storage for each cell.

		std::stack<maze::MazeCell> _stack;		// Intermidiate path	

		std::vector<maze::MazeCell> _path;		// Path to follow
	};
}