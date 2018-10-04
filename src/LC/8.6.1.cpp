/*
 * 8.6.1.cpp
 * Letter Combinations of a Phone Number
Given a digit string, return all possible letter combinations that the number could represent.
A mapping of digit to letters (just like on the telephone buttons) is given below.

Input:Digit string "23"
Output: [ad, ae, af, bd, be, bf, cd, ce, cf].
 *
 */
#include <print.h>

#include <algorithm>
#include <cctype> // isdigit
#include <exception>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

void getPhoneLettersHelper(std::vector<std::string>* res, std::string* curRes, const int idx, const std::string& str, const std::unordered_map<int, std::string>& keyMap) {
	if(!res || !curRes || idx < 0) {
		std::runtime_error("Invalid input");
	}

	if(idx >= str.size()) {
		res->emplace_back(*curRes);
		return;
	}

	const std::string& chars = keyMap.at(str[idx] - '0');
	for(const auto& c : chars) {
		curRes->push_back(c);
		getPhoneLettersHelper(res, curRes, idx + 1, str, keyMap);
		curRes->pop_back();
	}
}

/*
 * Time O(4^N) as for each digit in input, there are 4 chars at max. N is length of str.
 * Space O(4^N) combinations produced in output + O(N) stack frames due to recursive calls.
 *
 * */
std::vector<std::string> getPhoneLetters(const std::string& str, const std::unordered_map<int, std::string>& keyMap) {

		// Recommended way to use isdigit() on a std::string in an STL algo: https://en.cppreference.com/w/cpp/string/byte/isdigit
		const auto& iter = std::find_if(std::cbegin(str), std::cend(str), [](unsigned char c){return !std::isdigit(c);});
		if(iter != std::cend(str)) {
			throw std::runtime_error("Invalid chars in input");
		}

		std::vector<std::string> res;
		std::string curRes;
		getPhoneLettersHelper(&res, &curRes, 0, str, keyMap);
		return res;
}
/*
 * Iterative solution using queue.
 * Translated into C++ from
 * https://leetcode.com/problems/letter-combinations-of-a-phone-number/discuss/8064/My-java-solution-with-FIFO-queue
 *
 * */

std::list<std::string> getPhoneLettersIter(const std::string& str) {
	std::list<std::string> ans;
	if(str.empty()) {
		return ans;
	}

	std::vector<std::string> mapping {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
	ans.push_back("");

	for(size_t i = 0; i < str.size(); ++i){
		int x = str[i] - '0';
		/*
		 * While the size of the string at the head of the list (front of queue) is the same as index i
		 * remove head, combine it with all chars at index i in the mapping, and add the combinations back
		 * to the tail of the queue
		 * */

		while(ans.front().size() == i) {
			const std::string t = ans.front(); // should not be std::string& t as we pop right after
			ans.pop_front();
//			std::cout << "Removed " << t << '\n';

			for(const char c : mapping[x]) {
					ans.push_back(t + c);
	//				std::cout << "Added " << t + c << '\n';
			}
		//	printContainer(ans);

		}

	}
	return ans;
}

/*
 * Another solution with 2 for() loops from
 * https://leetcode.com/problems/letter-combinations-of-a-phone-number/discuss/8097/My-iterative-sollution-very-simple-under-15-lines
 * */

std::vector<std::string> getPhoneLettersIter2(std::string digits) {
	std::vector<std::string> res;
	std::vector<std::string> charmap {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    res.push_back("");
    for (int i = 0; i < digits.size(); i++)
    {
    	std::vector<std::string> tempres;
    	std::string chars = charmap[digits[i] - '0'];
        for (int c = 0; c < chars.size();c++)
            for (int j = 0; j < res.size();j++) {
                tempres.push_back(res[j]+chars[c]);
                std::cout << "Added " << res[j]+chars[c] << '\n';
            }
        printContainer(tempres);
        res = tempres;
    }
    return res;
}

/*
int main() {
	try {
		const std::vector<std::string> strs {
			"23",
			"234",
			"22",
			"1",
			"2",
			"",
			"79",
			"03",
			"rqwe" // Non digits
		};
		const std::unordered_map<int, std::string> keyMap = {
				{1, ""},
				{2, "abc"},
				{3, "def"},
				{4, "ghi"},
				{5, "jkl"},
				{6, "mno"},
				{7, "pqrs"},
				{8, "tuv"},
				{9, "wxyz"},
				{0, " "},
		};
		for(const auto& str : strs) {
		//	auto& res = getPhoneLetters(str, keyMap);
		//	auto& res = getPhoneLettersIter(str);
			auto& res = getPhoneLettersIter2(str);

			std::cout << "For str=" << str << '\n';
			printContainer(res);
			std::cout << '\n';
		}
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	} catch(...) {
		return -1;
	}
}
*/




