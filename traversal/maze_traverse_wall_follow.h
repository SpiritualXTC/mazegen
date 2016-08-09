#pragma once
/********************************************************************
File: maze_traverse_wall_follow.h
Author: s3435406
Desc: Traverse a maze using the wall following algorithm
********************************************************************/

#include <vector>

#include "../maze/maze_builder.h"


namespace traversal
{
	/*
		Traverses a maze using the Left-Turn rule
	*/
	class MazeTraverseWallFollow : public maze::IMazeTraverse
	{
	public:
		static const int32_t ADJACENCY_NOT_FOUND = -1;

		MazeTraverseWallFollow();
		virtual ~MazeTraverseWallFollow();

		/*
			path():

			Get the path
		*/
		const std::vector<maze::MazeCell> & path() const override 
		{
			return _path;
		}


		bool traverse(int32_t startX, int32_t startY
			, int32_t finishX, int32_t finishY
			, const std::shared_ptr<maze::Maze> maze) override;

	private:
		bool selectAdjacent(const maze::MazeNode & node, 
			int32_t mazeWidth, maze::MazeCell & outAdj);

		std::vector<bool> _visited;
		std::vector<maze::MazeCell> _path;
	};
}