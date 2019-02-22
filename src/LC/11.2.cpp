/*
 * 11.2.cpp
 * Implement int sqrt(int x).
Compute and return the square root of x.
 *
 */

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

// Time complexity O(log(N/2))
int mySqrt(int x) {
	if(x < 0) {
		throw std::runtime_error("Invalid input");
	}
	if(x == 0) {
		return 0;
	}

	int low = 1, high = x/2;

	while(high - low > 1) {
		const int mid = low + (high-low)/2;
		const int curAns = mid * mid;
		if(curAns == x) {
			return curAns;
		} else if(curAns > x) {
			high = curAns;
		} else {
			low = curAns;
		}
	}

	return low;
}

int main() {
	const std::vector<int> inputs {
		4
		/*
		 * examples
4 => 2
2 => 1
0 => 0
1 => 1
-1 => throw
5 => 2
289 => 17
special cases
--


		 *
		 * */
	};

	for(const auto input : inputs) {
		std::cout << sqrt(input) << " : " << mySqrt(input) << '\n';
	}
}

