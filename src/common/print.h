/*
 * print.h
 * Routines to pretty print sequential containers
 */

#ifndef SRC_COMMON_PRINT_H_
#define SRC_COMMON_PRINT_H_

#include <vector>

template <typename T>
void printVector(const std::vector<T>& v);

template <typename T>
void printVectorOfVectors(const std::vector<std::vector<T>>& v);

#endif /* SRC_COMMON_PRINT_H_ */
