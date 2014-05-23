#include "shell.h"

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

void printhelp()
{
	cout << endl << endl;

	cout << "This program will generate an agenda using csv files" << endl;
	cout << "CSV FORMATTING: " 
		<<"\"work,time,deadline,priority,partitions,details\"" << endl;

	cout << endl << endl;
	cout << "SPECIAL NOTES ***********************************************";
	cout << endl;
	cout << "DEADLINE - must be formatted as:: YY.MM.DD" << endl;
	cout << "PRITORITY - a number from 5 - 0." << endl
		<< "\t " << task::IMMDEDIATE_PRIORITY 
			<< " Is a due immediately" << endl
		<< "\t " << task::MAX_PRIORITY 
			<< " Is highest, " << 
			task::MIN_PRIORITY <<" is lowest" << endl
		<< "\t Any other values will be changed to " 
			<< task::MIN_PRIORITY << endl;
	cout << "TIME:: Max amount of time per a partition" << endl;

	cout << endl << endl;
}

void printmenu()
{
	cout << endl << "What would you like to do?" << endl << endl;
	cout << "0) Help Me!" << endl;
	cout << "1) Generate a sample csv file" << endl;
	cout << "2) Create Agenda" << endl;
	cout << "3) Fill Agenda" << endl;	
	cout << "4) Print out Agenda" << endl;
	cout << "5) Save agenda to disk" << endl;
	cout << "6) Load agenda from disk" << endl;
	cout << "7) Delete Agenda" << endl;
	cout << "8) Exit Application" << endl;
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

	cout << endl;
	
	return menuchoice;
}



