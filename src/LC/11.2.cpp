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

	int low = 1, high = x/2; // Confirmed, high cannot be > x/2 for x > 1

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

// GFG has a cleaner implementation
// A C++ program to find floor(sqrt(x)
// Returns floor of square root of x
int floorSqrt(int x)
{
	// Base cases
	if (x == 0 || x == 1)
	return x;

	// Do Binary Search for floor(sqrt(x))
	int start = 1, end = x, ans;
	while (start <= end)
	{
		int mid = (start + end) / 2;

		// If x is a perfect square
		if (mid*mid == x)
			return mid;

		// Since we need floor, we update answer when mid*mid is
		// smaller than x, and move closer to sqrt(x)
		if (mid*mid < x)
		{
			start = mid + 1;
			ans = mid;
		}
		else // If mid*mid is greater than x
			end = mid-1;
	}
	return ans;
}


int main() {
	
	std::vector<int> inputs(1000);
	std::iota(std::begin(inputs), std::end(inputs), 0);
	
	for(const auto input : inputs) {
	    const int expected = static_cast<int>(sqrt(input));
	    const int actual = mySqrt(input); // or floorSqrt(input)
	    
	    if(expected != actual){
	        std::cout << input << " - " << expected  << " : " << actual << '\n';
	    }	
	}
}
