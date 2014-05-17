#ifndef _WORKDAY_H
#define _WORKDAY_H

#include <string>
#include <vector>
#include <ostream>
#include <iterator>
#include <cmath>

#include "task.h"

using namespace std;

// Redefine a vector of tasks as a task list
typedef vector <task *> tasklist;

/* Define an iterator for the takslist*/
typedef tasklist::iterator taskiterator;

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
	string getDate() const { return date; }
	taskiterator begin() { return tasks.begin(); }
	taskiterator end() { return tasks.end(); }
	
	/* Used to determine how allocated the current workday is
		RETURNS:: percent allocation (<= 1)*/
	float getPercentAlloc() const;

	/*Attempts to add a task to this workday
		t:: pointer to the task to be inserted
		RETURNS:: a list of tasks that need to be relocated*/
	tasklist plottask(task *_t);
	
	// Printer
	friend ostream& operator<<(ostream& os, Workday &w);

};

ostream &operator<<(ostream &os, Workday &w);


#endif
