/*
 * 
 *Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.
A region is captured by flipping all 'O's into 'X's in that surrounded region .
For example,
X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:
X X X X
X X X X
X X X X
X O X X
 *
 * 
 * */

#include <print.h>

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

using BoardType = std::vector<std::vector<char>>;

bool findValidRegion(std::vector<std::vector<bool>>* visitedPtr, std::vector<std::pair<int, int>>* regionRowColPairsPtr, const int row, const int col, const BoardType& board) {
	if(!visitedPtr || !regionRowColPairsPtr) {
		throw std::runtime_error("Invalid input");
	}

	(*visitedPtr)[row][col] = true;
	regionRowColPairsPtr->emplace_back(std::make_pair(row, col));

	// Next coordinates - top, bottom, left, right
	const std::vector<int> nextRows{row - 1, row + 1, row, row};
	const std::vector<int> nextCols{col, col, col - 1, col + 1};
	bool validRegion = true;

	// Could use boost::combine to combine nextRowCords and nextColCoords
	for(size_t i = 0; i < nextRows.size(); ++i) {
		const int nextRow = nextRows[i], nextCol = nextCols[i];
		if(nextRow < 0 || nextRow == board.size() || nextCol < 0 || nextCol == board[0].size()) {
			validRegion = false; 	// The current cell is on the edge of the board, and the region is thus exposed
			continue; // However, we should investigate '0's adjacent to this cell as those shouldn't appear
					// as valid regions
		}

		if((*visitedPtr)[nextRow][nextCol]) {
			continue;
		}

		if(board[nextRow][nextCol] == 'X') {
			(*visitedPtr)[nextRow][nextCol] = true;
			continue;
		}

		if(!findValidRegion(visitedPtr, regionRowColPairsPtr, nextRow, nextCol, board)) {
			validRegion = false;
		}
	}
	return validRegion;
}
/*
 * Complexity
time O(N * M), space O(N * M) for "seen", or if seen is an attribute of a cell then an additional field.
 *
 * */
void captureRegion(BoardType& board) {
	if(!board.size()) {
		return;
	}

	const int maxRows = board.size();
	const int maxCols = board[0].size();

	std::vector<std::vector<bool>> visited(maxRows, std::vector<bool>(maxCols, false));
	std::vector<std::vector<std::pair<int, int>>> allValidRegions;

	for(int row = 0; row < maxRows; ++row) {
		for(int col = 0; col < maxCols; ++col) {
			if(visited[row][col]) {
				continue;
			}

			if(board[row][col] == 'O') {
				std::vector<std::pair<int, int>> regionRowColPairs;
				if(findValidRegion(&visited, &regionRowColPairs, row, col, board)) {
					allValidRegions.emplace_back(regionRowColPairs);
				}
			} else {
				visited[row][col] = true;
			}
		}
	}

	// Flip cells identified within valid regions
	for(const auto& regionRowColPairs : allValidRegions) {
		std::for_each(std::cbegin(regionRowColPairs), std::cend(regionRowColPairs),
				[&board](const std::pair<int, int>& p){board[p.first][p.second] = 'X';});
	}
}


int main() {
	try {
		std::vector<std::vector<char>> board {
			{'X', 'O', 'X', 'X'},
			{'X', 'O', 'X', 'X'},
			{'X', 'X', 'O', 'X'},
			{'X', 'O', 'X', 'X'},
		};

//		std::vector<std::vector<char>> board {
//			{'O', 'X'},
//			{'X', 'O'},
//
//		};
		captureRegion(board);
		printContainer(board);
	} catch(const std::exception& e) {
		std::cerr << "Exception in main(): " << e.what() << '\n';
	} catch(...) {
		return -1;
	}
}
