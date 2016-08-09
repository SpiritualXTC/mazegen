/********************************************************************
File: command_args.cpp
Author: s3435406
********************************************************************/

#include "command_args.h"

/*
	Constructor():

	Extract the command, and it's arguments.
*/
Command::Command(int argc, char ** argv)
{
	bool command_found = false;
	char ** pargv = argv;

	// Loop through arguments until their is none remaining.
	while (pargv < argv + argc)
	{
		std::string argument = *pargv++;

		// Look for the command prefix
		if (argument.find("--") == 0)
		{
			// Command hasn't been assigned yet.
			if (! command_found)
			{
				// Command Name
				_command = argument;
				command_found = true;
			}
			else
			{
				// Next Command.
				break;
			}
		}
		else
		{
			// Should really be checking whether 
			// command_found is false and failing

			// Add Parameter to lists
			_arguments.push_back(argument);
		}
	}
}

/*

*/
Command::~Command()
{

}



/*
	Constructor():

	Parses the Command Line Arguments as Program Options
*/
ProgramOptions::ProgramOptions(int argc, char ** argv)
{
	char ** pargs = argv;
	int args_rem = argc;

	// Ignore the First Argument [It's the Executable]
	pargs++;
	args_rem--;

	// Loop through arguments until they're is none remaining.
	while (pargs < argv + argc)
	{
		int params = 0;

		// Get Command!
		Command command(args_rem, pargs);

		// Add Command
		_commands.push_back(command);

		// Set Parameter Delta (Arguments + Command)
		params += command.parameters() + 1;
		
		// Update for next pass
		pargs += params;
		args_rem -= params;
	}
}



/*

*/
ProgramOptions::~ProgramOptions()
{

}







