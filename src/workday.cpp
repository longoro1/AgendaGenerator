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


tasklist Workday::plottask(task *_t)
{
	tasklist toReplot;

	// For now, just add the day
	numWorkMin += _t -> getTime();

	// Add the item to the vector
	tasks.push_back(_t);
	
	return toReplot;
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
