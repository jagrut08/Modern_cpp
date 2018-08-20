/*
 * btnew.h
 *
 */

#ifndef SRC_COMMON_BTNEW_H_
#define SRC_COMMON_BTNEW_H_

#include <iostream>
#include <exception>
#include <memory>
#include <vector>
#include <list>

template <typename T>
struct TreeNode {
	T val;
	std::shared_ptr<TreeNode<T>> left, right;

	TreeNode(const T v) : val(v) {}
	TreeNode(const TreeNode& n): val(n.val), left(n.left), right(n.right) {}

	const TreeNode& operator =(const TreeNode& n) {
		if(this != &n) {
			val = n.val;
			left = n.left;
			right = n.right;
		}
		return *this;
	}
};

template <typename T>
using tnPtr = std::shared_ptr<TreeNode<T>>;

// Non member functions to print and create BTs
// They are defined in the header itself to avoid the 'external symbol not found' linker error
// With MSVC, there isn't a compiler/linker error when multiple .cpp files include this header
// For Clang, try using the extern template technique (declare instantiation of the below template functions
// as extern template ...  in all .cpp files that include this header

// Create a Binary Tree
// The first arg is a vector that specifies values for nodes at each level, from left to right (similar to level order traversal)
// The second arg is a single value that acts as the null value
// E.g., {1, 2, 3}, {1} => BT with 1 at the root, 2 as left node, 3 as right node
// {1, -1, 3}, {-1} => 1 at the root, no left node, 3 as the right node
// {1, -1, 2, 3, 4}, {-1} => 1 at the root, no left node, 2 as right node, but 3 and 4 go under a null parent. invalid_argument() thrown.
// {1, -1, 2, -1, -1, 3, 4}, {-1} => similar to the above example, but 3 and 4 go under 2
// {'a', '\0', 'c'}, {'\0'} => a at the root, no left node, c as the right node
template <typename T>
tnPtr<T> createBT(const std::vector<T>& v, const T& nullVal) {
	if(v.empty() || v[0] == nullVal) {
		return nullptr;
	}
	std::vector<tnPtr<T>> ptrs(v.size(), nullptr);
	try{
		ptrs[0] = std::make_shared<TreeNode<T>>(v[0]);
		tnPtr<T> parent;
		std::ostringstream ostr;
		for(size_t childIdx = 1, parentIdx = 0; childIdx < v.size(); ++parentIdx) {

			ostr << "Parent: " << (ptrs[parentIdx]->val ? ptrs[parentIdx]->val : "nullptr") << " left: ";

			if(v[childIdx] != nullVal) {
				ptrs[childIdx] = std::make_shared<TreeNode<T>>(v[childIdx]);
				if(ptrs[parentIdx]) {
					ptrs[parentIdx]->left = ptrs[childIdx];
					ostr << ptrs[childIdx]->val;
				} else {
					throw std::invalid_argument( "Parent is null, but left child is not! Check the input vector.");
				}

			} else { // left child is null
				ostr << "nullptr";
			}

			ostr << " right: ";

			++childIdx;
			if(childIdx < v.size()) {
				if(v[childIdx] != nullVal) {
					ptrs[childIdx] = std::make_shared<TreeNode<T>>(v[childIdx]);
					if(ptrs[parentIdx]) {
						ptrs[parentIdx]->right = ptrs[childIdx];
						ostr << ptrs[childIdx]->val;
					} else {
						throw std::invalid_argument( "Parent is null, but right child is not! Check the input vector.");
					}
				} else {
					ostr << "nullptr";
				}
				++childIdx;
			}

			ostr << '\n';
		}
	} catch(const std::bad_alloc & e) {
		std::cout << e.what() << '\n';
		return nullptr;
	}

	std::cout << ostr.str();
	return ptrs[0];
}

template <typename T>
void printBT(const tnPtr<T>& root) {
	if(!root) {
			std::cout << "{}\n";
			return;
	}

	std::list<tnPtr<T>> queue{root};

	while(!queue.empty()) {
		std::list<tnPtr<T>> tmpQueue;
		for(const auto& ptr : queue) {
			std::cout << ptr->val << " ";
			if(ptr->left) {
				tmpQueue.emplace_back(ptr->left);
			}
			if(ptr->right) {
				tmpQueue.emplace_back(ptr->right);
			}
		}
		// Below won't work if queue and tmpQueue contain const tnPtr
		queue = tmpQueue;
		std::cout << '\n';
	}
}

#endif /* SRC_COMMON_BTNEW_H_ */
