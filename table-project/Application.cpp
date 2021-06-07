#include <table-project/Application.h>

std::vector<std::string> TableProject::Application::tokenise(const std::string & s) {
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

TableProject::Application::Application(std::istream & in, std::ostream & out)
	: in(in), out(out) {


}

bool TableProject::Application::hasOpenFile() const {
	return !filePath.empty();
}

bool TableProject::Application::hasTable() const {
	return (bool) tablePtr;
}

const std::string & TableProject::Application::getFilePath() const {
	return filePath;
}

const TableProject::Table & TableProject::Application::getTable() const {
	return *tablePtr;
}

void TableProject::Application::run() {
	std::string input;

	printCommands();
	while (true) {
		std::getline(in, input);

		if (input.empty()) {
			printUnknownCommand();
			continue;
		}

		const std::vector<std::string> tokens = tokenise(input);
		if (tokens.empty()) {
			printUnknownCommand();
			continue;
		}

		const std::string & cmd = tokens[0];

		if (cmd == "exit") {
			break;
		}

		else if (cmd == "open") {
			if (tokens.size() != 2) {
				printWrongArgCount();
				continue;
			}
			handleCommandOpen(tokens);
		}
	}
}

void TableProject::Application::printCommands() const {
	out << '\n' << "Available commands:" << '\n'
		<< '\t' << "open <file-path>" << '\n';
}

void TableProject::Application::printUnknownCommand() const {

}

void TableProject::Application::printWrongArgCount() const {

}

void TableProject::Application::handleCommandOpen(const std::vector<std::string> & tokens) {
	if (hasOpenFile()) {
		out << "ERROR: already have an open file" << std::endl;

	}
}
