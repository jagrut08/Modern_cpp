/*
 * 
 * Palindrome Partitioning
Given a string s, partition s such that every substring of the partition is a palindrome.
Return all possible palindrome partitioning of s.
For example, given s = "aab", Return
[
	["aa","b"],
	["a","a","b"]
]
 * 
 * */

#include <print.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

bool isPalindrome(const std::string& str) {
	if(str.empty()){
		return true;
	}
	int startIdx = 0, endIdx = str.size() - 1;

	while(startIdx <= endIdx) {
		if(str[startIdx] != str[endIdx]) {
			return false;
		}
		++startIdx;
		--endIdx;
	}
	return true;
}

void getPalPartitionHelper(std::vector<std::string>* curResPtr, std::vector<std::vector<std::string>>* resPtr, const std::string& str) {
 	if(str.empty()) {
 		resPtr->emplace_back(*curResPtr);
 		return;
 	}

 	for(size_t width = 1; width <= str.size(); ++width) {
 		const std::string& subStr = str.substr(0, width);
 		if(isPalindrome(subStr)) {
 			curResPtr->emplace_back(subStr);
 			getPalPartitionHelper(curResPtr, resPtr, str.substr(width));
 			curResPtr->pop_back();
 		}
 	}
 }


std::vector<std::vector<std::string>> getPalindromePartitions(const std::string& str) {
 	std::vector<std::vector<std::string>> res{};
 	std::vector<std::string> curRes{};

 	if(str.empty()) {
 		return res;
 	}

 	getPalPartitionHelper(&curRes, &res, str);
 	return res;
 }

int main() {
	try {
		const std::vector<std::string> inputs = {
				"aab",
				"aba",
				"aaa",
				"aaaa",
				" a",
				"agfgb"
		};

		for(const auto& input : inputs) {
			std::cout << input << ":" << '\n';
			printContainer(getPalindromePartitions(input));
			std::cout << '\n';
		}

	} catch(const std::exception& e) {
		std::cerr << "Exception in main(): " << e.what() << '\n';
	} catch(...) {
		return -999;
	}
}
