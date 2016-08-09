#pragma once
/********************************************************************
File: options_traverse.h
Author: s3435406
Desc: Command line Options for Saving/Importing a maze
********************************************************************/


#include "options.h"

/*
	Handles the Command for Loading a Maze
*/
class OptionLoadMaze : public IOptions<App*>
{
public:
	OptionLoadMaze() {}
	virtual ~OptionLoadMaze() {}

	/*
		execute():
	*/
	bool execute(const Command & command, App * app) override
	{
		std::cout << "Load Maze" << std::endl;

		if (command.parameters() != 1)
			return false;

		std::cout << " : Filename: " << command.argument(0)
			<< std::endl;

		return app->load(command.argument(0));
	}
};


/*
	Handles the Command for Saving a Maze
*/
class OptionSaveMaze : public IOptions<App*>
{
public:
	OptionSaveMaze(maze::MazeFormat format)
		: _format(format)
	{

	}
	virtual ~OptionSaveMaze() {}

	/*
		execute():
	*/
	bool execute(const Command & command, App * app) override
	{
		std::cout << "Save Maze" << std::endl;

		if (command.parameters() != 1)
			return false;

		std::cout << " : Filename: " << command.argument(0)
			<< std::endl;
		std::cout << " : Format: " << (_format == maze::MazeFormat::Binary ?
			"Binary" : "SVG") << std::endl;

		return app->save(_format, command.argument(0));
	}
private:
	maze::MazeFormat _format;
};