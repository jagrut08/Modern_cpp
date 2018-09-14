/*
 * test.cpp
 */

#include <iostream>
#include <vector>

#include "bt.h"

int main() {
	const char nullVal = '\0';
	std::vector<std::vector<char>> levelOrderTrees {
//		{},
//		{'a'},
//		{'a', 'b', 'c'},
//		{'a', 'b', 'c', 'd', 'e', 'f', 'g'},
		{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o'},
//		{'a', 'b', 'c', '\0', '\0', 'd'},
/*		{'a', 'b', 'c', 'd', '\0', 'e', '\0'},
		{'a', 'b', '\0', 'c'},
		{'a', '\0', 'b', '\0', '\0', 'c'},
		{'a', '\0', 'b', '\0', '\0', 'c', 'd', '\0', '\0', '\0', '\0', '\0', 'e'}
*/
	};
	for(const auto& levelOrder : levelOrderTrees) {
		try {
			const auto& root = createBT(levelOrder, nullVal);
			prettyPrintBT(root);
			std::cout << '\n';
		} catch(const std::exception& e) {
			std::cout << e.what() << '\n';
		} catch(...) {
			return -1;
		}
	}
}





