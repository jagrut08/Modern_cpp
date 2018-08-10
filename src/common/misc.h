/*
 * misc.h
 * Miscellaneous helper routines.
 */

#ifndef SRC_COMMON_MISC_H_
#define SRC_COMMON_MISC_H_

#include <unordered_map>

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

#endif /* SRC_COMMON_MISC_H_ */
