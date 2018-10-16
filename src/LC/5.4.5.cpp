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
#include <limits>
#include <stdexcept>

/*
 * O(N) time and O(N) space due to recursion
 * Using Post-Order traversal as the max sum path at a node depends on its children (their max sum)
 * */

struct Result {
	int sum;
	bool canBeAdded;

	Result(const int s, const bool b) : sum(s), canBeAdded(b) {}

	Result(const Result& r) : sum(r.sum), canBeAdded(r.canBeAdded) {}

};

Result findMaxPathSumHelper(const tnPtr<int>& rootPtr) {
	if(!rootPtr) {
			return Result(std::numeric_limits<int>::min(), true);
	}

	const Result leftChildSum = findMaxPathSumHelper(rootPtr->left);
	const Result rightChildSum = findMaxPathSumHelper(rootPtr->right);
	const int maxChildSum = std::max(leftChildSum.sum, rightChildSum.sum);

	int pathThruNodeSum = rootPtr->val;
	if(leftChildSum.canBeAdded && leftChildSum.sum > 0) {
		pathThruNodeSum += leftChildSum.sum;
	}
	if(rightChildSum.canBeAdded && rightChildSum.sum > 0) {
		pathThruNodeSum += rightChildSum.sum;
	}

	return pathThruNodeSum > maxChildSum ? Result(pathThruNodeSum, true) : Result(maxChildSum, false);
}

int findMaxPathSum(const tnPtr<int>& rootPtr) {
	if(!rootPtr) {
		throw std::runtime_error("rootPtr is empty");
	}

	return findMaxPathSumHelper(rootPtr).sum;
}
int main() {
	try {
			const std::vector<std::vector<TreeNode<int>>> levelOrderNodes {
				{1, 2, 3},
				{1, 2, -6, 4, nullptr, 5, nullptr},
				{5},
				{5, 1, nullptr},
				{1, 2, nullptr, 3, nullptr, nullptr, nullptr, 4, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, // left skew
				{1, nullptr, 2, nullptr, nullptr, nullptr, 3, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 4}, // right skew
				{1, 2, -2, -14, -5, 3, 6},
				{1, 2, -2, -14, 5, 3, 6},
				{-10, -14, -15},
				{0, 1, 2},
				{-5, 2, 4},
				{-10, 9, 20, nullptr, nullptr, 15, 7},
				{1000, 20000, -5600},
				{},
			};

			for(const auto& nodes : levelOrderNodes) {
				const auto& rootPtr = createBTFromNodes(nodes);
				std::cout << "Max Path Sum: " << findMaxPathSum(rootPtr) << '\n' << '\n';
			}
		} catch(const std::exception& e) {
			std::cerr << "Exception in main(): " << e.what() << '\n';
		} catch(...) {
			return -1;
		}
}
