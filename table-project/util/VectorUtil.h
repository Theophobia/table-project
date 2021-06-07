#pragma once

#include <vector>

/**
 * Contains utilities for working with vector objects.
 */
namespace TableProject::VectorUtil {

	template<class T>
	bool contains(const std::vector<T> & v, const T & elem) {
		for (const T & currElem : v) {
			if (currElem == elem) {
				return true;
			}
		}
		return false;
	}
}