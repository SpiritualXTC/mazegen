/********************************************************************
File: maze_export_binary.h
Author: s3435406
Desc: Exports a binary file of the maze
********************************************************************/

#pragma once

#include "../maze/maze_builder.h"


namespace io
{ 
	/*
		Save a Binary File representing the maze
	*/
	class MazeExportBinary : public maze::IMazeExport
	{
	public:
		MazeExportBinary();
		virtual ~MazeExportBinary();

		bool save(const std::string & filename,
			const std::shared_ptr<maze::Maze> maze,
			const std::shared_ptr<maze::MazePath> path) override;
	};
}