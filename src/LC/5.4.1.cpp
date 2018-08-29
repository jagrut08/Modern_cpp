
#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <boost/range/combine.hpp>

#include "bt.h"

/*
 5.4.1 Minimum depth of binary tree
 O(N) time, O(2^depth) space, uses BFS
 BFS is preferred since we wish to find the shortest path to a leaf node
 DFS could traverse longer depths first
 BFS may not be appropriate for wide trees, but here we have a BT
 so that's not an issue
*/
template <typename T>
int findMinDepth(const tnPtr<T>& root) {
	if(!root) {
		return -1;
	}

	std::list<tnPtr<T>> queue{root};
	int depth = 0;

	while(!queue.empty()) {
		std::list<tnPtr<T>> tmpQueue;
		for(const auto& ptr : queue) {
			if(!ptr->left && !ptr->right) {
				return depth;
			} else {
				if(ptr->left) {
					tmpQueue.emplace_back(ptr->left);
				}
				if(ptr->right) {
					tmpQueue.emplace_back(ptr->right);
				}

			}
		}
		++depth;
		// The below doesn't work .. "no viable overload"
		// if queue and tmpQueue hold const tnPtrs.
		queue = tmpQueue;
	}

	return depth;
}

/*
int main() {
	const char nullVal = '\0';
	std::vector<std::vector<char>> levelOrderTrees {
		{},
		{'a'},
		{'a', 'b'},
		{'a', 'b', 'c'},
		{'a', 'b', 'c', '\0', '\0', 'd'},
		{'a', 'b', 'c', 'd', '\0', 'e', '\0'},
		{'a', 'b', '\0', 'c'},
		{'a', '\0', 'b', '\0', '\0', 'c'},
		{'a', '\0', 'b', '\0', '\0', 'c', 'd', '\0', '\0', '\0', '\0', '\0', 'e'}
	};
	std::vector<int> minDepths {
		-1,
		0,
		1,
		1,
		1,
		2,
		2,
		2,
		2
	};


	for(size_t i = 0; i < levelOrderTrees.size(); ++i) {
		const auto root = createBT(levelOrderTrees[i], nullVal);
		printBT(root);
		const int minDepth = findMinDepth(root);
		assert(minDepth == minDepths[i]);
		std::cout << "Min depth: " << minDepth << '\n' << '\n';
	}

	// Using boost::combine

	for(auto tup : boost::combine(levelOrderTrees, minDepths)) {
		std::vector<char> levelOrder{};
		int expectedMinDepth = -1;
		boost::tie(levelOrder, expectedMinDepth) = tup;


		const auto root = createBT(levelOrder, nullVal);
		printBT(root);
		const int minDepth = findMinDepth(root);
		assert(minDepth == expectedMinDepth);
		std::cout << "Min depth: " << minDepth << '\n' << '\n';
	}
}


*/
