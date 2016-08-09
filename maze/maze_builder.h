#pragma once
/********************************************************************
File: maze_builder.h
Author: s3435406
Desc: Maze Builder.
Helpers for generating a maze from an abstract algorithm
********************************************************************/



#include <memory>
#include <cstdint>

#include "maze.h"
#include "maze_path.h"


namespace maze
{
	/*
		File Formats supported by the Maze

		Binary: Load & Save
		SVG: Save Only [Loading is possible but .... yolo]
	*/
	enum class MazeFormat
	{
		Binary,
		SVG,
	};


	/*
		Builds a Maze
	*/
	class IMazeBuilder
	{
	public:
		IMazeBuilder() {}
		virtual ~IMazeBuilder() {}

		virtual const std::vector<MazeEdge> & edges() const = 0;

		virtual int32_t width() const = 0;
		virtual int32_t height() const = 0;
	};

	/*
		Generates a Maze using an algorithm
	*/
	class IMazeGenerator : public IMazeBuilder
	{
	public:
		IMazeGenerator(){}
		virtual ~IMazeGenerator() {}

		virtual bool generate(int32_t width, int32_t height) = 0;
	};

	/*
		Import a Maze from file
	*/
	class IMazeImport : public IMazeBuilder
	{
	public:
		IMazeImport() {}
		virtual ~IMazeImport(){}
		virtual bool import(const std::string & filename) = 0;
	};

	/*
		Common interface for exporting the maze!
	*/
	class IMazeExport
	{
	public:
		IMazeExport() {}
		virtual ~IMazeExport() {}

		virtual bool save(const std::string & filename, 
			const std::shared_ptr<Maze> maze, const std::shared_ptr<MazePath> path) = 0;
	};



	/*
		Common Interface for traversing a maze!
	*/
	class IMazeTraverse
	{
	public:
		IMazeTraverse() {}
		virtual ~IMazeTraverse() {}

		virtual const std::vector<MazeCell> & path() const = 0;

		virtual bool traverse(int32_t startX, int32_t startY, 
			int32_t finishX, int32_t finishY, 
			const std::shared_ptr<Maze> maze) = 0;
	};





	/*
		Acts as common ground between the maze generation
		and creating the maze class for traversal.
	
		NOTE: 
		For Assignment 1, this is more of a helper class
		than one that does anything constructive :)

		This will possibly remain more of a helper class 
		for Assignment 2 :)
	*/
	class MazeBuilder
	{
	public:
		/* Import a maze from file */
		static std::shared_ptr<Maze> import(MazeFormat format, 
			const std::string & filename);

		/* Import a maze from file */
		static std::shared_ptr<Maze> import(std::shared_ptr<IMazeImport> importer,
			const std::string & filename);
	
		/* Save the maze using a known/supported format */
		static bool save(MazeFormat format, const std::string & filename, 
			const std::shared_ptr<Maze> maze, const std::shared_ptr<MazePath> path);

		/* Save the maze using any custom formatter */
		static bool save(std::shared_ptr<IMazeExport> exporter, 
			const std::string & filename, const std::shared_ptr<Maze> maze,
			const std::shared_ptr<MazePath> path);


		/* Generate the maze using any type of generator */
		static std::shared_ptr<Maze> generate(int32_t width, int32_t height,
			std::shared_ptr<IMazeGenerator> generator);

		/* Maze Traversal */
		static std::shared_ptr<MazePath> traverse(int32_t startX, 
			int32_t startY, int32_t finishX, int32_t finishY, 
			std::shared_ptr<Maze> maze, std::shared_ptr<IMazeTraverse> traversal);

	private:
		/* Builds the Maze from the Builder */
		static std::shared_ptr<Maze> build(
			std::shared_ptr<IMazeBuilder> builder);


	private:
		// Can't be instantiated.
		MazeBuilder(){}
		virtual ~MazeBuilder(){}
	};

}