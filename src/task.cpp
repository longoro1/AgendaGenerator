#include "task.h"

task::task(string _subject, string _name, int _time, int _partitions, 
		string _duedate, int _priority, string _description)
{
	// Assign basic fields
	subject = _subject;
	name = _name;
	time = _time;
	remainingPartitions = _partitions;
	priority = _priority;
	description = _description;
	duedate = _duedate;
}


task::task(const task &_t, const int _newTaskTime)
{
	// Assign basic fields
	subject = _t.subject;
	name = _t.name;
	time = _newTaskTime;
	remainingPartitions = 1;
	priority = _t.priority;
	description = _t. description;
	duedate = _t.duedate;
}

task *task::partition(int _newTaskTime)
{
	// Trying to take away too much time
	if (_newTaskTime > this -> time) return NULL;

	// Reduce the time
	this -> time -= _newTaskTime;

	// Create the new task
	task *t = new task(*this, _newTaskTime);

	return t; 
	
}
