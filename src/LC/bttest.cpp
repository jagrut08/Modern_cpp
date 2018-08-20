/*
 * bttest.cpp
 *
 */

#include <vector>
#include "btnew.h"

int main() {
	const std::vector<int> nodes{1, 2, 3};
	const int nullVal = -1;
	auto root = createBT(nodes, nullVal);
	printBT(root);
}



