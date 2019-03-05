#include <iostream>
#include <stdexcept>
#include <vector>

enum class IndexStatus : int {not_visited, good, bad};

bool isLastIndexHelper(std::vector<IndexStatus>* vPtr, const int idx, const std::vector<int>& v) {
	if(!vPtr) {
		throw std::runtime_error("vPtr is null!");
	}
	if(idx >= v.size() - 1) {
		return true;
	}
	if((*vPtr)[idx] != IndexStatus::not_visited) {
		return (*vPtr)[idx] == IndexStatus::good ? true : false;
	}

	for(int jump = v[idx]; jump > 0; --jump) {
		const int newIdx = idx + jump;
		if(isLastIndexHelper(vPtr, newIdx, v)) {
			(*vPtr)[newIdx] = IndexStatus::good; // TODO Can also use std::unordered_set to track
			return true;
		}
	}
	(*vPtr)[idx] = IndexStatus::bad;
	return false;
}
/*
O(N^2) time. For each index, we look at all of the indexes on its right to see if they are good (one can reach the last index from them)
O(N) space complexity as we use a mem table of size N + N stack frames for recursion in worst case (e.g., [1, 1, 1, 1]).
https://leetcode.com/articles/jump-game/
*/
bool isLastIndexReacheable(const std::vector<int>& v) {
	if(v.empty()) {
		throw std::runtime_error("Empty input");	
	}
	std::vector<IndexStatus> visited(v.size(), IndexStatus::not_visited);
	return isLastIndexHelper(&visited, 0, v);
}

// O(N) time, O(1) space
bool isLastIndexReacheableOpt(const std::vector<int>& v) {
    if(v.empty()) {
        throw std::runtime_error("Empty input");
    }
    
    int idxToReach = v.size() - 1;
    for(int idx = v.size() - 2; idx >= 0; --idx) {
        // From idx, you can jump v[idx] to the right, does that enable you to reach the last index?
        if(idx + v[idx] >= idxToReach) {
            // If you are able to reach the last index, then this index becomes the index to be reached
            // Need not try to reach index v.size() - 1 from every location in v, just the next index from which
            // it's possible to reach v.size() - 1
            idxToReach = idx;
        }
    }
    return idxToReach == 0;    
}
int main() {
    const std::vector<std::vector<int>> inputs {
        {2, 3, 1, 1, 4},
        {3, 2, 1, 0, 4},
        {1, 0},
        {3, 2, 1, 0},
        {0, 1, 2, 4},
        {2, 3},
        {1, 1, 0, 2, 3},
        {2, 4, 2, 1, 0, 2, 0},
        {9, 4, 2, 1, 0, 2, 0}
    };
    
    for(const auto& input : inputs) {
        std::cout << std::boolalpha << isLastIndexReacheable(input) << " - " << isLastIndexReacheableOpt(input) << '\n';
    }
}

