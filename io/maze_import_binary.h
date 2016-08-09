#pragma once
/********************************************************************
File: maze_import_binary.h
Author: s3435406
Desc: Imports a Maze
********************************************************************/

#include <string>

#include <vector>

#include "../maze/maze_builder.h"

namespace io
{
	/*
		Imports a maze from a binary file
	*/
	class MazeImportBinary : public maze::IMazeImport
	{
	public:
		static const int HEADER_ELEMENTS;
		static const int HEADER_SIZE;

	public:
		MazeImportBinary();
		virtual ~MazeImportBinary();

		int32_t width() const override { return _width; }
		int32_t height() const override { return _height; }

		//bool generate(std::shared_ptr<Maze> maze) override;// {return true; }
		bool import(const std::string & filename) override;

		const std::vector<maze::MazeEdge> & edges() const override
		{
			return _edges; 
		}

	private:

	//	std::string _filename;

		std::vector<maze::MazeEdge> _edges;

		int32_t _width = 0;
		int32_t _height = 0;
	};
}


