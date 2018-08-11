/*
 * misc.h
 * Miscellaneous helper routines.
 */

#ifndef SRC_COMMON_MISC_H_
#define SRC_COMMON_MISC_H_

#include <unordered_map>
#include <sstream>

template <typename T>
std::unordered_map<T, int> createFreqTableFromVector(const std::vector<T>& v) {
	std::unordered_map<T, int> res;
	for(const auto& elem : v){
		if(res.find(elem) == res.end()) {
			res[elem] = 0;
		}
		++res[elem];
	}
	return res;
}

template <typename T>
void printFreqTable(const std::unordered_map<T, int> table) {
	std::ostringstream ostr;
	ostr << "Frequency table is\n";

	// The recommended way to pass the <K,V> pairs of the map as per
	// https://stackoverflow.com/questions/17306715/lambda-signature-for-each-unordered-map

	// Also, the arg to the lambda is a dependent typename
	auto printLambda = [&ostr](const typename std::unordered_map<T, int>::value_type& p) {
		ostr << p.first << " : " << p.second << '\n';
	};

	std::for_each(table.cbegin(), table.cend(), printLambda);
	std::cout << ostr.str();
}

#endif /* SRC_COMMON_MISC_H_ */
