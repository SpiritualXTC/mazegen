/********************************************************************
File: maze_generate_prims_classic.h
Author: s3435406
Desc: Generate a maze using Prims Classic Algorithm
********************************************************************/
#pragma once

#include <vector>

#include "../maze/maze_builder.h"

#include "graph.h"

namespace generators
{

	/*
		Modifed version of prims algorthm
	*/
	class MazeGeneratePrimsModified : public maze::IMazeGenerator
	{
		/*
			Defines a nice in the graph
		*/
		struct PrimNode
		{
			bool visited;
			
			int32_t x;
			int32_t y;

			
			std::vector<maze::MazeCell> adjacency;
		};

	public:
		MazeGeneratePrimsModified();
		virtual ~MazeGeneratePrimsModified();

		int32_t width() const override { return _width; }
		int32_t height() const override { return _height; }

		const std::vector<maze::MazeEdge> & edges() const override
		{ 
			return _edges; 
		}

		bool generate(int32_t width, int32_t height) override;

	private:
		inline int32_t getIndex(int32_t x, int32_t y) 
		{
			return x + y * _width; 
		}


		void initCells();
		void pushCell(PrimNode & node);
		void pushCell(PrimNode & node, int32_t x, int32_t y);

		int32_t _width = 0;
		int32_t _height = 0;

		std::vector<maze::MazeEdge> _edges;	// Closed List of Walls

		PrimSet<PrimNode, maze::MazeCell> _graph;
	};

}