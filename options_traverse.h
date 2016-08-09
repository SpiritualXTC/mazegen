#pragma once
/********************************************************************
File: options_traverse.h
Author: s3435406
Desc: Command line Options for Traversing a Maze
********************************************************************/

#include "app.h"
#include "command_args.h"
#include "options.h"

/*

*/
template <class TRAVERSAL>
class OptionTraverseMaze : public IOptions<App*>
{
public:
	/*
		execute():
	*/
	bool execute(const Command & command, App * app) override
	{
		// Doesn't take any arguments.... ??

		// Too many arguments
		if (command.parameters() > 0)
			return false;

		// Create the Traverse
		std::shared_ptr<maze::IMazeTraverse> traversal
			= std::make_shared<TRAVERSAL>();

		return app->traverse(traversal);
	}
};