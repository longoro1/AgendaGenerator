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

public: 
	// Ctor
	Workday(string _date);

	// Accessors
	string getDate() { return date; }	
	

	// Member functions --------------------------
	
	/* Used to determine how allocated the current workday is
		_maxMinutes:: max number of minutes for
			 this particular day of the week
		RETURNS:: percent allocation (<= 1)*/
	float getPercentAlloc(const int _maxMinutes);

	/*Attempts to add a task to this workday
		t:: pointer to the task to be inserted
		RETURNS:: a list of tasks that need to be relocated*/
	tasklist plottask(task *_t);
	
};


#endif
