/*
 * test.cpp
 */

#include <bt.h>
#include <node.h>
#include <print.h>
#include <iostream>
#include <list>
#include <memory>
#include <vector>


int main() {
	/*

	const char nullVal = '\0';
	std::vector<std::vector<char>> levelOrderTrees {

		{},
		{'a'},
		{'a', 'b', 'c'},
		{'a', 'b', 'c', 'd', 'e', 'f', 'g'},
		{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o'},
		{'a', 'b', 'c', '\0', '\0', 'd'},
		{'a', 'b', 'c', 'd', '\0', 'e', '\0'},
		{'a', 'b', '\0', 'c'},
		{'a', '\0', 'b', '\0', '\0', 'c'},

		{'a', '\0', 'b', '\0', '\0', 'c', 'd', '\0', '\0', '\0', '\0', '\0', 'e', '\0', '\0'},
		{'a', '\0', 'b', '\0', '\0', 'c', 'd', '\0', '\0', '\0', '\0', 'e', '\0', '\0', '\0'},
		{'a', '\0', 'b', '\0', '\0', 'c', 'd', '\0', '\0', '\0', 'e', '\0', '\0', '\0', '\0'},
		{'a', '\0', 'b', '\0', '\0', 'c', 'd', '\0', '\0', 'e', '\0', '\0', '\0', '\0', '\0'},
		{'a', '\0', 'b', '\0', '\0', 'c', 'd', '\0', 'e', '\0', '\0', '\0', '\0', '\0', '\0'},
		{'a', '\0', 'b', '\0', '\0', 'c', 'd', 'e', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
		{'a', '\0', 'b', '\0', '\0', 'c', 'd', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
	};
	*/

	const int nullVal = -1;
	const std::vector<std::vector<int>> levelOrderTrees {
		{1, 2, 3, 4, -1, 5, -1},
		{1, 2, -1, 3, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1}, // left skew
		{1, -1, 2, -1, -1, -1, 3, -1, -1, -1, -1, -1, -1, -1, 4}, // right skew

	};


	for(const auto& levelOrder : levelOrderTrees) {
		try {
			const auto& root = createBT(levelOrder, nullVal);
		//	printBT(root);
		//	std::cout << '\n';
			prettyPrintBT(root);
			std::cout << '\n';
		} catch(const std::exception& e) {
			std::cerr << e.what() << '\n';
		} catch(...) {
			return -1;
		}
	}

}





