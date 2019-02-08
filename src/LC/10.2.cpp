10.2
int findPaths(const int m, const int n)
--
2x2 => {d, r} and {r, d} => 2
--
empty grid? 
1 cell? (start == finish)
3, 5
2, 4
0, x
x, 0
-ve or 0
--
Algo
findPaths(m, n)
	validation
	paths = 0
	helper(m, n, 0, 0, paths)
	return paths

void helper(m, n, curRow, curCol, paths)
if curRow and curCol are last square
	increment paths
	return 
else
	from this row and column, try to move down and right
	nextRow = curRow + 1
	if nextRow is valid
		helper(m, n, nextRow, curCol)
	nextCol = curCol + 1
	if nextCol is valid
		helper(m, n, nextCol, curRow)
--
Time m *n as entire grid processed once at least
Space complexity - worst case, stack frames = longest path between 00 and bottom square = m + n - 1
--
#include <iostream>
#include <stdexcept>
#include <vector>

// Backtracking
void findPathsHelper(int *pathsPtr, const int m, const int n, const int curRow, const int curCol) {
	if(pathsPtr == nullptr) {
		throw std::exception("Unexpected nullptr");
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

int main() {
	const std::vector<std::pair<int, int>> inputs {
		std::make_pair(2, 2),
	}
	for(const auto& input : inputs) {
		std::cout << input.first << ", " << input.second << " :  " <<  findPaths(input.first, input.second) << '\n';
	}
}	
