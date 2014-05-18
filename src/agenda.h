#ifndef _AGENDA_H
#define _AGENDA_H

#include <string>
#include <list>
#include <ostream>
#include <iterator>

#include "workday.h"
#include "fileparser.h"
#include "utilities.h"

using namespace std;

/* Define a list of workdays as workdaylist */
typedef list <Workday *> workdaylist;

/* Define the iterator */
typedef workdaylist::iterator workdayiterator;

class Agenda {

private:

	// A Map that holds all of the work days
	workdaylist workdays;

	// Name of this agenda
	string name;

	// Arrays to hold the max working minutes, and max tasks
	int *maxworkmin;
	int *maxtasks;

	/* Adds a particular day to the workdaymap
		_date:: the date that the workday will have
		_posn:: where to put the new date
		RETURNS:: pointer to the new workday*/
	Workday *createDay(string _date, workdayiterator _posn);

	// Minimum and maximum dates in the agenda
	string minday, maxday;


	/* Attempts to plot a list of tasks and modifies the local list
		_tasks:: list of tasks to plot
		RETURNS:: true if all tasks were plotted correctly*/
	bool plottask_helper(tasklist *&_tasks);

	/* Attempts to plot a list of tasks and modifies the local list
		_tasks:: list of tasks to plot
		_startdate:: Forces plotting to start 1 Day before this date
		RETURNS:: true if all tasks were plotted correctly*/
	bool plottask_helper(tasklist *&_tasks, string _startdate);

public:
	// Ctor
	Agenda (string _name, int *_maxworkmin, int *_maxtasks);
	
	// Dtor
	~Agenda();

	// Accessor
	string getName() const { return name; }
	workdayiterator begin() { return workdays.begin(); }
	workdayiterator end() { return workdays.end(); }

	/* Attempts to fetch a particular day given the date
		calls createDay if the day isn't found
		_date:: the workday that is needed
		_canAdd:: whether or not to add the day if not found
		RETURNS:: pointer to the workday (or NULL)*/
	Workday *getDay(string _date, bool _canAdd);

	/* Attempts to plot the task in the workday list
		_t:: the task to plot*/
	void plot_task (task *_t);

	/* Attempts to plot the list of tasks in the workday list
		_tlist:: the list of tasks to plot*/
	void plot_tasklist (tasklist *_tlist);

	// Printer
	friend ostream& operator<<(ostream& os, Agenda &a);

};

ostream &operator<<(ostream &os, Agenda &a);

#endif
