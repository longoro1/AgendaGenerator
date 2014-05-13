#include <iostream>
#include <sstream>
#include <ctime>

#include "agenda.h"
#include "fileparser.h"
#include "shell.h"

using namespace std;

// Global variables
int *maxworkmin;
int *maxtasks;

// Agenda
Agenda *agenda = NULL;

/* Generates a file that the user can fill in*/
void generateFile()
{
	ofstream out("sample.csv");
	out << "work,time,deadline,priority,partitions,details" << endl;
	out.close();

	cout << "File \"sample.csv\" created in local directory" << endl;
}

/* Guides the user through the process of creating a new agenda*/
void makeAgenda()
{
	// Desired name of the agenda
	string agendaname;

	// Make sure that no agenda currently exists
	if (agenda != NULL)
	{
		cout << "An agenda exists already." << endl
			<< "Please delete it first!" << endl;

		return;
	}

	// Get the desired agenda name
	cout << "What would you like to call the agenda (1 word only)?" << endl;
	cin >> agendaname;
	cin.ignore(1000, '\n');

	// Create the agenda
	agenda = new Agenda(agendaname, maxworkmin, maxtasks);

	// Confirm with user
	cout << "Agenda " << agendaname << " created" << endl;
}

/* Populates an agenda with entries */
void fillAgenda()
{
	// Quit if agenda is empty
	if (agenda == NULL)
	{
		cout << "No agenda exists!" << endl;
		return;
	}

	int maxFiles = 8; // How many files can be handled
	int numFiles = 0; // Counter for the number of filenames scanned
	string filename[10]; // The names of the file
	string subject[10]; // The names of the subject
	// thread *t[MAX_FILES]; // Each file gets its own thread

	// Prompt the user for the file names
	std::cout << "Please enter up to " << maxFiles << " files in format: subject filename\n";

	getline(cin, filename[0]); // Skip description line
	stringstream ss(filename[0]);

	// Read files and launch threads
	while(!ss.eof() && numFiles < maxFiles)
	{
		ss >>  subject[numFiles] >> filename[numFiles];
		string s1 = filename[numFiles];
		string s2 = subject[numFiles];
		//t[numFiles] = new thread([s1, s2, numFiles]{
			readFile(s1, s2, numFiles, agenda);
		//});

		numFiles++;
	}

	// Join all threads
	/*for(int i = 0; i < numFiles; i++) 
		if(t[i] -> joinable()) t[i] -> join(); // Join on the threads
		*/
}

/* Deletes the agenda */
void deleteAgenda()
{
	// Nothing to delete
	if (agenda == NULL)
	{
		cout << "No agenda to delete!" << endl;
		return;
	}

	// Delete agenda
	cout << "Deleting agenda " << agenda -> getName() << endl;
	delete agenda;
	agenda = NULL;
}

int main (int numarg, char *arg[])
{
	string filename (arg[1]); // Name of the config file
	int menuchoice; // What menu option was selected

	// Print the shell header
	printheader();

	// Improper number of config file parameters
	if(numarg != 2)
	{
		cerr << "Configuration file not specified. Terminating program."
			 << endl;
		return 0;
	}

	
	// Process the config file
	int err = parseConfigFile (filename, maxworkmin, maxtasks);
	if (err != 0)
	{
		cout << "Error with configuration file" << endl;
		return 0;
	}
	cout << "conf File processed Correctly" << endl << endl;


	// Keep processing input until exit
	do{
		menuchoice = shell();

		switch (menuchoice)
		{
			case HELP: // Help
			printhelp();
			break;

			case 1: // Sample file
			generateFile();
			break;

			case 2: // New Agenda
			makeAgenda();
			break;

			case 3: // Fill Agenda
			fillAgenda();
			break;

			case 7: // Delete Agenda
			deleteAgenda();
			break;

			case EXIT:
			cout << endl << "Terminating Application!" << endl;
			break;

			default:
			cout << "Not yet implemented" << endl;
			break;
		}

	} while (menuchoice != EXIT);
		
	return 0;	

}



























