#ifndef _FILEPARSER_H
#define _FILEPARSER_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "task.h"
using namespace std;

/* Processes a given config file. ARRAYS ARE UNALLOCATED BEFORE FUNCTION!!
	_filename:: name of the file
	_maxworkmin:: array of how many minutes are avaliable for use each day
	_maxtasks:: the maximum number of tasks allowed in a day
	RETURNS:: -1 if error, 0 if succeeded*/
int parseConfigFile(string _filename, int *&_maxworkmin, int *&_maxtasks);

/* Genearates a task using a given line from a file
	_subject:: subject associated with that file	
	_fileline:: one line of text in the file
	RETURNS:: pointer to a task*/
task &generateTask(string _subject, string _fileline);

/* Gets the number for the day of the week in accordance with ctime
	_date:: the string for the date
	RETURNS:: ctime day of the week*/
int getDayofWeek (string _date);

/* Shifts a given date by a specific number of days
	_date:: the date in the struct
	_numDays:: how many days to shift (+ or -)
	RETURNS:: the new date*/
string shiftDate(const string _date, const int _numDays);

/*Gets the current date as a string
	RETURNS:: the current date formatted as day, month, year*/
string getDate();



#endif
