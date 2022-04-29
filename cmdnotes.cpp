// author: luna aphelion
// contact: luna-aphelion@outlook.com

/*
TODO:
make it tell the user that a command does not exist in stead of just calling PrintHelp()
add a confirmation thing to -delete and -amend
*/

#include <iostream>

#include <string>

#include <vector>

#include <sstream>

#include <fstream>

using namespace std;

// this is the source code for cmdnotes, it will almost certainly be awful, i apologise for the pain reading this code may cause.
// this program is licenced under the GPLv3 a copy of which can be found at https://www.gnu.org/licenses/gpl-3.0.en.html

void PrintHelp() {
	// lists the commands
	cout << "-see: lets you print a specific note" << endl;
	cout << "-delete lets you delete a note" << endl;
	cout << "-mknote: lets you make a new note" << endl;
	cout << "-list: prints all your notes to the screen" << endl;
	cout << "-amend: lets you overwrite an existing note" << endl;
	cout << "-about: tells you information about the program" << endl;
}

int main(int argc, char * argv[]) {
	//sets up varibles that the program needs
	string input;
	vector < string > Notes;
	int SaveNoteOnLine = 1;
	string output; //a var needed for specific situations, not used for all output
	string NoteToDump;
	int PrintNote; //also used for the delete command

	if (argc > 1) {
		input = argv[1];
	}

	// imports any notes the user has saved in prior sessions
	ifstream in ("cmdnotes_data.txt");
	string str;
	// Read the next line from File untill it reaches the end.
	while (getline( in , str)) {
		// Line contains string of length > 0 then save it in vector
		if (str.size() > 0)
			Notes.push_back(str);
	} in .close();
	SaveNoteOnLine = Notes.size();

	// the main code that the user interacts with

	if (input == "-list") {

		if (SaveNoteOnLine == 0) {
			cout << "you have no notes" << endl;
		}

		for (int i = 0; i < SaveNoteOnLine; i++) {
			cout << i + 1 << " " << Notes.at(i) << endl;
		}
	} else if (input == "-see") {

		input = argv[2];

		for (int i = 0; input.size() > i; i++) {
			if (isdigit(input.at(i)) == false) {
				cout << "-see only accepts an integer as an input" << endl;
				return 0;
			}
		}
		stringstream ss(input);
		ss >> PrintNote;
		if (PrintNote > SaveNoteOnLine) {
			cout << "Sorry! that note doesnt exist" << endl;
		} else {
			cout << Notes.at(PrintNote - 1) << endl;
		}
	} else if (input == "-delete") {

		input = argv[2];

		for (int i = 0; input.size() > i; i++) {
			if (isdigit(input.at(i)) == false) {
				cout << "-delete only accepts an integer as an input" << endl;
				return 0;
			}
		}
		stringstream ss(input);
		ss >> PrintNote;
		if (PrintNote == -1) {
			//does nothing
		} else if (PrintNote > SaveNoteOnLine) {
			cout << "Sorry! that note doesnt exist" << endl;
		} else {

			Notes.erase(Notes.begin() + (PrintNote - 1));
			SaveNoteOnLine = SaveNoteOnLine - 1;

			// saves the vector to the file
			ofstream outFile("cmdnotes_data.txt");
			for (const auto & e: Notes) outFile << e << endl;
			cout << "vector saved to file" << endl;
			outFile.close();
		}
	} else if (input == "-mknote") {
		cout << "dingus" << endl;
		//getline(cin, input);
		Notes.push_back(argv[2]);
		cout << "saved on line " << SaveNoteOnLine + 1 << endl;
		SaveNoteOnLine++;
		//save the vector to file
		ofstream outFile("cmdnotes_data.txt");
		for (const auto & e: Notes) outFile << e << endl;
		cout << "vector saved to file" << endl;
		outFile.close();
	} else if (input == "-help") {
		PrintHelp();
	} else if (input == "-amend") {
		//allows the user to write to a position in the vector they have already written to

		input = argv[2];

		stringstream ss(input);
		ss >> PrintNote;
		//checks the users input to make sure its an integer
		for (int i = 0; input.size() > i; i++) {
			if (isdigit(input.at(i)) == false) {
				cout << "-amend only accepts an integer as an input" << endl;
				return 0;
			}
		}
		//check if the note exists
		if (PrintNote > SaveNoteOnLine) {
			cout << "Sorry! that note doesnt exist" << endl;
			return 0;

		}

		// shows the user the contents of the note they want to edit
		else {
			cout << Notes.at(PrintNote - 1) << endl;
		}
		// lets the user overwrite the note
		cout << "please type what the note should be" << endl;
		getline(cin, input);
		Notes.at(PrintNote - 1) = input;
		cout << "note saved to vector" << endl;
		//saves the vector to file
		ofstream outFile("cmdnotes_data.txt");
		for (const auto & e: Notes) outFile << e << endl;
		cout << "vector saved to file" << endl;
		outFile.close();
		//todo: make it so that the note is shown in the users input bar and they can edit it right there instead of just overwriting the note.
	} else if (input == "-about") {
		cout << "author: luna aphelion" << endl;
		cout << "contact: luna-aphelion@outlook.com" << endl;
		cout << "this program is licenced under the GPLv3, a copy of which can be found at https://www.gnu.org/licenses/gpl-3.0.en.html" << endl;
	} else if (input == "-debug") {

		// this case exists for development reasons, the code in here will change often
		cout << argv[1];

	} else {
		PrintHelp();
	}
	return 0;
}
