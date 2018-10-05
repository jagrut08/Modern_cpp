/*
 * 5.4.4.cpp
 * Given a binary tree and a sum, find all root-to-leaf paths where each path’s sum equals the given sum.
For example: Given the below binary tree and sum = 22,
 5
/  \
4   8
/  / \
11 13 4
/ \  / \
7 2  5 1

return
[
[5,4,11,2],
[5,8,4,5]
]
 *
 */
#include <bt.h>
#include <print.h>

#include <boost/range/combine.hpp>
#include <boost/tuple/detail/tuple_basic.hpp>

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

/*
Time: O(N) as each node is examined
Space: O(N) stack frames due to recursion + curPath size O(N) + allPaths size  O(2^(d - 1) * N) if every path is added to allPaths
*/

// Optimization - you can avoid passing curSum as a param if you reduce n at each call
// the final check becomes rootPtr->val == n
void findPathsHelper(std::vector<tnPtr<int>>* curPathPtr, int* curSumPtr, std::vector<std::vector<tnPtr<int>>>* allPaths, const tnPtr<int>& rootPtr, const int n) {
	if(!curPathPtr || !allPaths) {
		throw std::runtime_error("Invalid inputs");
	}

	if(!rootPtr) {
		return;
	}

	*curSumPtr += rootPtr->val;
	curPathPtr->emplace_back(rootPtr);

	if(!rootPtr->left && !rootPtr->right) {
		if(*curSumPtr == n) {
			allPaths->emplace_back(*curPathPtr);
		}
	} else {
		findPathsHelper(curPathPtr, curSumPtr, allPaths, rootPtr->left, n);
		findPathsHelper(curPathPtr, curSumPtr, allPaths, rootPtr->right, n);
	}

	*curSumPtr -= rootPtr->val;
	curPathPtr->pop_back();
}

std::vector<std::vector<tnPtr<int>>> findPaths(const tnPtr<int>& root, const int n) {
	std::vector<std::vector<tnPtr<int>>> allPaths;
	std::vector<tnPtr<int>> curPath;
	int curSum = 0;
	findPathsHelper(&curPath, &curSum, &allPaths, root, n);
	return allPaths;
}


int main() {
	try {
		const int nullVal = -1;
		const std::vector<std::vector<int>> levelOrderTraversals {
			{5, 4, 8},
			{5, 4, 8},
			{5},
			{5},
			{5, 4, -1},
			{5, 4, -1},
			{5, -1, 8},
			{5, -1, 8},
			{1, 5, 5},
			{5, 4, 8, -1, 6, 9, 4, -1, -1, 7, 2, -1, -1, 5, 5},
//
//			{1, 2, -1, 3, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1}, // left skew
//			{1, -1, 2, -1, -1, -1, 3, -1, -1, -1, -1, -1, -1, -1, 4}, // right skew
//			{1, -1, 2, -1, -1, -1, 3, -1, -1, -1, -1, -1, -1, -1, 4}, // right skew

		};

		const std::vector<int> ns = {
				9,
				-1,
				5,
				-1,
				9,
				-1,
				13,
				-1,
				6,
				22,
		};

		assert(levelOrderTraversals.size() == ns.size() && "Ranges passed to boost::combine not equal in size");

		for(auto tup : boost::combine(levelOrderTraversals, ns)) {
			std::vector<int> levelOrderTraversal;
			int n = -1;
			boost::tie(levelOrderTraversal, n) = tup;

			const auto root = createBT(levelOrderTraversal, nullVal);
			printBT(root);
			const auto& res = findPaths(root, n);
		//	assert(res == expResVal);
			std::cout << "Paths adding up to " << n << " : " << res.size() << '\n';
			printContainer(res);
			std::cout << '\n';
		}
	} catch(const std::exception& e) {
		std::cerr << "Exception in main() " << e.what() << '\n';
	} catch(...) {
		return -1;
	}
}

