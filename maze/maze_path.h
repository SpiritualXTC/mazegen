#pragma once
/********************************************************************
File: maze_path.h
Author: s3435406
Desc: Timer class for benchmarking
********************************************************************/

#include <cstdint>
#include <vector>

#include "maze_types.h"


namespace maze
{
	/*
		Stores a path that follows a maze.
	*/
	class MazePath
	{
	public:
		MazePath();
		virtual ~MazePath();


		bool addPath(const MazeCell & cell);

		const std::vector<MazeCell> & path() const { return _path; }

		void printPath();

	private:
		std::vector<MazeCell> _path;
	};
}