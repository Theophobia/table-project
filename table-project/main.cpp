#include <fstream>
#include <iostream>

#include <table-project/TableProject.h>

std::vector<std::string> tokeniseInputString(const std::string & s) {
	std::vector<std::string> v;
	std::string buffer;
	bool isSkipWhitespace = true;

	for (std::size_t i = 0; i < s.size(); i++) {
		if (s[i] == '"') {
			buffer += s[i];
			isSkipWhitespace = !isSkipWhitespace;
			continue;
		}

		if (s[i] == ' ') {

			if (!isSkipWhitespace) {
				buffer += s[i];
				continue;
			}

			if (!buffer.empty()) {
				v.push_back(buffer);
				buffer.clear();
				continue;
			}

			continue;
		}

		buffer += s[i];
	}

	if (!buffer.empty()) {
		v.push_back(buffer);
	}

	return v;
}

void printCommands() {
	std::cout << '\n' << "Available commands:" << '\n'
			  << '\t' << "load <file-path>" << '\n'
			  << '\t' << "save <file-path>" << '\n'
			  << '\t' << "edit <cell-location> <value>" << '\n'
			  << '\t' << "print" << '\n'
			  << '\t' << "printcsv" << '\n'
			  << '\t' << "exit" << '\n';
}

void printUnknownCommand() {
	std::cout << "Unknown command entered, please refer to the command list" << std::endl;
}

int run() {
	using namespace TableProject;
	
	std::shared_ptr<Table> tablePtr;

	printCommands();
	while (true) {
		std::cout << "\n> ";

		std::string inputString;
		std::getline(std::cin, inputString);
		std::vector<std::string> args = tokeniseInputString(inputString);

		switch (args.size()) {
			case 0: {
				std::cout << "ERROR: no command entered, try again" << std::endl;
				break;
			}

			case 1: {
				if (args[0] == "print") {
					if (!tablePtr) {
						std::cout << "ERROR: no table loaded, cannot print" << std::endl;
					}
					else {
						std::cout << *tablePtr;
					}
				}
				else if (args[0] == "printcsv") {
					if (!tablePtr) {
						std::cout << "ERROR: no table loaded, cannot print" << std::endl;
					}
					else {
						std::cout << tablePtr->toCSV();
					}
				}
				else if (args[0] == "exit") {
					return 0;
				}
				else {
					printUnknownCommand();
				}
				break;
			}

			case 2: {
				if (args[0] == "load") {
					if (!TableProject::FileUtil::fileExists(args[1])) {
						std::cout << "ERROR: file does not exist or could not be opened" << std::endl;
						break;
					}

					std::shared_ptr<TableProject::Table> tmpPtr;
					try {
						tmpPtr = std::make_shared<Table>(args[1].c_str());
					}
					catch (std::exception & e) {
						std::cout << "ERROR: could not load table from file\n\t" << e.what() << std::endl;
						break;
					}

					if (tablePtr) {
						std::cout << "INFO: removing old table" << std::endl;
					}

					tablePtr = std::move(tmpPtr);

					std::cout << "INFO: load table" << std::endl;
				}
				else if (args[0] == "save") {
					if (!tablePtr) {
						std::cout << "ERROR: no table exists" << std::endl;
						break;
					}

					if (TableProject::FileUtil::fileExists(args[1])) {
						std::cout << "ERROR: file already exists" << std::endl;
						break;
					}

					std::ofstream fout;
					fout.open(args[1], std::ios::out);
					if (!fout) {
						std::cout << "ERROR: could not open file for writing" << std::endl;
						break;
					}

					fout << tablePtr->toCSV();
					fout.close();

					std::cout << "INFO: wrote table to \"" << args[1] << '"' << std::endl;
				}
				else {
					printUnknownCommand();
				}
				break;
			}

			case 3: {
				if (args[0] == "edit") {
					if (!tablePtr) {
						tablePtr = std::make_shared<Table>();
						std::cout << "INFO: created new table as one does not exist" << std::endl;
					}

					std::size_t rowIndex;
					std::size_t colIndex;

					try {
						std::pair<std::size_t, std::size_t> cellIndices = Table::cellCoordsToIndices(args[1]);
						rowIndex = cellIndices.first;
						colIndex = cellIndices.second;
					}
					catch (std::exception & e) {
						std::cout << "ERROR: could not parse cell location\n\t" << e.what() << std::endl;
						break;
					}

					std::cout << "DEBUG: editing cell ("
							  << std::to_string(rowIndex) + ", "
							  << std::to_string(colIndex) + ")"
							  << std::endl;

					std::shared_ptr<Type> typePtr;
					try {
						typePtr = Type::fromString(args[2]);

					}
					catch (std::exception & e) {
						std::cout << "ERROR: could not parse passed cell data\n\t" << e.what() << std::endl;
						break;
					}

					std::cout << "DEBUG: cell object of class " + typePtr->getClass() << std::endl;

					try {
						tablePtr->put(rowIndex, colIndex, *typePtr);
					}
					catch (std::exception & e) {
						std::cout << "ERROR: could not insert cell into table\n\t" << e.what() << std::endl;
						break;
					}
				}
				else {
					printUnknownCommand();
				}
				break;
			}
		}
	}

	// Unreachable
//	return 0;
}

int main() {
	return run();
}