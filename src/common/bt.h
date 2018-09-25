/*
 * btnew.h
 *
 */

#ifndef SRC_COMMON_BT_H_
#define SRC_COMMON_BT_H_

#include <node.h>
#include <print.h>
#include <iostream>
#include <iomanip>
#include <list>
#include <memory>
#include <sstream>
#include <vector>


/*
Non member functions to print and create BTs
They are defined in the header itself to avoid the 'external symbol not found' linker error
*/

/*
Create a Binary Tree
The first arg is a vector that specifies values for nodes at each level, from left to right (similar to level order traversal)
The second arg is a single value that acts as the null value
E.g., {1, 2, 3}, {1} => BT with 1 at the root, 2 as left node, 3 as right node
{1, -1, 3}, {-1} => 1 at the root, no left node, 3 as the right node
{1, -1, 2, 3, 4}, {-1} => 1 at the root, no left node, 2 as right node, but 3 and 4 go under a null parent. invalid_argument() thrown.
{1, -1, 2, -1, -1, 3, 4}, {-1} => similar to the above example, but 3 and 4 go under 2
{'a', '\0', 'c'}, {'\0'} => a at the root, no left node, c as the right node
*/


/*
 * Simple implementation - loop through the input vector, incrementing childIdx twice and parentIdx once during each iteration
 * Allocates a vector of pointers to TreeNodes, mirroring the input vector
 *
 * https://www.geeksforgeeks.org/construct-complete-binary-tree-given-array/
 * has another implementation of creating a Binary Tree - given a TreeNode at index i, the left child is at index 2*i + 1 and the right
 * child is at index 2*i + 2, and you could recurse left and right. However, if you try to implement that iteratively, you'd still need
 * to maintain an array of pointers to TreeNodes that were created previously by the loop. The recursive approach allocates O(N) stack
 * space, while the iterative approach allocates a vector up-front, and is also O(N)
 *
 */
template <typename T>
inline tnPtr<T> createBT(const std::vector<T>& v, const T& nullVal) {
	if(v.empty() || v[0] == nullVal) {
		return nullptr;
	}
	std::vector<tnPtr<T>> ptrs(v.size(), nullptr);

	try{
		ptrs[0] = std::make_shared<TreeNode<T>>(v[0]);
		tnPtr<T> parent;
		for(size_t childIdx = 1, parentIdx = 0; childIdx < v.size(); ++parentIdx) {

			// We need to keep track of pointers to TreeNodes created previously so that the linkages of parent->children can be
			// done correctly. parent TreeNode will always exist at this point so should not be re-created.
			parent = ptrs[parentIdx];

			if(v[childIdx] != nullVal) {
				ptrs[childIdx] = std::make_shared<TreeNode<T>>(v[childIdx]);
				if(parent) {
					parent->left = ptrs[childIdx];
				} else {
					std::cerr << "Parent is null, but left child is not! Check the input vector.";
					return nullptr;
				}

			}

			++childIdx;
			if(childIdx < v.size()) {
				if(v[childIdx] != nullVal) {
					ptrs[childIdx] = std::make_shared<TreeNode<T>>(v[childIdx]);
					if(parent) {
						parent->right = ptrs[childIdx];
					} else {
						std::cerr << "Parent is null, but right child is not! Check the input vector.";
						return nullptr;
					}
				}
				++childIdx;
			}
		}
	} catch(const std::bad_alloc& e) {
		std::cerr << e.what() << '\n';
		return nullptr;
	}

	return ptrs[0];
}

/*
 * Pretty print.
 * Time O(N) for collecting N nodes using breadth first traversal.
 * Only prints the first character of the stringified value of a TreeNode::val.
 * E.g., 'a' or '1' if TreeNode::val = 12.
 * Assumes that TreeNode::val is one character wide.
 * It could be made smarter by multiplying the width and offset variables by width of val, TBD.
 *
 * Time complexity:
 * Size of res vector = depth = d
 * Amount of work done for each string within res = Size of each string in res = 2*2^(d-1) - 1.
 * Total = O(N + (d * 2*2^(d-1) - 1))
 *
 * Space complexity:
 * O(d) strings, each string is 2 * (2^d) - 1
 * Total = O(d * 2 * (2^d) - 1) + space for Breadth First traversal (O(N))
 *
 * An implementation with more bells and whistles can be found here
 * https://articles.leetcode.com/how-to-pretty-print-binary-tree/
 */
template <typename T>
inline void printBT(const tnPtr<T>& root) {
	if(!root) {
		std::cout << "{}\n";
		return;
	}

	std::vector<tnPtr<T>> curNodes {root};
	std::vector<std::vector<tnPtr<T>>> allNodes;

	// Assemble all nodes into allNodes, level by level

	while(!curNodes.empty()) {
			allNodes.emplace_back(curNodes);
			std::vector<tnPtr<T>> nextNodes;
			bool atLeastOneChildAtNextLevel = false;
			for(const auto& ptr : curNodes) {
				if(ptr) {
					// Add left and right nodes to nextNodes, irrespective of
					// whether they are nullptrs
					nextNodes.emplace_back(ptr->left);
					nextNodes.emplace_back(ptr->right);
					atLeastOneChildAtNextLevel = (ptr->left || ptr->right) || atLeastOneChildAtNextLevel;
				} else {
					// Otherwise, add nullptrs for left and right children
					nextNodes.emplace_back(nullptr);
					nextNodes.emplace_back(nullptr);
				}
			}
			// Continue only if there is a child at the next level
			if(atLeastOneChildAtNextLevel) {
				curNodes = nextNodes;
			} else {
				break;
			}
	}
	// Print nodes thus accumulated in allNodes

	int depth = std::pow(2, allNodes.size() - 1);
	int width = 2 * depth - 1;
	int offset = 0, gap = 1;
	std::list<std::string> res; // emplace always to the front of the list and then traverse left to right

	for(auto revIter = std::crbegin(allNodes); revIter != std::crend(allNodes); ++revIter) {
		std::string row(width, ' ');
		int rowIdx = offset;
		const auto& nodes = *revIter;
		for(auto iter = std::cbegin(nodes); iter != std::cend(nodes) && rowIdx < row.size(); ++iter) {
			const auto& nodePtr = *iter;
			if(nodePtr) {
				row[rowIdx] = getFirstChar(*nodePtr);
			}
			rowIdx += gap + 1;
		}
		res.push_front(row);
		gap = 2 * gap + 1;
		offset = 2 * offset + 1;
	}

	printContainer(res, "\n");
	std::cout << '\n';
}

/*
 * Post order traversal with a user-supplied stateless lambda
 *
 * Type U could be printLamdba as in
 * int i = 0;
 * auto printLambda = [&i](const tnPtr<char>& ptr) { std::cout << ptr->val << " " << i++ << '\n'; };
 *
 * */

template <typename T, typename U>
inline void traversePostOrder(const tnPtr<T>& root, U func) {

	if(!root) {
		return;
	}

	if(root->left) {
		traversePostOrder(root->left, func);
	}

	if(root->right) {
		traversePostOrder(root->right, func);
	}

	func(root);
}


/*
 * Pre Order Traversal with a user-supplied stateless lambda
 * */

template <typename T, typename U>
inline void traversePreOrder(const tnPtr<T>& root, U func) {

	if(!root) {
		return;
	}

	func(root);

	if(root->left) {
		traversePostOrder(root->left, func);
	}

	if(root->right) {
		traversePostOrder(root->right, func);
	}
}

/* Useful test cases for binary trees
 *
	const char nullVal = '\0';
	std::vector<std::vector<char>> levelOrderTraversals {

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


	const int nullVal = -1;
	const std::vector<std::vector<int>> levelOrderTraversals {
		{1, 2, 3, 4, -1, 5, -1},
		{1, 2, -1, 3, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1}, // left skew
		{1, -1, 2, -1, -1, -1, 3, -1, -1, -1, -1, -1, -1, -1, 4}, // right skew

	};

 *
 * */

#endif /* SRC_COMMON_BT_H_ */
