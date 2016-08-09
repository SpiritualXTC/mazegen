/********************************************************************
File: maze_generate_prims_classic.h
Author: s3435406
Desc: Abstract Prims. (Not in use yet)
********************************************************************/

#pragma once

#include "../maze/maze_builder.h"

namespace generators
{
	/*
		Base class for Prims Algorithms
	*/
	class MazeGeneratorPrims : public maze::IMazeGenerator
	{
	public:
		MazeGeneratorPrims();
		virtual ~MazeGeneratorPrims();

		inline int32_t width() const override 
		{
			return _width; 
		}
		inline int32_t height() const override 
		{
			return _height; 
		}

		const std::vector<maze::MazeEdge> & edges() const override 
		{
			return _edges; 
		}

		bool generate(int32_t width, int32_t height) override;


	private:
		inline int32_t getIndex(int32_t x, int32_t y) 
		{
			return x + y * width(); 
		}

		int32_t _width;
		int32_t _height;

		std::vector<maze::MazeEdge> _edges;	// Closed List of Walls
	};
}