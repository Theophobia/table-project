#pragma once

#include <string>
#include <fstream>

/**
 * Contains utilities for working with files.
 */
namespace TableProject::FileUtil {
	static bool fileExists(const std::string & filePath) {
		std::ifstream fin(filePath);
		if (!fin.is_open()) {
			fin.close(); // Maybe not needed
			return false;
		}
		fin.close(); // Maybe not needed
		return true;
	}
}