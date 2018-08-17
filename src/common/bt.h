/*
 * bt.h
 *
 */

#ifndef BT_H_
#define BT_H_

#include <memory>

struct TreeNode {
	char val;
	std::shared_ptr<TreeNode> left, right;

	TreeNode(const char v) : val(v) {}
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

using tnPtr = std::shared_ptr<TreeNode>;

void printBT(const tnPtr& root);
tnPtr createBT5_1();
tnPtr createBT5();
tnPtr createBT4();
tnPtr createBT3RightSkew();
tnPtr createBT3LeftSkew();
tnPtr createBT3();
tnPtr createBT2();
tnPtr createBT1();
tnPtr createBT0();

#endif /* BT_H_ */
