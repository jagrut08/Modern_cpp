/*
 * 11.2.cpp
 * Implement int sqrt(int x).
Compute and return the square root of x.
 *
 */

#include <algorithm>
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

	while(high > low) {
		if(high - low == 1) {
			return (high * high <= x ? high : low);
		}
		const int mid = low + (high - low)/2;
		const int curAns = mid * mid;
		if(curAns == x) {
			return curAns;
		} else if(curAns > x) {
			high = mid;
		} else {
			low = mid;
		}
	}

	return low;
}

int main() {
	const std::vector<int> inputs {

		/*
		 * other examples
-1 => throw
289 => 17
special cases */
	};

	for(const auto input : inputs) {
		std::cout << sqrt(input) << " : " << mySqrt(input) << '\n';
	}
}

