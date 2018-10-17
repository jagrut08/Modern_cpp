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

struct Result {
	int localPath, connectingPath;
    bool localPathExists;

	Result(const int l, const int c, const bool e) : localPath(l), connectingPath(c), localPathExists(e) {}

	Result(const Result& r) : localPath(r.localPath), connectingPath(r.connectingPath), localPathExists(r.localPathExists) {}
};

std::ostream& operator <<(std::ostream& out, const Result& r) {
	return out << "(" << r.localPath << ", " << r.connectingPath << ", " << std::boolalpha << r.localPathExists << ")";
}
/*
 There are two types of paths at each node:
A path that cannot be added to parent's path - a path through left child, right child and the node itself, aka "localPath"
A path that can be added to the parent's path - a path through node including either left or right child, or neither, but not both, aka "connectingPath"

One cannot compare these 2 paths at a node - either could lead to global maximum. localPath could be greater than connectingPath, but once connectingPath gets added to parent's connecting path, it may exceed localPath.

Also, for leaf nodes, there isn't a localPath. So maintain "localPathExists" to check for whether a valid localPath was ever calculated or not.

Complexity:
O(N) time and O(N) space due to recursion
Using Post-Order traversal as the max sum path at a node depends on its children (their max sum paths)
*
* */
Result findMaxPathSumHelper(const tnPtr<int>& rootPtr) {
	if(!rootPtr) {
			return Result(0,0, false);
	}

	const Result leftChildPaths = findMaxPathSumHelper(rootPtr->left);
	const Result rightChildPaths = findMaxPathSumHelper(rootPtr->right);
	const int localPathHere = leftChildPaths.connectingPath + rightChildPaths.connectingPath + rootPtr->val;

	int maxLocalPathSeen = localPathHere;
	if(leftChildPaths.localPathExists) {
		maxLocalPathSeen = std::max(maxLocalPathSeen, leftChildPaths.localPath);
	}

	if(rightChildPaths.localPathExists) {
		maxLocalPathSeen = std::max(maxLocalPathSeen, rightChildPaths.localPath);
	}

	const int maxChildConnectingPath = std::max(0, std::max(leftChildPaths.connectingPath, rightChildPaths.connectingPath));
	int connectingPathThruNode = rootPtr->val + maxChildConnectingPath;

	//std::cout << "Returning " << Result(maxLocalPathSeen, connectingPathHere) << '\n';
	return Result(maxLocalPathSeen, connectingPathThruNode, true);
}

int findMaxPathSum(const tnPtr<int>& rootPtr) {
	if(!rootPtr) {
		throw std::runtime_error("rootPtr is empty");
	}

	const Result& res = findMaxPathSumHelper(rootPtr);
	return res.localPath > res.connectingPath && res.localPathExists ? res.localPath : res.connectingPath;
}

/*
 * Leetcode discuss solution for comparison
 * https://leetcode.com/problems/binary-tree-maximum-path-sum/discuss/39775/Accepted-short-solution-in-Java
 *
 * GFG also has similar algo
 * https://www.geeksforgeeks.org/find-maximum-path-sum-in-a-binary-tree/
 * */

 int maxValue;

 int maxPathDown(const tnPtr<int>& rootPtr) {
        if (!rootPtr) return 0;
        int left = std::max(0, maxPathDown(rootPtr->left));
        int right = std::max(0, maxPathDown(rootPtr->right));
        maxValue = std::max(maxValue, left + right + rootPtr->val); // equivalent to globally max "localPath"
        return std::max(left, right) + rootPtr->val;// equivalent to "connectingPath"
 }

 int maxPathSum(const tnPtr<int>& rootPtr) {
        maxValue = std::numeric_limits<int>::min();
        maxPathDown(rootPtr);
        return maxValue;
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
				{10, 2, 10, 20, 1, nullptr, -25, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 3, 4},
	//			{},
			};

			for(const auto& nodes : levelOrderNodes) {
				const auto& rootPtr = createBTFromNodes(nodes);
				std::cout << "Max Path Sum: " << findMaxPathSum(rootPtr) <<  ", " << maxPathSum(rootPtr) << '\n' << '\n';
			}
		} catch(const std::exception& e) {
			std::cerr << "Exception in main(): " << e.what() << '\n';
		} catch(...) {
			return -1;
		}
}
