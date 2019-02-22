/*
 * 
 * Implement pow(x, n)
 * */
#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

// O(log(n)) time and O(log(n)) space due to recursive calls
double myPowRecur(const double x, const int n) {
	if(n == 1) {
		return x;
	}

	double ans = myPowRecur(x, n/2);
	ans*= ans;
	return (n % 2 == 0 ? ans : ans * x);
}

double myPow(const double x, const int n) {
	if(n == 0) {
		return 1;
	}

	if(x == 0) {
		return 0;
	}

	double y = x;
	int z = n;

	if(n < 0) {
		y = 1/x;
		z*= -1;
	}

	return myPowRecur(y, z);
}

/*
int main() {
	try {
		const std::vector<std::pair<double, int>> inputs {
			std::make_pair(2, 4),
			std::make_pair(1.5, 2),
			std::make_pair(2, 0),
			std::make_pair(-2, 0),
			std::make_pair(2, 1),
			std::make_pair(-2, 1),
			std::make_pair(-2, 2),
			std::make_pair(-2, -2),
			std::make_pair(-2, -3),
			std::make_pair(2, 3),
			std::make_pair(2, -1),
			std::make_pair(0, 1),
//			std::make_pair(0, -1), pow() function returns inf
			std::make_pair(36, 22),
		};

		for(const auto& input : inputs) {
			const double ans = myPow(input.first, input.second);
			const double powAns = pow(input.first, input.second);
			std::cerr << input.first << "^"<< input.second << " = " << ans <<  " pow(): " << powAns << '\n';
			assert(ans == powAns);
		}
	} catch(const std::exception& e) {
		std::cerr << "Exception in main(): " << e.what() << '\n';
	} catch(...) {
		return -999;
	}
}
*/
