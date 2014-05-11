#include "agenda.h"


Agenda::Agenda (string _name, int *_maxworkmin, int *_maxtasks)
{
	name = _name;
	maxworkmin = _maxworkmin;
	maxtasks = _maxtasks;
}


Workday *Agenda::createDay(string _date)
{
	// Find out the workday
	int workdayindex = getDayofWeek(_date);

	// Initiate a new day
	Workday *day = new Workday (_date, maxworkmin[workdayindex], 
			maxtasks[workdayindex]);

	// Add it to the map
	workdays.insert (pair<string, Workday *>(_date, day));

	// Return the pointer
	return day;
}


Workday *Agenda::getDay(string _date)
{
	// Initially, assume the workday exists
	if (workdays[_date] != NULL) return workdays[_date];
	
	// Workday doesn't exist, create it
	return createDay(_date);

}
