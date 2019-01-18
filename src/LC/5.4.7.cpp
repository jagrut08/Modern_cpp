/*
 *
 * Sum Root to Leaf Numbers

Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
An example is the root-to-leaf path 1->2->3 which represents the number 123.
Find the total sum of all root-to-leaf numbers.
For example,
1
/ \
2 3
The root-to-leaf path 1->2 represents the number 12. The root-to-leaf path 1->3 represents the number 13.
Return the sum = 12 + 13 = 25.
 *
 */


#include <bt.h>

#include <iostream>
#include <stdexcept>

/*
 * Algo

DFS, process root, then children, so Pre order.
The number created by parent is multiplied by 10, and then the current node's value is added to it.

O(N) time and space as all nodes need to be checked and added to total

Leetcode solution returns values:
https://leetcode.com/problems/sum-root-to-leaf-numbers/discuss/41363/Short-Java-solution.-Recursion.
 *
 */
void rootToLeafSumHelper(int *finalSumPtr, const int curSum, const tnPtr<unsigned short int>& root) {
	if(!root) {
		return;
	}

	if(!finalSumPtr) {
		throw std::runtime_error("finalSumPtr is null!");
	}

	const int newSum = curSum * 10 + root->val;
	if(!root->left && !root->right) {
		*finalSumPtr += newSum;
	} else {
		rootToLeafSumHelper(finalSumPtr, newSum, root->left);
		rootToLeafSumHelper(finalSumPtr, newSum, root->right);
	}
}

int rootToLeafSum(const tnPtr<unsigned short int>& root) {
	if(!root) {
		return -1;
	}

	int finalSum = 0;
	rootToLeafSumHelper(&finalSum, 0, root);
	return finalSum;
}
/*
int main() {
	try {
			const std::vector<std::vector<TreeNode<unsigned short int>>> levelOrderNodes {
				{1, 2, 3},
				{1},
				{},
				{1, 2},
				{1, 2, 3, 4},
				{1, 2, 3, 4, 5, 6, 7},
				{1, 2, static_cast<unsigned short int>(0), 3, 5, 6, 7},
				{static_cast<unsigned short int>(0), 1, 2, 3, 5, 6, 7},

			};

			for(const auto& nodes : levelOrderNodes) {
				const auto& rootPtr = createBTFromNodes(nodes);
				std::cout << "Root to leaf sum: " << rootToLeafSum(rootPtr) << '\n' << '\n';
			}
		} catch(const std::exception& e) {
			std::cerr << "Exception in main(): " << e.what() << '\n';
		} catch(...) {
			return -999;
		}
}
*/
