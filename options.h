#pragma once
/********************************************************************
File: options.h
Author: s3435406
Desc: Interface for Executing Command Line Arguments
********************************************************************/



/*
	Interface for executing a command
*/
template <class T>
class IOptions
{
public:
	IOptions() {}
	virtual ~IOptions() {}

	virtual bool execute(const Command & command, T p) = 0;
};