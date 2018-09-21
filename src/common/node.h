/*
 * node.h
 *
 */

#ifndef SRC_COMMON_NODE_H_
#define SRC_COMMON_NODE_H_

#include <iostream>
#include <memory>

/*
 * A parent class of TreeNode, GraphNode and ListNode
 */

template <typename T>
struct Node {
	T val;

	Node(const T& v) : val(v) {}

	~Node() {}

	Node(const Node& n) : val(n.val) {}

	Node& operator =(const Node& n) {
		if(this != &n) {
			val = n.val;
		}
		return *this;
	}
};

template <typename T>
struct TreeNode : public Node<T> {
	std::shared_ptr<TreeNode<T>> left, right;

	TreeNode(const T& v) : Node<T>(v) {}
	TreeNode(const TreeNode& n): Node<T>(n.val), left(n.left), right(n.right) {}

	TreeNode& operator =(const TreeNode& n) {
		if(this != &n) {
			Node<T>::val = n.val;
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
std::ostream& operator <<(std::ostream& out, const Node<T>& n) {
	out << std::to_string(n.val);
	return out;
}


#endif /* SRC_COMMON_NODE_H_ */
