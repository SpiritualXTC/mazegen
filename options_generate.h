#pragma once
/********************************************************************
File: options_generate.h
Author: s3435406
Desc: Command line Options for Generating a Maze
********************************************************************/


#include <iostream>

#include "app.h"
#include "command_args.h"
#include "options.h"
#include "util/random.h"

/*
	Handles the Command for generating the maze
*/
template <class GENERATOR>
class OptionGenerateMaze : public IOptions<App*>
{
public:
	static const int32_t SEED_TIME = -1;


public:
	OptionGenerateMaze() {}
	virtual ~OptionGenerateMaze() {}

	/*
		execute():
	*/
	bool execute(const Command & command, App * app) override
	{
	//	namespace chrono = std::chrono;

		std::cout << "Generate Maze" << std::endl;

		// Set Default Parameters for Maze
		int32_t seed = OptionGenerateMaze::SEED_TIME;
		int32_t width = maze::Maze::DEFAULT_SIZE;
		int32_t height = maze::Maze::DEFAULT_SIZE;

		int param = 0;

		// Too many arguments
		if (command.parameters() > 3)
			return false;

		// Get Seed Argument [1 or 3 parameters]
		// Always the First Parameter
		if (command.parameters() > 0 && command.parameters() != 2)
			seed = stoi(command.argument(param++));

		// Get Dimension Arguments [2 or 3 parameters]
		if (command.parameters() > 1)
		{
			width = stoi(command.argument(param++));
			height = stoi(command.argument(param++));
		}

		// Set the Seed
		uint32_t seedval = 0;

		if (seed == OptionGenerateMaze::SEED_TIME)
			seedval = util::Random::seed();
		else
			seedval = util::Random::seed((uint32_t)seed);

		// Output Info about Generation
		std::cout << " : Dimensions: " << width << "x"
			<< height << std::endl;
		std::cout << " : Seed: " << seedval << std::endl;

		// Create the Generator
		std::shared_ptr<maze::IMazeGenerator> generator
			= std::make_shared<GENERATOR>();

		// Generate
		return app->generate(width, height, generator);
	}
};
