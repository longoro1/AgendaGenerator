#include <iostream>
#include <sstream>
#include <ctime>

using namespace std;

// General constants
const int HELP = 0;
const int EXIT = 7;

/*Gets the current date as a string
	RETURNS:: the current date formatted as day, month, year*/
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

void printheader()
{
	cout << "###################################################" << endl;
	cout << "###################################################" << endl;
	cout << "#                                                 #" << endl;
	cout << "#                 AGENDA GENERATOR                #" << endl;
	cout << "#                      v 1.0                      #" << endl;
	cout << "#                                                 #" << endl;
	cout << "#               BY:: HACKBIT STUDIOS              #" << endl;
	cout << "#                                                 #" << endl;
	cout << "###################################################" << endl;
	cout << "###################################################" << endl;
	cout << endl;
}

void printmenu()
{
	cout << endl << "What would you like to do?" << endl << endl;
	cout << "0) Help Me!" << endl;
	cout << "1) Generate a sample csv file" << endl;
	cout << "2) Create an Agenda" << endl;
	cout << "3) Fill an Agenda" << endl;	
	cout << "4) Print out an Agenda" << endl;
	cout << "5) Save an agenda to disk" << endl;
	cout << "6) Load an agenda from disk" << endl;
	cout << "7) Exit Application" << endl;
}

int shell()
{
	int menuchoice; // What menu item was chosen

	do{
		// Print the menu and get an item
		printmenu();
		cout << "> ";
		cin >> menuchoice;
		
		// Input failed
		if (cin.fail())
		{
			cerr << endl << "Invalid option. Please input a number!" 
				<< endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		
		// Input not in menu range
		if (menuchoice > EXIT || menuchoice < HELP)
			cerr << endl << "Please select a number between "
				<< "0 and 7." << endl;


	} while (menuchoice > EXIT || menuchoice < HELP);

	return menuchoice;
}

int main (int numarg, char *arg[])
{
	// Improper number of config file parameters
	/*if(numarg != 2)
	{
		cerr << "Configuration file not specified. Terminating program."
			 << endl;
		return 0;
	}*/

	// Print the shell header
	printheader();


	int menuchoice;

	// Keep processing input until exit
	do{
		menuchoice = shell();




	} while (menuchoice != EXIT);
		

	cout << endl << "Terminating Application!" << endl;

	return 0;	

}



























