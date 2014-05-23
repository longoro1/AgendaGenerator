#include "task.h"

task::task(string _subject, string _name, int _time, int _partitions, 
		string _duedate, int _priority, string _description)
{
	// Assign basic fields
	subject = _subject;
	name = _name;
	time = _time;
	remainingPartitions = _partitions;
	if (priority == IMMDEDIATE_PRIORITY)
		remainingPartitions = 1;
	
	priority = (_priority >= IMMDEDIATE_PRIORITY 
				&& _priority <= MIN_PRIORITY) 
		? _priority : MIN_PRIORITY; // Within limit
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


bool task::operator== (const task &_t)
{
	// Check basic values
	if (subject != _t.subject) return false;
	if (name != _t.name) return false;
	if (time != _t.time) return false;
	if (remainingPartitions != _t.remainingPartitions) return false;
	if (priority != _t.priority) return false;
	if (duedate != _t.duedate) return false;

	return true;
}

ostream &operator<<(ostream &os, const task &t)
{
	// Print off the task
	os << "[ ] " << t.subject << " - " << t.name << endl
		<< "\tPRIORITY '";
	
	if (t.priority > 0) os << t.priority;
	else os << "IMMEDIATE";

	os << "'\tDUE DATE " 
		<< t.duedate << endl		
		<< "\tTIME " << t.time << " min";
	if (t.remainingPartitions > 1 && t.priority > 0)
		os << "\tPARTITIONS " << t.remainingPartitions;
	os << endl;

	if(!t.description.empty())
		os << '\t' << t.description << endl;

	os << endl;

	return os;
}

