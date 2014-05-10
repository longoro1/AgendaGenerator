#include "workday.h"


Workday::Workday(string _date)
{
	// Assign the date
	this -> date = _date;

	// Initialize the number of work minutes

}


float Workday::getPercentAlloc(const int _maxMinutes)
{
	return (float) (numWorkMin / _maxMinutes);
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
