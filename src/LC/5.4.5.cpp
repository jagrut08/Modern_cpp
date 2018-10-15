/*
 * 5.4.5 Binary Tree Maximum Path Sum

Given a binary tree, find the maximum path sum.
The path may start and end at any node in the tree. For example: Given the below binary tree,

For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.

 1
/ \
2  3
Return 6


	-10
   / \
  9  20
    /  \
   15   7

Output: 42

 * 
 * */

#include <bt.h>

#include <algorithm>
#include <iostream>
#include <stdexcept>

/*
 * O(N) time and O(N) space due to recursion
 * Using Post-Order traversal as the sum through a node depends on its children
 * */
int findMaxPathSum(const tnPtr<int>& rootPtr) {
	if(!rootPtr) {
			return 0;
	}

	const int leftSum = findMaxPathSum(rootPtr->left);
	const int rightSum = findMaxPathSum(rootPtr->right);
	const int pathThruNode = leftSum + rightSum + rootPtr->val;
	const int maxChild = std::max(leftSum, rightSum);
	return std::max(pathThruNode, maxChild);
}

int main() {
	try {
			const int nullVal = -1;
			const std::vector<std::vector<int>> levelOrderTraversals {
			/*	{1, 2, 3},
				{1, 2, -6, 4, -1, 5, -1},
				{},
				{5},
				{5, 1, -1},
				{1, 2, -1, 3, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1}, // left skew
				{1, -1, 2, -1, -1, -1, 3, -1, -1, -1, -1, -1, -1, -1, 4}, // right skew*/

			//	{1, 2, -2, -14, -5, 3, 6},
				{1, 2, -2, -14, 5, 3, 6},
			/*	{-10, -14, -15},
				{0, 1, 2},
				{-5, 2, 4},
				{-10, 9, 20, -1, -1, 15, 7},
			*/};

			for(const auto& levelOrderTraversal : levelOrderTraversals) {
				const auto& rootPtr = createBT(levelOrderTraversal, nullVal);
				printBT(rootPtr);
				std::cout << "Max Path Sum: " << findMaxPathSum(rootPtr) << '\n';
			}
		} catch(const std::exception& e) {
			std::cerr << "Exception in main(): " << e.what() << '\n';
		} catch(...) {
			return -1;
		}
}
