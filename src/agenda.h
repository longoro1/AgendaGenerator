#ifndef _AGENDA_H
#define _AGENDA_H

#include <string>
#include <map>

#include "workday.h"
#include "fileparser.h"

using namespace std;

// Redefine a map of workdays as workdaymap
typedef map <string, Workday *> workdaymap;


class Agenda {

private:

	// A Map that holds all of the work days
	workdaymap workdays;

	// Name of this agenda
	string name;

	// Arrays to hold the max working minutes, and max tasks
	int *maxworkmin;
	int *maxtasks;

	/* Adds a particular day to the workdaymap
		_date:: the date that the workday will have
		RETURNS:: pointer to the new workday*/
	Workday *createDay(string _date);

public:
	// Ctor
	Agenda (string _name, int *_maxworkmin, int *_maxtasks);

	// Accessor
	string getName() { return name; }

	/* Attempts to fetch a particular day given the date
		calls createDay if the day isn't found
		_date:: the workday that is needed
		RETURNS:: pointer to the workday*/
	Workday *getDay(string _date);

};

#endif
