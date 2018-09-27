/*
 * 5.4.3.cpp
 *
 * Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the
values along the path equals the given sum.
For example: Given the below binary tree and sum = 22,
5
/ \
4 8
/ / \
11 13 4
/ \ \
7 2 1
return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
 */


#include <bt.h>

#include <boost/range/combine.hpp>
#include <boost/tuple/detail/tuple_basic.hpp>

#include <cassert>
#include <iostream>
#include <stdexcept>

/*
 * O(N) time complexity, O(N) space due to recursive calls
Since we need to find leaf nodes, we have to traverse down the depth, so a DFS type of traversal
may be faster than DFS, in which you'd traverse the entire tree and only in the last iteration, you can
return a true or false. Plus you'd have to maintain partial sums along each path.
 *
 * */
bool pathExistsHelper(const tnPtr<int>& root, const int expSum, const int curSum) {
	if(!root) {
		return false;
	}

	if(!root->left && !root->right) {
		return (curSum + root->val == expSum ? true : false);
	}

	return pathExistsHelper(root->left, expSum, curSum + root->val) ||
		pathExistsHelper(root->right, expSum, curSum + root->val);
}

bool pathExists(const tnPtr<int>& root, const int s) {
	return pathExistsHelper(root, s, 0);
}
/*
int main() {
	try {
		const int nullVal = -1;
		const std::vector<std::vector<int>> levelOrderTraversals {
			{5, 4, 8},
			{5, 4, 8},
			{5, 4, 8},
			{1, 2, 3, 4, -1, 5, -1},
			{1, 2, 3, 4, -1, 5, -1},

			{1, 2, -1, 3, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1}, // left skew
			{1, -1, 2, -1, -1, -1, 3, -1, -1, -1, -1, -1, -1, -1, 4}, // right skew
			{1, -1, 2, -1, -1, -1, 3, -1, -1, -1, -1, -1, -1, -1, 4}, // right skew

		};

		const std::vector<int> expSums = {
				9,
				13,
				5,
				7,
				9,
				10,
				10,
				6
		};

		const std::vector<bool> expRes = {
				true,
				true,
				false,
				true,
				true,
				true,
				true,
				false
		};

		for(auto tup : boost::combine(levelOrderTraversals, expSums, expRes)) {
			std::vector<int> levelOrderTraversal;
			int expSum = -1;
			bool expResVal = false;
			boost::tie(levelOrderTraversal, expSum, expResVal) = tup;

			const auto root = createBT(levelOrderTraversal, nullVal);
			printBT(root);
			const bool res = pathExists(root, expSum);
		//	assert(res == expResVal);
			std::cout << "Path adding up to " << expSum << (res? " exists.\n" : " doesn't exist.\n");
		}
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	} catch(...) {
		return -1;
	}
}
*/



