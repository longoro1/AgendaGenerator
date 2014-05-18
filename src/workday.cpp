#include "workday.h"


Workday::Workday(string _date, int _maxwork, int _maxtasks)
{
	// Assign the date
	date = _date;
	maxworkmin = _maxwork;
	maxtasks = _maxtasks;
	numWorkMin = 0;
}


float Workday::getPercentAlloc() const
{
	return ((float)numWorkMin / (float)maxworkmin);
}


tasklist *Workday::plottask(task *_t)
{
	tasklist *bumpedtasks = NULL; // List that will be returned


	// See if time is violated
	if ( (_t -> getTime() + numWorkMin) > maxworkmin )
	{
		bumpedtasks = bump (_t); // Bump

		/*if (bumpedtasks == NULL) // Couldn't bump
		{
			// Just shove this task into a list, and return it
			bumpedtasks = new tasklist();
			bumpedtasks -> push_back ( _t);
			return bumpedtasks;
		}*/ return NULL;
	}

	// At this point, guarenteed that there is room for the task, so add it
	numWorkMin += _t -> getTime();
	tasks.push_back(_t);	

	return bumpedtasks;
}

tasklist *Workday::bump(task *t)
{
	// A list of tasks
	tasklist *tlist = new tasklist;

	// The priority of the task
	int priority = t -> getPriority();

	// Will not bump low-priority items
	if (priority == task::MIN_PRIORITY) return NULL;
	
	int posn = 0; // Where we left off in the tasklist
	
	// Tasklist iterators
	taskiterator i_begin = begin();
	taskiterator i_end = end();

	/* Iterate through the list and find lower priority tasks
	found::
		1) add pointer to new list
		2) using the iterator, remove the task from the list
		3) put iterator back at old posn
		4) recurse*/
	while (i_begin != i_end)
	{
		// Steps 1 and 2
		if ( (*i_begin) -> getPriority() > priority)
		{
			tlist -> push_back (*i_begin); // Add to list
			tasks.erase(i_begin); // Remove the task from list

			// Realign pointer
			i_begin = begin();
			i_end = end();
			//advance (i_begin, posn); // #efficency
		}

		// Increase positions
		++i_begin;
		++posn;
	}

	// Nothing found, cleanup
	if (tlist -> size() == 0)
	{
		delete tlist;
		tlist = NULL;
	}

	return tlist;
}

ostream &operator<<(ostream &os, Workday &w)
{
	os << "DAY " << w.date << endl;
	os << "Time : (" << w.numWorkMin << "/" << w.maxworkmin 
		<< ")\tPercent Allocation = " 
		<< (w.getPercentAlloc() * 100) 
		<< "%" << endl;

	// Print the tasks
	taskiterator i_begin = w.begin();
	taskiterator i_end = w.end();

	while (i_begin != i_end)
	{
		os << "------------------------------------------------------";
		os << endl;
		os << *(*i_begin);
		i_begin++;
	}
	
	return os; 
}
