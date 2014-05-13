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

string getDate()
{
	stringstream ss;

	// Get the time
	time_t now = time(0);
	tm *ltm = localtime(&now);

	// Store the time
	ss << ((ltm -> tm_year) + 1900) << "." 
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

void readFile(const string _filename, const string _subject, 
	const int _index, Agenda *_agenda)
{
	ifstream file;
	file.open(_filename);
	string base;
	int maxtasks = 100;
	string sformat = "work,time,deadline,priority,partitions,details";

	int i = 0; // Counter

	// Make sure file opened correctly
	if(file == NULL)
	{
		std::cout << "Failed to open '" << _filename << "'\n";
		return;
	}

	getline(file, base); // Skip first line

	// File does not follow given specs
	if(base != sformat)
	{
		cout << "ERR Invalid File: \"" 
			<< _filename << "\"" << std::endl ;
		return;
	}

	// Read until end of file
	while(!file.eof() && i < maxtasks)
	{
		getline(file, base);
	
		// Allocate non-empty strings
		if(!base.empty()) // Line must be non-empty
		{
			// Allocate a new daily task
			task t = generateTask(_subject, base); // Make new task
			Workday *w = _agenda -> getDay(t.getDate());
			w -> plottask(&t);
			
			i++; // Increase counter
		}
	}


	file.close();

	// Finally, print result
	std::cout << "Scanned " << i << " items from '" << _filename << "'\n";

	return;

	//return tasks;
}

