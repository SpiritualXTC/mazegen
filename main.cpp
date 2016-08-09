/********************************************************************
File: main.cpp
Author: s3435406
********************************************************************/
#include <string>
#include <iostream>
#include <chrono>
#include <unordered_map>

#include "app.h"
#include "command_args.h"
#include "options.h"
#include "options_generate.h"
#include "options_io.h"
#include "options_traverse.h"

#include "generators/maze_generate_recursive.h"
#include "generators/maze_generate_prims_classic.h"
#include "generators/maze_generate_prims_modified.h"
#include "traversal/maze_traverse_wall_follow.h"
#include "traversal/maze_traverse_astar.h"
#include "traversal/maze_traversal_tremaux.h"

// FIX ME
#include "traversal/heuristic_euclidean.h"
#include "traversal/heuristic_manhattan.h"


// Shorten type names to fit 80 character
// restriction
typedef std::shared_ptr<IOptions<App*>> IOptionPtr;
typedef std::unordered_map<std::string, IOptionPtr> OptionMap;



/*
	printUsage():

	Prints usage about teh command line.
*/
void printUsage()
{
	std::cout << "Command Line Arguments: " << std::endl;

	std::cout << std::endl << "Generating:" << std::endl;
	std::cout << "--gr [<seed>] [<width>] [<height>]" << std::endl;
	std::cout << "\tGenerate Map using the Recursive Division Algorithm";
	std::cout << std::endl;

	std::cout << "--gp [<seed>] [<width>] [<height>]" << std::endl;
	std::cout << "\tGenerate Map using Prim's Classic Algorithm";
	std::cout << std::endl;

	std::cout << "--gpm [<seed>] [<width>] [<height>]" << std::endl;
	std::cout << "\tGenerate Map using Prims Modified Algorithm";
	std::cout << std::endl;

	std::cout << std::endl << "Generation Parameters" << std::endl;
	std::cout << "[<seed>] - Optional. Defaults the seed based on time";
	std::cout << std::endl;

	std::cout << "[<width>] - Optional. Defaults width to " 
		<< maze::Maze::DEFAULT_SIZE << std::endl;
	
	std::cout << "[<height>] - Optional. Defaults Heigh to " 
		<< maze::Maze::DEFAULT_SIZE << std::endl;

	std::cout << std::endl << "Generation Format" << std::endl;
	std::cout << "<seed>" << std::endl;
	std::cout << "<width> <height>" << std::endl;
	std::cout << "<seed> <width> <height>" << std::endl;




	std::cout << std::endl << "Traversal:" << std::endl;
	std::cout << "--pw" << std::endl;
	std::cout << "\tTraverse using a Wall Follower" << std::endl;
	
	std::cout << "--pt" << std::endl;
	std::cout << "\tTraverse using Tremaux Algorithm" << std::endl;
	
	std::cout << "--pm" << std::endl;
	std::cout << "\tTraverse using A*. Heuristic is Manhattan Distance";
	std::cout << std::endl;

	std::cout << "--pe" << std::endl;
	std::cout << "\tTraverse using A*. heuristic is Euclidean Distance";
	std::cout << std::endl;


	std::cout << std::endl << "Loading:" << std::endl;
	std::cout << "--lb <filename>" << std::endl;
	std::cout << "\tLoad a binary maze" << std::endl;
	
	std::cout << std::endl << "Saving:" << std::endl;
	std::cout << "--sb <filename>" << std::endl;
	std::cout << "\tSave a binary maze" << std::endl;
	std::cout << "--sv <filename>" << std::endl;
	std::cout << "\tSave the maze as an SVG Image" << std::endl;
}












/*
	main():
	
	Entry Point
*/
int main(int argc, char ** argv)
{
	// Parse Command Line Arguments
	ProgramOptions po(argc, argv);
	
	// Create Program Options Map
	// This would be nicer in a more "classy" environment :P
	// Alongside some instant validation when the command line args
	// are parsed. Rather than while they are being interpreted.

	OptionMap _options;

	//_options["--g"] = std::make_shared<GenMaze>();
	_options["--gr"] = std::make_shared<
		OptionGenerateMaze<generators::MazeRecursiveDivision>>();
	_options["--gp"] = std::make_shared<
		OptionGenerateMaze<generators::MazeGeneratePrimsClassic>>();
	_options["--gpm"] = std::make_shared<
		OptionGenerateMaze<generators::MazeGeneratePrimsModified>>();

	_options["--pw"] = std::make_shared<
		OptionTraverseMaze<traversal::MazeTraverseWallFollow>>();
	_options["--pt"] = std::make_shared<
		OptionTraverseMaze<traversal::MazeTraversalTremaux>>();			
	_options["--pm"] = std::make_shared<
		OptionTraverseMaze<traversal::MazeTraversalAStarManhattan>>();	
	_options["--pe"] = std::make_shared<
		OptionTraverseMaze<traversal::MazeTraversalAStarEuclidean>>();

	_options["--lb"] = std::make_shared<OptionLoadMaze>();
	_options["--sb"] = std::make_shared<
		OptionSaveMaze>(maze::MazeFormat::Binary);
	_options["--sv"] = std::make_shared<
		OptionSaveMaze>(maze::MazeFormat::SVG);

	// Create the App
	App app;

	// Loop through Program Options
	for (auto cmd : po)
	{
#if 0
		// Debug: Output the Command and it's parameters
		std::cout << cmd.command;
		for (auto arg : cmd.arguments)
			std::cout << " " << arg;
		std::cout << std::endl;
#endif

		// Find the option to execute.
		auto exec = _options.find(cmd.command());

		// Was the option Found? And it's valid?
		if (exec != _options.end() && exec->second)
		{
			try
			{
				// Execute Option
				bool result = exec->second->execute(cmd, &app);
				if (!result)
				{
					std::cerr << "Failed to Execute Command" 
						<< std::endl;
					return EXIT_FAILURE;
				}
			}
			catch (std::exception & e)
			{
				std::cerr << "Exception Occured:" << std::endl;
				std::cerr << e.what() << std::endl;
				return EXIT_FAILURE;
			}
		}
		else
		{
			// Not Found. Failure!
			std::cerr << "Argument not found!" << std::endl;

			// Print Usage
			printUsage();

			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}