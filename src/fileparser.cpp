#include "fileparser.h"


/*
// Assign the other parameters
		string temp;
		istringstream ss(scan);
		getline(ss, key, ',');
		getline(ss, temp, ',');
		time = stoi(temp);
		getline(ss, deadline, ',');
		getline(ss, temp, ',');
		priority = stoi(temp);
		getline(ss, temp, ',');
		numPartitions = stoi(temp);
		getline(ss, details, ',');
*/


int getDayofWeek (string _date)
{
	int day, month, year;

	sscanf(_date.c_str(), "%d.%d.%d", &month, &day, &year);

	// Create a time struct
	struct tm t;
	t.tm_year = year - 1900;
	t.tm_mon = month - 1;
	t.tm_mday = day;
	mktime(&t); // Configure the struct
	
	// Return the day of the week
	return t.tm_wday;
}

string shiftDate(const string _date, const int _numDays)
{
	int day, month, year;

	sscanf(_date.c_str(), "%d.%d.%d", &month, &day, &year);

	// Create a time struct
	struct tm t;
	t.tm_year = year - 1900;
	t.tm_mon = month - 1;
	t.tm_mday = day;

	// Offset the number of days
	t.tm_mday += _numDays;
	mktime(&t);

	// Store the new day
	stringstream ss;
	ss << ((t.tm_year) + 1900) << "." 
		<< t.tm_mon << "."
		<< (t.tm_mday + 1) << endl;

	// Return the result
	return ss.str();

}
