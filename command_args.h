#pragma once
/********************************************************************
File: command_args.h
Author: s3435406
Desc: Parses Command Line Arguments

TODO: (or just use boost...)
Add Validation.
	- Min/Max number of arguments
	- Valid Commands only. Throw exception on invalid commands
********************************************************************/
#include <vector>
#include <string>

/*
	Parameters for a single command passed in via hte command line
*/
class Command
{
public:
	Command(int argc, char ** argv);
	virtual ~Command();

	// Get Command Name
	const std::string & command() const 
	{ 
		return _command; 
	}

	// Get the Argument
	const std::string & argument(int index) const 
	{ 
		return _arguments[index]; 
	}

	// Get Parameter Count
	int parameters() const
	{
		return _arguments.size();
	}

private:
	std::string _command;
	std::vector<std::string> _arguments;
};


/*
	All the parameters passed in via the command line
*/
class ProgramOptions
{
public:
	typedef std::vector<Command>::iterator iterator;
	typedef std::vector<Command>::const_iterator const_iterator;

public:
	ProgramOptions(int argc, char ** argv);
	virtual ~ProgramOptions();

	iterator begin() {return _commands.begin();}
	iterator end() { return _commands.end(); }

	const_iterator cbegin() { return _commands.cbegin(); }
	const_iterator cend() { return _commands.cend(); }

private:
	std::vector<Command> _commands;

};