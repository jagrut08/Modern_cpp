/*
 * bttest.cpp
 *
 */

#include <vector>
#include <stdexcept>

#include "btnew.h"


int main() {
//	const std::vector<int> nodes{1, -1, 2, -1, -1, 4, 4};
//	const int nullVal = -1;

	const std::vector<char> nodes {'a', '\0', 'c'};
	const char nullVal = '\0';

	try {
		auto root = createBT(nodes, nullVal);
		printBT(root);
	} catch(const std::invalid_argument& e) {
		std::cerr << e.what();
	}
}



