/*
 * print.cpp
 *
 */

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

#include "print.h"

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
