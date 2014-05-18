#include "utilities.h"

string logfilename = "log.txt";
const bool canLOG = true;

void LOG (string ss)
{
	if (canLOG)
	{
		// Get time stamp
		stringstream ss2;

		// Get the time
		time_t now = time(0);
		tm *ltm = localtime(&now);

		// Store the time
		ss2 << "[" << ((ltm -> tm_year) + 1900 - 2000) << "." 
			<< ltm -> tm_mon << "."
			<< (ltm -> tm_mday + 1) 		
			<< "]" << endl;

	
		// Write the log entry
		ofstream f;
		f.open (logfilename, ios::app);
		f << ss2.str() << ss <<endl;
		f.close();
	}
}
