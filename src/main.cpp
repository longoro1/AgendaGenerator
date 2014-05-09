#include <iostream>
#include <sstream>
#include <ctime>

using namespace std;

/*Gets the current date as a string
	RETURNS:: the current date formatted as day, month, year*/
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

int main (void)
{
	cout << "Hello World!" << std::endl;

	return 0;	

}
