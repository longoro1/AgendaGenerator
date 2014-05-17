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

	// Workday doesn't exist, create it
	return createDay(_date, i_begin);
}

ostream &operator<<(ostream &os, Agenda &a)
{
	// Print the header
	os << a.name << endl;

	os << "First Day of Work:: " << a.minday << endl;
	os << "Last Day of Work:: " << a.maxday << endl;

	// Print off the workdays
	workdayiterator i_begin = a.begin();
	workdayiterator i_end = a.end();

	while (i_begin != i_end)
	{
		os << *(*i_begin) << endl;
		i_begin++;
	}

	return os;
}
