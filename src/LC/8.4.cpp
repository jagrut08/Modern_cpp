/*
 * 8.4.cpp
 *
 * Find unique permutations given an input vector with duplicate elements
 */

#include <misc.h>
#include <print.h>
#include <iostream>
#include <unordered_map>
#include <vector>

void getUniquePermsHelper(std::vector<std::vector<int>>& res, std::vector<int>& cur,
	std::unordered_map<int, int>& freqTable, const size_t n) {
	if(cur.size() == n) {
		res.emplace_back(cur);
		return;
	}

	for(auto iter = freqTable.begin(); iter != freqTable.end(); ++iter) {
		if(iter->second > 0) {
			--(iter->second);
			cur.emplace_back(iter->first);
			getUniquePermsHelper(res, cur, freqTable, n);
			cur.pop_back();
			++(iter->second);
		}
	}
}

void getUniquePerms(const std::vector<int>& v) {

	auto freqTable = createFreqTableFromVector<int>(v);
	std::vector<std::vector<int>> res;
	std::vector<int> cur;

	getUniquePermsHelper(res, cur, freqTable, v.size());
	printContainer(res);
	std::cout << "--------\n";

}

/*

int main() {

	const std::vector<std::vector<int>> v{
		{},
		{1, 2},
		{1, 2, 3},
		{1, 1},
		{1, 1, 2},
		{1, 1, 2, 2},
	};
	std::for_each(v.begin(), v.end(), getUniquePerms);
}
*/


