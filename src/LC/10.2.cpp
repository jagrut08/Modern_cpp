/*
A robot is located at the top-left corner of a m * n grid (marked ’Start’ in the diagram below).
The robot can only move either down or right at any point in time. The robot is trying to reach the
bottom-right corner of the grid (marked ’Finish’ in the diagram below).
How many possible unique paths are there?
*/
#include <iostream>
#include <stdexcept>
#include <vector>

// Recursive solution
// Time complexity exponential
// Space complexity O(n + m), the longest possible path, which corresponds to that many recursive stack frames
void findPathsHelper(int *pathsPtr, const int m, const int n, const int curRow, const int curCol) {
	if(pathsPtr == nullptr) {
		throw std::runtime_error("Unexpected nullptr");
	}

	if(curRow == m - 1 && curCol == n - 1) {
		++(*pathsPtr);
	} else {
		const int nextRow = curRow + 1;
		if(nextRow < m) {
			findPathsHelper(pathsPtr, m, n, nextRow, curCol);
		}
		const int nextCol = curCol + 1;
		if(nextCol < n) {
			findPathsHelper(pathsPtr, m, n, curRow, nextCol);
		}
	}
}
int findPaths(const int m, const int n) {
	if(m <=0 || n <= 0) {
		return -1;	
	}
	int paths = 0;
	findPathsHelper(&paths, m, n, 0, 0);
	return paths;
}

/*
Better solutions
DP
http://buttercola.blogspot.com/2014/09/leetcode-unique-paths.html

Optimized DP
https://leetcode.com/problems/unique-paths/discuss/22954/0ms-5-lines-DP-Solution-in-C%2B%2B-with-Explanations

Treat it like a combination: https://leetcode.com/problems/unique-paths/discuss/22981/My-AC-solution-using-formula, for explanation watch
https://www.youtube.com/watch?v=M8BYckxI8_U

Treat it like a permutation: https://leetcode.com/problems/unique-paths/discuss/22958/Math-solution-O(1)-space
*/
/*
int main() {
	const std::vector<std::pair<int, int>> inputs {
		std::make_pair(2, 2),
		std::make_pair(2, 3),
		std::make_pair(3, 4),
		
	};
	
	for(const auto& input : inputs) {
		std::cout << input.first << ", " << input.second << " :  " <<  findPaths(input.first, input.second) << '\n';
	}
}	
*/
