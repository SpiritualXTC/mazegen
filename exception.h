#pragma once
/********************************************************************
File: exception.h
Author: s3435406
Desc: Exception handling.
********************************************************************/

#include <exception>

/*
	Basic Exception Class
*/
class MazeException : public std::exception
{
public:
	MazeException() : MazeException("Unknown Exception in Maze")
	{

	}

	MazeException(const std::string & message) 
		: _msg(message)
	{

	}

	virtual const char * what() const throw() override
	{
		return _msg.c_str();
	}

private:
	std::string _msg;
};

