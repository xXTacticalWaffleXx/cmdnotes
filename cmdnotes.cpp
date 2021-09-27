// author: luna aphelion
// contact: luna-aphelion@outlook.com

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

// this is the source code for cmdnotes beta v7.1, it will almost certainly be awful, i apologise for the pain reading this code may cause.
// this program is licenced under the GPLv3 a copy of which can be found at https://www.gnu.org/licenses/gpl-3.0.en.html

int main(int argc, char *argv[])
{
	//sets up varibles that the program needs
	string input;
	vector <string> Notes;
	int SaveNoteOnLine = 1;
	string output; //a var needed for specific situations, not used for all output
	string NoteToDump;
	int PrintNote; //also used for the delete command
	bool rollback = false;

	// imports any notes the user has saved in prior sessions
	ifstream in("cmdnotes_data.txt");
	string str;
	// Read the next line from File untill it reaches the end.
	while (getline(in, str))
	{
		// Line contains string of length > 0 then save it in vector
		if (str.size() > 0)
			Notes.push_back(str);
	}
	in.close();
	SaveNoteOnLine = Notes.size();

	// the main code that the user interacts with
	cout << "welcome to cmdnotes release 1.0 <3\ntype -help for a list of commands\n";
	while (true) {
		startofcode:
		getline(cin, input);
		if (input == "-list") {
			for (int i = 0; i < SaveNoteOnLine; i++) {
				cout << i + 1 << " " << Notes.at(i) << endl;
			}
		}
		else if (input == "-exit") {
			if (rollback == true) {
				cout << "you still have a transaction open, would you like to commit your changes\n(Y/N)\n";
				cin >> input;
				cin.ignore();
				if (input == "y" || input == "Y") {
					// saves the vector to file
					ofstream outFile("cmdnotes_data.txt");
					for (const auto &e : Notes) outFile << e << "\n";
					cout << "vector saved to file\n";
					outFile.close();
					return 0;
				} if (input == "n" || input == "N") {
					return 0;
				}
				else {
					cout << "invalid input\n";
				}
			}
			else {
				return 0;
			}
		}
		else if (input == "-see") {
			cout << "what note do you want\n";
			cin >> input;
			cin.ignore();
			for (int i = 0; input.size() > i; i++) {
				if (isdigit(input.at(i)) == false) {
					cout << "-see only accepts an integer as an input\n";
					goto startofcode;
				}
			}
			stringstream ss(input);
			ss >> PrintNote;
			if (PrintNote > SaveNoteOnLine) {
				cout << "Sorry! that note doesnt exist\n";
			}
			else {
				cout << Notes.at(PrintNote - 1) << endl;
			}
		}
		else if (input == "-delete") {
			cout << "what note do you want to delete, type -1 to cancel\n";
			cin >> input;
			cin.ignore();
			for (int i = 0; input.size() > i; i++) {
				if (isdigit(input.at(i)) == false) {
					cout << "-delete only accepts an integer as an input\n";
					goto startofcode;
				}
			}
			stringstream ss(input);
			ss >> PrintNote;
			if (PrintNote == -1) {
				//does nothing
			}
			else if (PrintNote > SaveNoteOnLine) {
				cout << "Sorry! that note doesnt exist\n";
			}
			else {
				Notes.erase(Notes.begin() + (PrintNote - 1));
				SaveNoteOnLine = SaveNoteOnLine - 1;
				// saves the vector to the file
				if (rollback == false) {
					ofstream outFile("cmdnotes_data.txt");
					for (const auto &e : Notes) outFile << e << "\n";
					cout << "vector saved to file\n";
					outFile.close();
				}
			}


		}
		else if (input == "-mknote") {
			getline(cin, input);
			Notes.push_back(input);
			cout << "saved on line " << SaveNoteOnLine + 1 << endl;
			SaveNoteOnLine++;
			//save the vector to file
			if (rollback == false) {
				ofstream outFile("cmdnotes_data.txt");
				for (const auto &e : Notes) outFile << e << "\n";
				cout << "vector saved to file\n";
				outFile.close();
			}
		}
		else if (input == "-help") {
			// lists the commands
			cout << "-exit: closes the program" << endl;
			cout << "-see: lets you print a specific note" << endl;
			cout << "-delete lets you delete a note" << endl;
			cout << "-mknote: lets you make a new note" << endl;
			cout << "-list: prints all your notes to the screen" << endl;
			cout << "-transaction: starts a transaction allowing you to rollback changes" << endl;
			cout << "-commit: saves your changes in a transaction to file" << endl;
			cout << "-rollback: reverts your changes" << endl;
			cout << "-amend: lets you overwrite an existing note" << endl;
			cout << "-about: tells you information about the program" << endl;
		}
		else if (input == "-transaction") {
			if (rollback == true) {
				cout << "there is already a transaction in progress\n";
			}
			else {
				cout << "transaction started\n";
				rollback = true;
			}
		}
		else if (input == "-commit") {
			if (rollback == false) {
				cout << "no transaction in progress\n";
			}
			else {
				// saves the vector to a file
				ofstream outFile("cmdnotes_data.txt");
				for (const auto &e : Notes) outFile << e << "\n";
				cout << "vector saved to file\n";
				outFile.close();
				rollback = false;
			}
		}
		else if (input == "-rollback") {
			// lets the user rollback there changes if they have a transaction
			if (rollback == false) {
				cout << "there is no transaction in progress\n";
			}
			else {
				// clears the vector then restores it from the file
				Notes.clear();
				// restores the vector from the file
				ifstream in("cmdnotes_data.txt");
				string str;
				// Read the next line from File untill it reaches the end.
				while (getline(in, str))
				{
					// Line contains string of length > 0 then save it in vector
					if (str.size() > 0)
						Notes.push_back(str);
				}
				in.close();
				SaveNoteOnLine = Notes.size();
				// tells other parts of the program that there isnt a transaction going on any more
				rollback = false;
			}
		}
		else if (input == "-amend") {
		//allows the user to write to a position in the vector they have already written to
		cout << "what note do you want to edit\n";
		cin >> input;
		cin.ignore();
		stringstream ss(input);
		ss >> PrintNote;
		//checks the users input to make sure its an integer
		for (int i = 0; input.size() > i; i++) {
			if (isdigit(input.at(i)) == false) {
				cout << "-amend only accepts an integer as an input\n";
				goto startofcode;
			}
		}
		if (PrintNote > SaveNoteOnLine) {
			cout << "Sorry! that note doesnt exist\n";
			goto startofcode;
		}
		// shows the user the contents of the note they want to edit
		else {
			cout << Notes.at(PrintNote - 1) << endl;
		}
		// lets the user overwrite the note
		cout << "please type what the note should be\n";
		getline(cin, input);
		Notes.at(PrintNote - 1) = input;
		cout << "note saved to vector\n";
		//saves the vector to file
		if (rollback == false) {
			ofstream outFile("cmdnotes_data.txt");
			for (const auto& e : Notes) outFile << e << "\n";
			cout << "vector saved to file\n";
			outFile.close();
		}
		//todo: make it so that the note is shown in the users input bar and they can edit it right there instead of just overwriting the note.
			}
		else if (input == "-about"){
			cout << "author: luna aphelion" << endl;
			cout << "contact: luna-aphelion@outlook.com" << endl;
			cout << "this program is licenced under the GPLv3, a copy of which can be found at https://www.gnu.org/licenses/gpl-3.0.en.html" << endl;
		}
		else if (input == "-debug"){
		
		//print the arguments given to the program at runtime
		for (int i = 0; i < argc; ++i)
        cout << argv[i] << "\n";
		
		}
		else {
			//do nothing
		}
	}
}
