#ifndef _SHELL_H
#define _SHELL_H

#include <iostream>
#include <sstream>
#include <ctime>

#include "fileparser.h"

using namespace std;

// General constants
const int HELP = 0;
const int EXIT = 8;

// Prints the shell header
void printheader();

// Prints the help menu
void printhelp();

// Prints the shell menu
void printmenu();

/* Actual shell / menu
	RETURNS:: choice made by user*/
int shell();

#endif
