#ifndef _TASK_H
#define _TASK_H

#include <string>
#include <regex>

using namespace std;

/* This class is a container for any items relating to a daily task*/
class task {

private:
	// The subject that this task belongs to
	string subject;
	
	// The name of the task
	string name;

	// Estimated time needed to complete the task
	int time;

	// How many partitions are allowed for this task.
	// Set to 1 if no more partitions are allowed
	int remainingPartitions;

	// Numerical day, month, year on which this task is due
	string duedate;

	// Priority of the task
	int priority;

	// Description of the task. Can potentially be empty
	string description;

public:
	// Ctor
	task(string _subject, string _name, int _time, int _partitions, 
		string _duedate, int _priority, string _description);
	~task();

	// Accessors

	// Mutators

	// Member functions

};


#endif
