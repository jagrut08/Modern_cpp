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

		// If one of the paths is not a valid region, all paths are invalid regions, since they are connected
		// However, we keep track of that here, and don't return() immediately as we wish to traverse all the paths
		if(!findValidRegion(visitedPtr, regionRowColPairsPtr, nextRow, nextCol, board)) {
			validRegion = false;
		}
	}
	return validRegion;
}
/*
 * Complexity
Similar to flood-fill, uses DFS starting at a cell with 'O'. Time O(N * M), space O(N * M) for tracking visited nodes.
	- Iterate over matrix, left to right, top to bottom. Track cells visited.
	- If you find a 'O', start DFS from that point onwards. The DFS will find all connected 'O's. However, if any of the
	  'O's is on the edge, the entire region is deemed "invalid"
	- Flip cells in all "valid" regions

Another approach -
since the "invalid" regions are those that have one or more 'Os' at the edge of the board, we could start our search on the edges. Similar to flood-fill algo, but fill the 'O's with '#'. So
- Search edges of the board for 'Os'. If found,  flood-fill with '#'. Flood-fill will mark all adjacent 'Os' with '#'
 - Flip all 'O's to 'X'. These are the "valid" regions.
 - Flip all '#'s back to 'Os'

 This approach simplifies the DFS a bit as we know that we're finding adjacent "invalid" cells and don't need to track visited cells. However, it iterates over the matrix multiple times.

GFG also has similar: https://www.geeksforgeeks.org/given-matrix-o-x-replace-o-x-surrounded-x/

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
	// This should be done at the end, as flipping cells while iterating may have different results
	// vs. flipping at the end after identifying all valid regions, without changing the input board.
	for(const auto& regionRowColPairs : allValidRegions) {
		std::for_each(std::cbegin(regionRowColPairs), std::cend(regionRowColPairs),
				[&board](const std::pair<int, int>& p){board[p.first][p.second] = 'X';});
	}
}


int main() {
	try {

		std::vector<std::vector<char>> board {
/*
			{'X', 'X', 'X', 'X'},
			{'X', 'O', 'X', 'X'},
			{'X', 'X', 'X', 'X'},
			{'X', 'X', 'O', 'X'},
			{'X', 'X', 'O', 'X'},
*/

/*
			{'O', 'O'},
			{'O', 'O'},
*/

/*
			 {'X', 'O', 'X', 'X', 'X', 'X'},
			 {'X', 'O', 'X', 'X', 'O', 'X'},
			 {'X', 'X', 'X', 'O', 'O', 'X'},
			 {'O', 'X', 'X', 'X', 'X', 'X'},
			 {'X', 'X', 'X', 'O', 'X', 'O'},
			 {'O', 'O', 'X', 'O', 'O', 'O'},
*/
			{'X', 'X', 'X', 'X'},
			{'X', 'O', 'X', 'X'},
			{'X', 'O', 'O', 'X'},
			{'X', 'O', 'X', 'X'},
			{'X', 'X', 'O', 'O'}
		};

		captureRegion(board);
		printContainer(board);
	} catch(const std::exception& e) {
		std::cerr << "Exception in main(): " << e.what() << '\n';
	} catch(...) {
		return -1;
	}
}
