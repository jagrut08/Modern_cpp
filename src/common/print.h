/*
 * print.h
 * Routines to pretty print sequential containers
 */

#ifndef SRC_COMMON_PRINT_H_
#define SRC_COMMON_PRINT_H_

#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
void printVector(const std::vector<T>& v) {
	if(v.empty()) {
		std::cout << "{}\n";
		return;
	}
	size_t i = 0;
	std::cout << "{";
	std::for_each(v.cbegin(), v.cend(), [&i, &v](T val) {std::cout << val << (++i == v.size() ? "" : ", ");} );
	std::cout << "}\n";
}

template <typename T>
void printVectorOfVectors(const std::vector<std::vector<T>>& v) {
	std::for_each(v.begin(), v.end(), printVector<T>);
}

#endif /* SRC_COMMON_PRINT_H_ */
