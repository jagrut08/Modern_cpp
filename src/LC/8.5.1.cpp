/*
 * 8.5.1.cpp
 *
 * Given two integers n and k, return all possible combinations of k numbers out of 1:::n.
For example, If n = 4 and k = 2, a solution is:
[
[2,4],
[3,4],
[2,3],
[1,2],
[1,3],
[1,4],
]
*/
#include <print.h>

#include <stdexcept>
#include <utility>
#include <vector>

void getCombHelper(std::vector<std::vector<int>>* res, std::vector<int>* curRes, const int n, const int k, const int ctr) {
	if(!res || !curRes || ctr > n + 1 || ctr <= 0) {
		throw std::runtime_error("Invalid inputs in helper");
	}

	if(k == curRes->size()) {
		res->emplace_back(*curRes);
		return;
	}

	for(int i = ctr; i <= n; ++i) {
		curRes->emplace_back(i);
		getCombHelper(res, curRes, n, k, i + 1);
		curRes->pop_back();
	}

}
/*
 * Backtracking solution. Similar to https://leetcode.com/problems/combinations/discuss/27002/Backtracking-Solution-Java
 * O(N!) time and space, as there are N! combinations
 *
 * */
std::vector<std::vector<int>> getCombinations(const int n, const int k) {
	if(n <= 0 || k <= 0 || k > n) {
		throw std::runtime_error("Invalid inputs");
	}

	std::vector<std::vector<int>> res;
	std::vector<int> curRes;
	getCombHelper(&res, &curRes, n, k, 1);
	return res;
}

/*
 * Iterative solution from https://leetcode.com/problems/combinations/discuss/26992/Short-Iterative-C++-Answer-8ms
 * with debug statements for understanding
 * */

std::vector<std::vector<int>> combine(int n, int k) {
		std::vector<std::vector<int>> result;
		int i = 0;
		std::vector<int> p(k, 0);
		while (i >= 0) {
			p[i]++;
			std::cout << "Incremented p[" << i << "] to " << p[i] << '\n';
			if (p[i] > n) {
				--i;
				std::cout << "Decremented i to " << i << '\n';

			}
			else if (i == k - 1) {
				result.push_back(p);
				std::cout << "Added to result:\n";
				printContainer(p);
				std::cout << '\n';
			}
			else {
			    ++i;
			    std::cout << "Incremented i to " << i << '\n';
			    p[i] = p[i - 1];
			    std::cout << "p[i] = p[i - 1]. p looks as follows:\n";
			    printContainer(p);
			    std::cout << '\n';
			}
		}
		return result;
	}
int main() {

	try {
		std::vector<std::pair<int, int>> inputs {
			std::make_pair(3, 2),
			std::make_pair(4, 2),
			std::make_pair(3, 3),
			std::make_pair(3, 1),
		//	std::make_pair(3, -4),
			std::make_pair(5, 2),
		};

		for(const auto& p : inputs) {
			const auto& combs = getCombinations(p.first, p.second);
	//		const auto& combs = combine(p.first, p.second);

			std::cout << "For " << p.first << ", " << p.second << '\n';
			printContainer(combs);
		}
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	} catch(...) {
		return -1;
	}
}
