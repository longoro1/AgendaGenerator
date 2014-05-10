#ifndef _FILEPARSER_H
#define _FILEPARSER_H

#include <string>

#include "task.h"

using namespace std;


/* Genearates a task using a given line from a file
	_subject:: subject associated with that file	
	_fileline:: one line of text in the file
	RETURNS:: pointer to a task*/
task &generateTask(string _subject, string _fileline);




#endif
