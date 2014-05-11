#ifndef _WORKDAY_H
#define _WORKDAY_H

#include <string>
#include <vector>

#include "task.h"

using namespace std;

// Redefine a vector of tasks as a task list
typedef vector <task *> tasklist;

class Workday {

private:
	// List of tasks that belong to this workday
	tasklist tasks;

	// The date that this workday represents
	string date;

	// Amount of time that is spent working (in minutes)
	int numWorkMin;

	// Max work in minutes that can be done this day
	int maxworkmin;

	// Maximum number of tasks that can be performed this day
	int maxtasks;

public: 
	// Ctor
	Workday(string _date, int _maxwork, int _maxtasks);

	// Accessors
	string getDate() { return date; }	
	
	/* Used to determine how allocated the current workday is
		RETURNS:: percent allocation (<= 1)*/
	float getPercentAlloc();

	/*Attempts to add a task to this workday
		t:: pointer to the task to be inserted
		RETURNS:: a list of tasks that need to be relocated*/
	tasklist plottask(task *_t);
	
};


#endif
