/*
 * node.h
 *
 */

#ifndef SRC_COMMON_NODE_H_
#define SRC_COMMON_NODE_H_

#include <iostream>
#include <memory>
#include <string>

/*
 * Node - A parent struct of TreeNode, GraphNode and ListNode
 */

template <typename T>
struct Node {
	T val;
	bool isNull = false; // Whether a null node was created intentionally

	Node(const T& v, bool isNullInput = false) : val(v), isNull(isNullInput) {}

	// Needed to create null nodes - e.g., Node<int>(nullptr)
	Node(const T* vPtr) {
		if(!vPtr) {
			isNull = true;
		} else {
			val = *vPtr;
		}
	}

	~Node() {}

	Node(const Node& n) : val(n.val), isNull(n.isNull) {}

	Node& operator =(const Node& n) {
		if(this != &n) {
			val = n.val;
			isNull = n.isNull;
		}
		return *this;
	}
};

template <typename T>
struct TreeNode : public Node<T> {
	std::shared_ptr<TreeNode<T>> left, right;

	TreeNode(const T& v) : Node<T>(v) {}

	TreeNode(const T* v) : Node<T>(v) {} // Needed to create null nodes

	TreeNode(const TreeNode& n): Node<T>(n.val, n.isNull), left(n.left), right(n.right) {}

	TreeNode& operator =(const TreeNode& n) {
		if(this != &n) {
			Node<T>::val = n.val;
			Node<T>::isNull = n.isNull;
			left = n.left;
			right = n.right;
		}
		return *this;
	}
};

template <typename T>
using tnPtr = std::shared_ptr<TreeNode<T>>;

// Overloaded stream insertion operator
template <typename T>
inline std::ostream& operator <<(std::ostream& out, const Node<T>& n) {
	out << std::to_string(n.val);
	return out;
}

#endif /* SRC_COMMON_NODE_H_ */
