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

	// LOG
	stringstream ss;
	ss << "Workday::plot_task(" << _t -> getName() << " " << _t -> getTime() << ") into " << date << endl;
	LOG (ss.str());
	
	// First, check if task exists already
	if (findMatch(*_t))
	{
		// Just shove this task into a list, and return it
		bumpedtasks = new tasklist();
		bumpedtasks -> push_back ( _t);
		return bumpedtasks;
	}


	// See if time is violated
	if ( (_t -> getTime() + numWorkMin) > maxworkmin )
	{	
		bumpedtasks = bump (_t); // Bump

		// LOG
		stringstream ss3;
		ss3 << "Bumped " << (bumpedtasks == NULL ? 0 : bumpedtasks -> size()) << " tasks." << endl;
		LOG (ss3.str());

		if (bumpedtasks == NULL) // Couldn't bump
		{
			// Just shove this task into a list, and return it
			bumpedtasks = new tasklist();
			bumpedtasks -> push_back ( _t);
			return bumpedtasks;
		}

		// Check if are not actually able to insert the task
		if ( (_t -> getTime() + numWorkMin) > maxworkmin )
		{
			// Add back the tasks
			for (int i = 0; i < bumpedtasks -> size(); i++)
			{
				tasks.push_back((*bumpedtasks)[i]);
				numWorkMin += ((*bumpedtasks)[i]) -> getTime();
			}
		
			delete bumpedtasks;

			// Just shove this task into a list, and return it
			bumpedtasks = new tasklist();
			bumpedtasks -> push_back ( _t);
			return bumpedtasks;			

		}
	}

	// LOG
	stringstream ss2;
	ss2 << "Workday::plot_task Added the task" << endl;
	LOG (ss2.str());

	// At this point, guarenteed that there is room for the task, so add it
	numWorkMin += _t -> getTime();
	tasks.push_back(_t);	
	
	return bumpedtasks;
}

tasklist *Workday::bump(task *t)
{
	// LOG
	stringstream ss;
	ss << "Workday::bump(" << t -> getName() << " " << t -> getTime() << ")";
	LOG (ss.str());

	// A list of tasks
	tasklist *tlist = new tasklist;

	// The priority of the task
	int priority = t -> getPriority();

	// Will not bump low-priority items
	if (priority == task::MIN_PRIORITY) return NULL;
	
	/* Iterate through the list and find lower priority tasks
	found::
		1) add pointer to new list
		2) using the iterator, remove the task from the list
			A) if got necessary time, exit
		3) realign iterators
		4) recurse*/

	for (int i = task::MIN_PRIORITY; i > priority; i--)
	{
	
		// Tasklist iterators
		taskiterator i_begin = begin();
		taskiterator i_end = end();

		while (i_begin != i_end)
		{
			// Steps 1 and 2
			if ( (*i_begin) -> getPriority()  == i)
			{
				tlist -> push_back (*i_begin); // Add to list
				numWorkMin -= 
					(*i_begin) -> getTime(); // Adjust time
				tasks.erase(i_begin); // Remove task from list

				// Realign pointer
				i_begin = begin();
				i_end = end();

				// Check if have sufficent time gain
				if ( (t -> getTime() + numWorkMin) <= maxworkmin )
					return tlist;

			}
			else
			{
				// Increase positions
				++i_begin;
			}
			
		}
	}

	// Nothing found, cleanup
	if (tlist -> size() == 0)
	{
		delete tlist;
		tlist = NULL;
	}

	return tlist;
}


bool Workday::findMatch (const task &_t)
{
	taskiterator i_begin = begin();
	taskiterator i_end = end();

	while (i_begin != i_end)
	{
		if (*(*i_begin) == _t) return true;		

		i_begin++;
	}

	return false;
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
