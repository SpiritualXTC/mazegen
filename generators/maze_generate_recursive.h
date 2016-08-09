/********************************************************************
File: maze_generate_recursive.h
Author: s3435406
Desc: Generate Maze using Recursive Division algorithm
********************************************************************/

#pragma once

#include <vector>

#include "../maze/maze_builder.h"


namespace generators
{
	/*
		Recusrive Division
	*/
	class MazeRecursiveDivision : public maze::IMazeGenerator
	{
	public:
		MazeRecursiveDivision();
		virtual ~MazeRecursiveDivision();


		int32_t width() const override { return _width; }
		int32_t height() const override { return _height; }

		const std::vector<maze::MazeEdge> & edges() const override 
		{ 
			return _edges; 
		}

		bool generate(int32_t width, int32_t height) override;

	private:

		void subdivide(int32_t x1, int32_t y1, int32_t x2, int32_t y2);

		bool addEdge(int32_t x1, int32_t y1, int32_t x2, int32_t y2);


		int32_t _width = 0;
		int32_t _height = 0;

		std::vector<maze::MazeEdge> _edges;
	};
}