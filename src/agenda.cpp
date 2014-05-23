#include "agenda.h"

Agenda::Agenda (string _name, int *_maxworkmin, int *_maxtasks)
{
	name = _name;
	maxworkmin = _maxworkmin;
	maxtasks = _maxtasks;

}
Agenda::~Agenda()
{
	// Implement me!!
}

void Agenda::plot_task (task *_t)
{
	tasklist *tlist = new tasklist();
	tlist -> push_back (_t);

	bool succeeded = plottask_helper(tlist);

	if (!succeeded) cout << "All tasks do not fit in agenda" << endl;

}

void Agenda::plot_tasklist (tasklist *_tlist)
{
	bool succeeded = plottask_helper(_tlist);

	if (!succeeded) cout << "All tasks do not fit in agenda" << endl;

}

bool Agenda::plottask_helper(tasklist *&_tasks)
{
	taskiterator i_begin = _tasks -> begin();
	taskiterator i_end = _tasks -> end();	

	while (i_begin != i_end)
	{
		// Get the task
		task *t = *i_begin;
		i_begin++;
		stringstream ss;
		ss << "Agenda::plottask_helper(" << t -> getName() << " " << t -> getTime() << ")" << endl;
		LOG(ss.str());

		// Plot it
		Workday *w = getDay(t -> getDate(), true);
		tasklist *returnedvalues = w -> plottask(t);

		if (returnedvalues != NULL)
		{
			bool succeeded = 
				plottask_helper(returnedvalues, t -> getDate());
			if (!succeeded) return false;
		}
	} 

	return true;
}

bool Agenda::plottask_helper(tasklist *&_tasks, string _startdate)
{	
	string today = getDate();
	string day = _startdate;

	if (_tasks -> size () == 0) return true;

	stringstream ss;
	ss << "Plotting " << _tasks -> size() << " tasks on days betwen today (" 
		<< today << ") and end day(" << day << ")" << endl
		<< "Is day >= today?? " 
		<< ((day >= today) ? "True" : "False");
	LOG(ss.str());

	while (day >= today) // Loop over every day from that date to today
	{
		stringstream ss;
		ss << "\tPlotting " << _tasks -> size() << " tasks on " 
			<< day << endl;
		LOG(ss.str());

		// Shift by -1
		day = shiftDate(day, -1);
		
		taskiterator i_begin = _tasks -> begin();
		taskiterator i_end = _tasks -> end();		

		while (i_begin != i_end) // Try to insert every task in the list
		{
			// Plot it 
			Workday *w = getDay(day, true);
			tasklist *returnedvalues = 
				w -> plottask(*i_begin);

			// CASE:: Any tasks returned
			if (returnedvalues != NULL)
			{
				bool succeeded = 
					plottask_helper(returnedvalues, day);
				if (!succeeded)
				{
					return false;
				}

				// Succeeded, realign pointers
				_tasks -> erase(i_begin);
				i_begin = _tasks -> begin();
				i_begin--;
				i_end = _tasks -> end();		
		
			}

			i_begin++; // Advance iterator
			if (i_begin == i_end) return true; // Finished
		}
	}

	return false;
}


Workday *Agenda::createDay(string _date, workdayiterator _posn)
{
	// Find out the workday
	int workdayindex = getDayofWeek(_date);

	// Initiate a new day
	Workday *day = new Workday (_date, maxworkmin[workdayindex], 
			maxtasks[workdayindex]);

	// Check empty list
	if (workdays.size() == 0) workdays.push_back(day);
	else workdays.insert (_posn, day);

	// Get the min and max date
	workdayiterator i_begin = begin();
	workdayiterator i_end = end();
	minday = (*i_begin) -> getDate();
	i_end--;
	maxday = (*i_end) -> getDate();


	stringstream ss;
	ss << "Agenda::createDay(" << _date << " max min:" << maxworkmin[workdayindex] << ")" << endl; ///////////////////////////////////////////////
	LOG(ss.str());

	// Return the pointer
	return day;
}


Workday *Agenda::getDay(string _date, bool _canAdd)
{
	// Try to find the value
	workdayiterator i_begin = begin();
	workdayiterator i_end = end();

	while (i_begin != i_end)
	{
		// Try to match
		if ((*i_begin) -> getDate() == _date) return *i_begin; // Match

		// Stop before the date is greater
		if ((*i_begin) -> getDate() > _date) break;

		i_begin++;
	}
	
	// Not allowed to add the workday
	if (!_canAdd) return NULL; 

	stringstream ss;
	ss << "Agenda::getDay(" << _date << ")" << endl; ///////////////////////////////////////////////
	LOG(ss.str());

	// Workday doesn't exist, create it
	return createDay(_date, i_begin);
}

ostream &operator<<(ostream &os, Agenda &a)
{
	// Print the heade
	os << "****************************************************************";
	os << endl;
	os << a.name << endl;
	os << "First Day of Work:: " << a.minday << endl;
	os << "Last Day of Work:: " << a.maxday << endl;
	os << "****************************************************************";
	os << endl << endl;

	// Print off the workdays
	workdayiterator i_begin = a.begin();
	workdayiterator i_end = a.end();

	while (i_begin != i_end)
	{
		os << "///////////////////////////////////////////////////////";
		os << endl;
		os << *(*i_begin);// << endl;
		i_begin++;
	}

	return os;
}
