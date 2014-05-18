#include "fileparser.h"

task *generateTask(string _subject, string _fileline)
{
	// Necessary fields
	string name, duedate, description;
	int time, partitions, priority;

	// Scan in the fields
	string temp;
	istringstream ss(_fileline);
	getline(ss, name, ',');
	getline(ss, temp, ',');
	time = stoi(temp);
	getline(ss, duedate, ',');
	getline(ss, temp, ',');
	priority = stoi(temp);
	getline(ss, temp, ',');
	partitions = stoi(temp);
	getline(ss, description, ',');

	// Create and return the object;
	task *t = new task(_subject, name, time, partitions, 
		duedate, priority, description);

	return t;
}


string getDate()
{
	stringstream ss;

	// Get the time
	time_t now = time(0);
	tm *ltm = localtime(&now);

	// Store the time
	ss << ((ltm -> tm_year) + 1900 - 2000) << "." 
		<< ltm -> tm_mon << "."
		<< (ltm -> tm_mday + 1) << endl;

	// Finsh
	return ss.str();
}

int parseConfigFile(string _filename, int *&_maxworkmin, int *&_maxtasks)
{
	ifstream file; // The config file
	string name; // A temp to hold the line name
	char temp[256];

	// Try to open a file
	file.open(_filename);
	if (!file.is_open()) return -1;

	// Can allocate the arrays
	_maxworkmin = new int[7];
	_maxtasks = new int[7];

	// Get the maxworkmin line
	if(file.eof()) return -1;
	file.getline(temp, 256);
	stringstream ss(temp);
	ss >> name;
	if (name != "maxworkmin") return -1;	
	for(int i = 0; i < 7; i++)
	{
		if(ss.eof()) return -1; // End of string stream
		ss >> _maxworkmin[i];
		if(ss.fail()) return -1; // Didn't work correctly	
	}

	// Get the maxtaskperday line
	if(file.eof()) return -1;
	file.getline(temp, 256);
	stringstream ss2(temp);
	ss2 >> name;
	if (name != "maxtaskperday") return -1;	
	for(int i = 0; i < 7; i++)
	{
		if(ss2.eof()) return -1; // End of string stream
		ss2 >> _maxtasks[i];
		if(ss2.fail()) return -1; // Didn't work correctly	
	}

	// Safe to exit
	file.close();
	return 0;
}

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

	sscanf(_date.c_str(), "%d.%d.%d", &year, &month, &day);
	day--;

	/*// Create a time struct
	struct tm t;
	t.tm_year = year - 1900 + 2000;
	t.tm_mon = month - 1;
	t.tm_mday = day;

	// Offset the number of days
	t.tm_mday += _numDays;
	time_t next = mktime(&t);

	// Output the new days
	year = t.tm_year + 1900;
	month = t.tm_mon + 1;
	day = t.tm_mday;*/

	// Store the new day
	stringstream ss;
	ss << year << "." << month << "." << day << endl;

	// Return the result
	return ss.str();

}



