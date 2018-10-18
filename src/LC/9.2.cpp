/*
 *
Word Ladder II

Given two words (start and end), and a dictionary, find all shortest transformation sequence(s) from start
to end, such that:
• Only one letter can be changed at a time
• Each intermediate word must exist in the dictionary
For example, Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]
Return
[
["hit","hot","dot","dog","cog"],
["hit","hot","lot","log","cog"]
]
Note:
• All words have the same length.
• All words contain only lowercase alphabetic characters.
 */

#include <print.h>

#include <algorithm>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using MapType = std::unordered_map<std::string, std::string>;

std::vector<std::string> getPathToStartWord(const std::string& word, const MapType& childParentMap) {
	std::vector<std::string> res;
	std::string tmpWord = word; // Can't use std::string& tmpWord = word as tmpWord is non-const ref that refers to the const word. Compiler error.
	while(childParentMap.count(tmpWord)) {
		res.emplace_back(tmpWord);
		tmpWord = childParentMap.at(tmpWord);
	}
	// tmpWord is startWord as startWord hasn't been added to childParentMap
	res.emplace_back(tmpWord);
	return std::reverse(res); // Alternately, use a std::list and push_front, then iterate left to right to extract words.
}

std::vector<std::string> getWordsOneCharAway(const std::string& word, const std::unordered_set<std::string>& dict, const std::string& endWord, const MapType& childParentMap) {
	std::vector<std::string> res;

	for(char c = 'a'; c <= 'z'; ++c) {
		for(size_t i = 0; i < word.size(); ++i) {
			if(word[i] != c) {
				std::string newWord = word;
				newWord[i] = c;
				if((dict.count(newWord) || newWord == endWord) && !childParentMap.count(newWord)) {
					res.emplace_back(newWord);
				}
			}
		}
	}
	return res;
}
/*
Complexity
O(N) time and space, due to BFS
*/
std::vector<std::vector<std::string>> findShortestTransforms(const std::string& startWord, const std::string& endWord, const std::unordered_set<std::string>& dict) {
	if(startWord.size() != endWord.size()) {
		throw std::runtime_error("startWord and endWord are unequal in size");
	}

	std::list<std::string> curQueue{startWord};
	MapType childParentMap; // Will hold mapping from childWord -> its parent word and will also be used to check if a
					        // word has been seen before in the BFS
	std::vector<std::vector<std::string>> res;

	while(!curQueue.empty() && res.empty()) {
		std::list<std::string> nextQueue;
		for(const auto& word : curQueue) {
			const auto& nextWords = getWordsOneCharAway(word, dict, endWord, childParentMap);
			for(const auto& nextWord : nextWords) {
				childParentMap[nextWord] = word;
				nextQueue.emplace_back(nextWord);

				if(nextWord == endWord) {
					res.emplace_back(getPathToStartWord(nextWord, childParentMap));
				}
			}
		}
		curQueue = nextQueue;
	}

	return res;
}

int main() {
	try {
			const std::string& startWord = "hit", endWord = "cog";
			const std::unordered_set<std::string> dict {"hot","dot","dog","lot","log"};
			const auto& res = findShortestTransforms(startWord, endWord, dict);
			printContainer(res);

		} catch(const std::exception& e) {
			std::cerr << "Exception in main(): " << e.what() << '\n';
		} catch(...) {
			return -1;
		}
}