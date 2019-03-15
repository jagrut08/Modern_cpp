/*
12.2 Jump Game II
Given an array of non-negative integers, you are initially positioned at the first index of the array. Each element in the array represents your maximum jump length at that position. Your goal is to reach the last index in the minimum number of jumps. 
For example: Given array A = [2,3,1,1,4]
The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)
*/
#include <iostream>
#include <stdexcept>
#include <vector>

// Having 3 status values prevents children nodes that are already going to be processed as the next generation, from getting into the next generation vector again

enum class VisitedStatus : int {notVisited, visiting, visited};

std::vector<int> getNextIdxs(std::vector<VisitedStatus>* visitedPtr, const int idx, const std::vector<int>& v) {
	if(!visitedPtr) {
		throw std::runtime_error("visitedPtr is null!");
	}
	std::vector<int> res;
	for(int jumpLen = v[idx]; jumpLen > 0; --jumpLen) {
		const int nextIdx = idx + jumpLen;
		if(nextIdx < v.size() && (*visitedPtr)[nextIdx] == VisitedStatus::notVisited) {
			res.emplace_back(nextIdx);
			(*visitedPtr)[nextIdx] = VisitedStatus::visiting;
		}
	}
	return res;
}
// BFS, time complexity ?
int findMinJumps(const std::vector<int>& v) {
	if(v.empty()) {
		throw std::runtime_error("Empty input!");
    }
    
    std::vector<VisitedStatus> visited(v.size(), VisitedStatus::notVisited);
    std::vector<int> curIdx{0};
    int cnt = 0;
	while(!curIdx.empty()) {
		std::vector<int> nextIdx;
		for(const auto& idx : curIdx) {
			if(idx == v.size() - 1) {
				return cnt;
			}
            visited[idx] = VisitedStatus::visited;
            const auto& nextGenIds = getNextIdxs(&visited, idx, v);
            nextIdx.insert(nextIdx.end(), nextGenIds.begin(), nextGenIds.end());
        }
		curIdx = nextIdx;
        ++cnt;
	}
	return -1;
}

// Don't actually need to track visited in BFS - see https://leetcode.com/problems/jump-game-ii/discuss/18028/O(n)-BFS-solution
int main() {
    std::vector<std::vector<int>> inputs {
      {2, 3, 1, 1, 4},  
      {1, 0},
      {0, 2},
      {1},
      {2, 2, 1, 4},
      {1, 1, 1, 1},
      {1, 2, 3, 2, 5, 3, 0, 2}
      
    };
    
    for(const auto& input : inputs) {
        std::cout << findMinJumps(input) << '\n';
    }
}
