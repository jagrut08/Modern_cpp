/*
 * print.h
 */

#ifndef SRC_COMMON_PRINT_H_
#define SRC_COMMON_PRINT_H_

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

void printVector(const std::vector<int>& v) {
	if(v.empty()) {
		std::cout << "{} ";
		return;
	}
	size_t i = 0;
	std::cout << "{";
	std::for_each(v.cbegin(), v.cend(), [&i, &v](int val) {std::cout << val << (++i == v.size() ? "" : ", ");} );
	std::cout << "} ";
}


#endif /* SRC_COMMON_PRINT_H_ */
