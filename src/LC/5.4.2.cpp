/*
 * 5.4.2.cpp
 *
 * Maximum depth of a Binary Tree
 */


#include <iostream>
#include <algorithm>
#include <vector>

#include "bt.h"

void findMaxDepthHelper(int& maxDepth, const int depth, const tnPtr& root) {
	if(!root->left && !root->right) {
		maxDepth = std::max(maxDepth, depth);
	} else if(root->left) {
		findMaxDepthHelper(maxDepth, depth + 1, root->left);
	} else if(root->right) {
		findMaxDepthHelper(maxDepth, depth + 1, root->right);
	}
}

int findMaxDepth(const tnPtr& root) {
	if(!root) {
		return -1;
	}
	int maxDepth = 0;
	findMaxDepthHelper(maxDepth, 0, root);
	return maxDepth;
}

int main() {
	const std::vector<tnPtr> roots {
		createBT0(),
		createBT1(),
		createBT2(),
		createBT3(),
		createBT4(),
		createBT5(),
		createBT3LeftSkew(),
		createBT3RightSkew(),
		createBT5_1()
	};

	for(const auto& root : roots) {
		printBT(root);
		std::cout << "Max Depth: " << findMaxDepth(root) << '\n' << '\n';
	}

}

