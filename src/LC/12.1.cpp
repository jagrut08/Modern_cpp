/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Determine if you are able to reach the last index.
For example:
A = [2,3,1,1,4], return true.
A = [3,2,1,0,4], return false.
*/

#include <iostream>
#include <stdexcept>
#include <vector>

bool isLastIndexHelper(std::vector<int>* vPtr, const int idx, const std::vector<int>& v) {
	if(!vPtr) {
		throw std::runtime_error("vPtr is null!");
	}
	if(idx >= v.size() - 1) {
		return true;
	}
	if((*vPtr)[idx] != -1) {
		return (*vPtr)[idx] == 1 ? true : false;
	}

	for(int jump = v[idx]; jump > 0; --jump) {
		const int newIdx = idx + jump;
		if(isLastIndexHelper(vPtr, newIdx, v)) {
			(*vPtr)[newIdx] = 1; // TODO Use enum or std::unordered_set to track
			return true;
		}
	}
	(*vPtr)[idx] = 0;
	return false;
}
/*
O(N) time and space as each element is processed once, and we use a mem table of size N + N stack frames for recursion in worst case ([1, 1, 1, 1]).

*/
bool isLastIndexReacheable(const std::vector<int>& v) {
	if(v.empty()) {
		throw std::runtime_error("Empty input");	
	}
	std::vector<int> visited(v.size(), -1);
	return isLastIndexHelper(&visited, 0, v);
}

int main() {
    const std::vector<std::vector<int>> inputs {
        {2, 3, 1, 1, 4},
        {3, 2, 1, 0, 4},
        {1, 0},
        {3, 2, 1, 0},
        {0, 1, 2, 4},
        {2, 3}
        
        
    };
    
    for(const auto& input : inputs) {
        std::cout << std::boolalpha << isLastIndexReacheable(input) << '\n';
    }
}

