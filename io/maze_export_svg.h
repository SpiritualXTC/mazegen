#pragma once
/********************************************************************
File: maze_export_svg.h
Author: s3435406
Desc: Export a Graphical Representation of the maze using
the Scalable Vector Graphics (SVG) format
********************************************************************/

#include <sstream>

#include "../maze/maze_builder.h"

/*
	Save a visual representation of the maze
*/
namespace io
{ 
	class MazeExportSVG : public maze::IMazeExport
	{
	public:
		MazeExportSVG();
		virtual ~MazeExportSVG();

		bool save(const std::string & filename, 
			const std::shared_ptr<maze::Maze> maze,
			const std::shared_ptr<maze::MazePath> path) override;

	private:
		void svgWalls(std::stringstream & stream, 
			const std::shared_ptr<maze::Maze> maze);
		
		void svgEdges(std::stringstream & stream,
			const std::shared_ptr<maze::Maze> maze);

		void svgPath(std::stringstream & stream, 
			const std::shared_ptr<maze::Maze> maze,
			const std::shared_ptr<maze::MazePath> path);

		void svgEdge(std::stringstream & stream,
			const std::string & color, float strokeWidth,
			int32_t x1, int32_t y1, int32_t x2, int32_t y2,
			int32_t mazeWidth, int32_t mazeHeight);

		void svgLine(std::stringstream & stream,
			const std::string & color, float strokeWidth,
			float x1, float y1, float x2, float y2);

	};
}
