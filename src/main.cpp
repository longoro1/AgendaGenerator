#include <iostream>
#include <sstream>
#include <ctime>

#include "fileparser.h"
#include "agenda.h"
#include "shell.h"

using namespace std;

// Global variables
int *maxworkmin;
int *maxtasks;

// Agenda
Agenda *agenda = NULL;

/* Reads out a file and parses it line by line
	Assumes formatting: "work,time,deadline,priority,partitions,details"
	filename:: the name of the file to be parsed 
	subject:: the subject associated with the file
	index:: the index associated with the given file
	agenda:: Pointer to the agenda class*/	
void readFile(const string _filename, const string _subject, 
	const int _index, Agenda *_agenda)
{
	ifstream file;
	file.open(_filename);
	string base;
	int maxtasks = 100;
	string sformat = "work,time,deadline,priority,partitions,details";

	int i = 0; // Counter

	// Make sure file opened correctly
	if(file == NULL)
	{
		std::cout << "Failed to open '" << _filename << "'\n";
		return;
	}

	getline(file, base); // Skip first line

	// File does not follow given specs
	if(base != sformat)
	{
		cout << "ERR Invalid File: \"" 
			<< _filename << "\"" << std::endl ;
		return;
	}
	
	// Create a list of tasks to plot
	tasklist *tlist = new tasklist();

	// Read until end of file
	while(!file.eof() && i < maxtasks)
	{
		getline(file, base);

		// Allocate non-empty strings
		if(!base.empty()) // Line must be non-empty
		{
			// Allocate a new daily task
			task *t = generateTask(_subject, base); // Make new task
			for (int i = 0; i < t -> getPartitions() ; i++)			
				tlist -> push_back (t);
			
			i++; // Increase counter
		}		
	}

	// Plot the tasks into the agenda
	_agenda -> plot_tasklist (tlist);
	delete tlist; // Safe as it is just a list of ptrs


	file.close();

	// Finally, print result
	std::cout << "Scanned " << i << " items from '" << _filename << "'\n";

	return;

	//return tasks;
}

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

	cin.ignore(1000, '\n');
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

/* Prints an agenda */
void printAgenda()
{
	// Nothing to delete
	if (agenda == NULL)
	{
		cout << "No agenda to print!" << endl;
		return;
	}

	// Delete agenda
	cout << *agenda;
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
			
			case 4: // Print Agenda
			printAgenda();
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

	// Delete the agenda
	if (agenda != NULL) delete agenda;
		
	return 0;	

}



























