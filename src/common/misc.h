/*
 * misc.h
 * Miscellaneous helper routines.
 */

#ifndef SRC_COMMON_MISC_H_
#define SRC_COMMON_MISC_H_

#include <vector>
#include <unordered_map>

template <typename T>
std::unordered_map<T, int> createFreqTableFromVector(const std::vector<T>& v);

template <typename T>
void printFreqTable(const std::unordered_map<T, int> table);

#endif /* SRC_COMMON_MISC_H_ */
