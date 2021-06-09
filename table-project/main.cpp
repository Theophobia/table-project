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
			  << '\t' << "edit <cell-location> <value>" << '\n'
			  << '\t' << "open <file-path>" << '\n'
			  << '\t' << "saveas <file-path>" << '\n'
			  << '\t' << "save" << '\n'
			  << '\t' << "print" << '\n'
			  << '\t' << "printcsv" << '\n'
			  << '\t' << "exit" << '\n';
}

void printUnknownCommand() {
	std::cout << "Unknown command entered, please refer to the command list" << std::endl;
}

int run() {
	using namespace TableProject;

	std::unique_ptr<Table> tablePtr;
	std::string lastFileName;

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
				if (args[0] == "save") {
					if (lastFileName.empty()) {
						std::cout << "ERROR: have not used any file before, unknown file to save to" << std::endl;
						continue;
					}

					if (!tablePtr) {
						std::cout << "ERROR: no table exists in memory, nothing to save" << std::endl;
						continue;
					}

//					lastFileName = TableProject::StringUtil::removeWrappedQuotes(lastFileName);
					std::ofstream fout;
					fout.open(lastFileName, std::ios::out | std::ios::trunc);

					if (!fout) {
						std::cout << "ERROR: could not open file for writing" << std::endl;
						continue;
					}

					fout << tablePtr->toCSV();
					fout.close();

					std::cout << "INFO: wrote table to \"" << lastFileName << "\"" << std::endl;
				}
				else if (args[0] == "print") {
					if (!tablePtr) {
						std::cout << "INFO: no table exists in memory, nothing to print" << std::endl;
						continue;
					}
					std::cout << *tablePtr;
				}
				else if (args[0] == "printcsv") {
					if (!tablePtr) {
						std::cout << "INFO: no table exists in memory, nothing to print" << std::endl;
						continue;
					}
					std::cout << tablePtr->toCSV();
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
				if (args[0] == "open") {
					args[1] = TableProject::StringUtil::removeWrappedQuotes(args[1]);

					if (!TableProject::FileUtil::fileExists(args[1])) {
						std::cout << "ERROR: file does not exist or could not be opened, nothing was opened"
								  << std::endl;
						continue;
					}

					std::unique_ptr<TableProject::Table> tmpPtr;
					try {
						tmpPtr = std::make_unique<Table>(args[1].c_str());
					}
					catch (std::exception & e) {
						std::cout << "ERROR: could not read table from file\n\t" << e.what() << std::endl;
						continue;
					}

					if (tablePtr) {
						std::cout << "INFO: removing old table" << std::endl;
					}

					tablePtr = std::move(tmpPtr);
					lastFileName = args[1];

					std::cout << "INFO: load table\n"
							  << "INFO: latest file detected is now \"" << lastFileName << "\"" << std::endl;
				}
				else if (args[0] == "saveas") {
					args[1] = TableProject::StringUtil::removeWrappedQuotes(args[1]);

					if (!tablePtr) {
						std::cout << "INFO: no table exists, saving empty file" << std::endl;
//						break;
					}

					if (TableProject::FileUtil::fileExists(args[1])) {
						std::cout << "INFO: file already exists, do you want to overwrite? "
								  << "Enter 'y' or 'n'\n" << "> ";

						std::getline(std::cin, inputString);

						if (inputString.size() == 1 && inputString[0] == 'y') {
							std::cout << "INFO: overwriting file \"" << args[1] << "\" with current data" << std::endl;
						}
						else if (inputString.size() == 1 && inputString[0] == 'n') {
							std::cout << "ERROR: file already exists, did not save" << std::endl;
							break;
						}
						else {
							std::cout << "ERROR: could not understand what was entered\n"
									  << "ERROR: file already exists, did not save" << std::endl;
							break;
						}
					}

					std::ofstream fout;
					fout.open(args[1], std::ios::out | std::ios::trunc);
					if (!fout) {
						std::cout << "ERROR: could not open file for writing, did not save" << std::endl;
						break;
					}

					if (tablePtr) {
						fout << tablePtr->toCSV();
					}
					fout.close();

					lastFileName = args[1];

					std::cout << "INFO: wrote table to \"" << args[1] << "\"\n"
							  << "INFO: latest file detected is \"" << lastFileName << "\"" << std::endl;
				}
				else {
					printUnknownCommand();
				}
				break;
			}

			case 3: {
				if (args[0] == "edit") {
					if (!tablePtr) {
						tablePtr = std::make_unique<Table>();
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

					std::unique_ptr<Type> typePtr;
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

					std::string reproducedCellCoords;
					reproducedCellCoords += TableProject::Table::indexToColumnLetter(colIndex);
					reproducedCellCoords += std::to_string(rowIndex + 1);

					std::cout << "INFO: set cell " << reproducedCellCoords << " with data " << args[2] << std::endl;
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