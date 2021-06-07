#pragma once

#include <iostream>
#include <memory>
#include <table-project/table/Table.h>

namespace TableProject {
	class Application final {

	private:
		std::istream & in;
		std::ostream & out;
		std::string filePath;
		std::shared_ptr<Table> tablePtr;

		static std::vector<std::string> tokenise(const std::string & s);
	public:
		Application(std::istream & in, std::ostream & out);


		bool hasOpenFile() const;
		bool hasTable() const;

		const std::string & getFilePath() const;

		const Table & getTable() const;

		void run();
		void printCommands() const;
		void printUnknownCommand() const;
		void printWrongArgCount() const;
		void handleCommandOpen(const std::vector<std::string> & tokens);
	};
}
