#include "utilities.h"

string logfilename = "log.txt";
const bool canLOG = true;

void LOG (string ss)
{
	if (canLOG)
	{
		// Write the log entry
		ofstream f;
		f.open (logfilename, ios::app);
		f << ss << endl;
		f.close();
	}
}
