/*
 * 11.2.cpp
 * Implement int sqrt(int x).
Compute and return the square root of x.
 *
 */

#include <numeric>
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
	//	std::cout << "\nMid " << mid << '\n';
		const int curAns = mid * mid;
		if(curAns == x) {
			return mid;
		} else if(curAns > x) {
			high = mid;
		} else {
			low = mid;
		}
	}

	return low;
}

// LC Discuss top answer also employs binary search
// https://leetcode.com/problems/sqrtx/discuss/25047/A-Binary-Search-Solution

int main() {
	
	std::vector<int> inputs(1000);
	std::iota(std::begin(inputs), std::end(inputs), 0);
	
	for(const auto input : inputs) {
	    const int expected = static_cast<int>(sqrt(input));
	    const int actual = mySqrt(input);
	    
	    if(expected != actual){
	        std::cout << input << " - " << expected  << " : " << actual << '\n';
	    }	
	}
}
