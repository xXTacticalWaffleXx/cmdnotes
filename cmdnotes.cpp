// author: luna aphelion
// contact: luna-aphelion@outlook.com

/*
TODO:
make it tell the user that a command does not exist in stead of just calling
PrintHelp() add a confirmation thing to -delete and -amend
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// this is the source code for cmdnotes, it will almost certainly be awful, i
// apologise for the pain reading this code may cause. this program is licenced
// under the GPLv3 a copy of which can be found at
// https://www.gnu.org/licenses/gpl-3.0.en.html

void PrintHelp() {
	// lists the commands
	std::cout << "-see: lets you print a specific note" << std::endl;
	std::cout << "-delete lets you delete a note" << std::endl;
	std::cout << "-mknote: lets you make a new note" << std::endl;
	std::cout << "-list: prints all your notes to the screen" << std::endl;
	std::cout << "-amend: lets you overwrite an existing note" << std::endl;
	std::cout << "-about: tells you information about the program" << std::endl;
}

int main(int argc, char *argv[]) {
	// sets up varibles that the program needs
	std::string input;
	std::vector <std::string> Notes;
	int SaveNoteOnLine = 1;
	std::string
			output; // a var needed for specific situations, not used for all output
	std::string NoteToDump;
	int PrintNote; // also used for the delete command

	if (argc > 1) {
		input = argv[1];
	}

	// imports any notes the user has saved in prior sessions
	std::ifstream in("cmdnotes_data.txt");
	std::string str;
	// Read the next line from File untill it reaches the end.
	while (getline(in, str)) {
		// Line contains string of length > 0 then save it in vector
		if (str.size() > 0)
			Notes.push_back(str);
	}
	in.close();
	SaveNoteOnLine = Notes.size();

	// the main code that the user interacts with

	if (input == "-list") {

		if (SaveNoteOnLine == 0) {
			std::cout << "you have no notes" << std::endl;
		}

		for (int i = 0; i < SaveNoteOnLine; i++) {
			std::cout << i + 1 << " " << Notes.at(i) << std::endl;
		}
	} else if (input == "-see") {

		input = argv[2];

		for (int i = 0; input.size() > i; i++) {
			if (isdigit(input.at(i)) == false) {
				std::cout << "-see only accepts an integer as an input" << std::endl;
				return 0;
			}
		}
		std::stringstream ss(input);
		ss >> PrintNote;
		if (PrintNote > SaveNoteOnLine) {
			std::cout << "Sorry! that note doesnt exist" << std::endl;
		} else {
			std::cout << Notes.at(PrintNote - 1) << std::endl;
		}
	} else if (input == "-delete") {

		input = argv[2];

		for (int i = 0; input.size() > i; i++) {
			if (isdigit(input.at(i)) == false) {
				std::cout << "-delete only accepts an integer as an input" << std::endl;
				return 0;
			}
		}
		std::stringstream ss(input);
		ss >> PrintNote;
		if (PrintNote == -1) {
			// does nothing
		} else if (PrintNote > SaveNoteOnLine) {
			std::cout << "Sorry! that note doesnt exist" << std::endl;
		} else {

			Notes.erase(Notes.begin() + (PrintNote - 1));
			SaveNoteOnLine = SaveNoteOnLine - 1;

			// saves the vector to the file
			std::ofstream outFile("cmdnotes_data.txt");
			for (const auto &e: Notes)
				outFile << e << std::endl;
			std::cout << "vector saved to file" << std::endl;
			outFile.close();
		}
	} else if (input == "-mknote") {
		std::cout << "dingus" << std::endl;
		// getline(std::cin, input);
		Notes.push_back(argv[2]);
		std::cout << "saved on line " << SaveNoteOnLine + 1 << std::endl;
		SaveNoteOnLine++;
		// save the vector to file
		std::ofstream outFile("cmdnotes_data.txt");
		for (const auto &e: Notes)
			outFile << e << std::endl;
		std::cout << "vector saved to file" << std::endl;
		outFile.close();
	} else if (input == "-help") {
		PrintHelp();
	} else if (input == "-amend") {
		// allows the user to write to a position in the vector they have already
		// written to

		input = argv[2];

		std::stringstream ss(input);
		ss >> PrintNote;
		// checks the users input to make sure its an integer
		for (int i = 0; input.size() > i; i++) {
			if (isdigit(input.at(i)) == false) {
				std::cout << "-amend only accepts an integer as an input" << std::endl;
				return 0;
			}
		}
		// check if the note exists
		if (PrintNote > SaveNoteOnLine) {
			std::cout << "Sorry! that note doesnt exist" << std::endl;
			return 0;

		}

			// shows the user the contents of the note they want to edit
		else {
			std::cout << Notes.at(PrintNote - 1) << std::endl;
		}
		// lets the user overwrite the note
		std::cout << "please type what the note should be" << std::endl;
		getline(std::cin, input);
		Notes.at(PrintNote - 1) = input;
		std::cout << "note saved to vector" << std::endl;
		// saves the vector to file
		std::ofstream outFile("cmdnotes_data.txt");
		for (const auto &e: Notes)
			outFile << e << std::endl;
		std::cout << "vector saved to file" << std::endl;
		outFile.close();
		// todo: make it so that the note is shown in the users input bar and they
		// can edit it right there instead of just overwriting the note.
	} else if (input == "-about") {
		std::cout << "author: luna aphelion" << std::endl;
		std::cout << "contact: luna-aphelion@outlook.com" << std::endl;
		std::cout << "this program is licenced under the GPLv3, a copy of which "
					 "can be found at https://www.gnu.org/licenses/gpl-3.0.en.html"
				  << std::endl;
	} else if (input == "-debug") {

		// this case exists for development reasons, the code in here will change
		// often
		std::cout << argv[1];

	} else {
		PrintHelp();
	}
	return 0;
}
