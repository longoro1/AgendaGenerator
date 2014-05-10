#ifndef _TASK_H
#define _TASK_H

#include <string>

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


	// Member functions ---------------------------	
	// A copy ctor with a newTaskTime specification
	task(const task &_t, const int _newTaskTime);

public:
	// Ctor
	task(string _subject, string _name, int _time, int _partitions, 
		string _duedate, int _priority, string _description);

	// Accessors
	int getTime() { return time; }

	// Mutators

	// Member functions
	/*Partitions a task to divide the load
		_newTaskTime:: amount of time to allocate to the new task
		RETURNS:: pointer to a new task class, 
			or null if an error occured*/
	task *partition(int _newTaskTime);
};


#endif