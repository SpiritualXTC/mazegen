/********************************************************************
File: console.cpp
Author: s3435406
********************************************************************/

#include "console.h"

#include <iostream>

// Prevent the Console from Closing
// Relevant only to windows :)
#define LOCK_CONSOLE

/* Windows Terminal Lock */
#if defined(_WIN32)
#include <conio.h>

// Uncomment to disable lock
//#undef LOCK_CONSOLE

#else
// Console based Platforms don't need it! 
#undef LOCK_CONSOLE

#endif







/*
	exit():

	Quit Handler : Only needed when run from windows!
	Keeps the terminal window open when the application has
	finished running.
*/
void exit()
{
	// Everything will be out of scope :)

#if defined(LOCK_CONSOLE)
#if defined(_WIN32)
	std::cout << "Press any Key to Continue:" << std::endl;
	_getch();
#else
	std::string in;
	std::cout << "Press Enter to Continue" << std::endl;;
	std::cin >> in;
#endif
#endif
}




/*
	initConsoleLock():


*/
void initConsoleLock()
{
	// Set Exit Handler
	atexit(exit);

	return;
}



/*
	put in main.cpp : main();

	#include "console.h"
	initConsoleLock();
*/
