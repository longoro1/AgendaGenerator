#include "workday.h"


Workday::Workday(string _date, int _maxwork, int _maxtasks)
{
	// Assign the date
	date = _date;
	maxworkmin = _maxwork;
	maxtasks = _maxtasks;

}


float Workday::getPercentAlloc()
{
	return (float) (numWorkMin / maxworkmin);
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
