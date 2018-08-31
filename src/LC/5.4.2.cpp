/*
 * 5.4.2.cpp
 *
 * Maximum depth of a Binary Tree
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

#include <boost/range/combine.hpp>
#include <boost/foreach.hpp>

#include "bt.h"

template <typename T>
void findMaxDepthHelper(int& maxDepth, const int depth, const tnPtr<T>& root) {
	if(!root->left && !root->right) {
		maxDepth = std::max(maxDepth, depth);
	}

	if(root->left) {
		findMaxDepthHelper(maxDepth, depth + 1, root->left);
	}

	if(root->right) {
		findMaxDepthHelper(maxDepth, depth + 1, root->right);
	}
}

/*
O(N) time, O(N) space due to N levels of recursion for unbalanced tree
GFG solution is similar: https://www.geeksforgeeks.org/write-a-c-program-to-find-the-maximum-depth-or-height-of-a-tree/
LC solution:
int maxDepth(TreeNode *root)
{
    return root == NULL ? 0 : max(maxDepth(root -> left), maxDepth(root -> right)) + 1;
}
*/

template <typename T>
int findMaxDepth(const tnPtr<T>& root) {
	if(!root) {
		return 0;
	}
	int maxDepth = 1;
	findMaxDepthHelper(maxDepth, 1, root);
	return maxDepth;
}

int main() {
	const char nullVal = '\0';
	std::vector<std::vector<char>> levelOrderTrees {
		{},
		{'a'},
		{'a', 'b'},
		{'a', 'b', 'c'},
		{'a', 'b', 'c', '\0', '\0', 'd'},
		{'a', 'b', 'c', 'd', '\0', 'e', '\0'},
		{'a', 'b', '\0', 'c'},
		{'a', '\0', 'b', '\0', '\0', 'c'},
		{'a', '\0', 'b', '\0', '\0', 'c', 'd', '\0', '\0', '\0', '\0', '\0', 'e'}

	};
	std::vector<int> maxDepths {
		0,
		1,
		2,
		2,
		3,
		3,
		3,
		3,
		4
	};

	// Using boost::combine and BOOST_FOREACH
	std::vector<char> levelOrder{};
	int expectedMaxDepth = -1;
	BOOST_FOREACH(boost::tie(levelOrder, expectedMaxDepth), boost::combine(levelOrderTrees, maxDepths)) {
		const auto root = createBT(levelOrder, nullVal);
		printBT(root);
	//	std::cout << '\n';
		const int maxDepth = findMaxDepth(root);
		assert(maxDepth == expectedMaxDepth);
		std::cout << "Max depth: " << maxDepth << '\n' << '\n';
	}
}

