/*
 * Given two words (start and end), and a dictionary, find the length of shortest transformation sequence
from start to end, such that:
- Only one letter can be changed at a time
- Each intermediate word must exist in the dictionary
For example, Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]
As one shortest transformation is hit -> hot -> dot -> dog -> cog, return its length 5.
Note:
- Return 0 if there is no such transformation sequence.
- All words have the same length.
- All words contain only lowercase alphabetic characters.
 *
 * Similar to Word Transformer in CTCI page 602
 * */
#include <print.h>

#include <algorithm>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <unordered_set>

/**
 * As suggested in CTCI, an optimization could be to pre-calculate the one word transforms for a given word.
 * The below function does it at run-time.
 *
 */
 std::unordered_set<std::string> generateOneWordTransforms(std::unordered_set<std::string>* wordsSeenPtr, const std::string& word) {
	std::unordered_set<std::string> res;

	for(char c = 'a'; c <= 'z'; c += 1) {
		for(size_t i = 0; i < word.size(); ++i) {
			if(c != word[i]) {
				std::string nextWord = word;
				nextWord[i] = c;
				// Alternately,
//				std::stringstream ss = word.substr(0, i) << c << word.substr(i + 1);
//				nextWord = ss.str();
				if(wordsSeenPtr->find(nextWord) == wordsSeenPtr->end()) {
					res.insert(nextWord);
					wordsSeenPtr->insert(nextWord);
				}

				/*
				 * Instead of maintaining wordsSeen, another approach could be to delete a word from dict, if it exists and has been seen once.
				 * That way dict can be used for two purposes, but needs to be editable.
				 * */
			}
		}
	}
	return res;
}
/*
 * BFS preferred for shortest path to target node
N = number of characters in word
Time complexity:
O(N) to go through all N words in the dictionary that are 1 character away from the starting word
Corresponds to full graph traversal.
Space: 2 lists created internally - could be O(N) wide if all one word differences are in dictionary
generateOneWordTransforms() - Alphabet size * N time and space
So total O(N) time and space.
 *
 *
 * Another approach is parallel BFS. Implementation here, in second code snippet
 * https://leetcode.com/problems/word-ladder/discuss/40707/Easy-76ms-C%2B%2B-Solution-using-BFS
 * */
int getLengthOfShortestTransform(const std::string& startWord, const std::string& endWord, const std::unordered_set<std::string>& dict) {
	if(startWord.size() != endWord.size()) {
		throw std::runtime_error("Input sizes are unequal");
	}

	std::list<std::string> curWords{startWord};
	std::unordered_set<std::string> wordsSeen{startWord};
	int pathLen = 1;

	while(!curWords.empty()) {
	//	printContainer(curWords);
		std::list<std::string> newCurWords{};
		++pathLen;
		for(const auto& word : curWords) {
			// Generate all potential next nodes in the graph
			const auto& newWords = generateOneWordTransforms(&wordsSeen, word);
			// If one of them is the end word, we're done
			if(newWords.find(endWord) != newWords.end()) {
				return pathLen;
			}
			// Only consider dictionary words as valid next nodes to traverse
			// Copy those into newCurWords
			std::copy_if(std::cbegin(newWords), std::cend(newWords), std::back_inserter(newCurWords), [&dict](const std::string& str){return dict.find(str) != dict.end();});

			// Another approach would be to modify getOneWordTransforms() to check whether a word is a valid dictionary word
			// startWord and endWord aren't in the dictionary. startWord doesn't need to be checked, only endWord needs to be checked, so
			// the check for a dictionary word should be whether its in the dictionary or if it's the end word.
			// That way getOneWordTransforms() would only return dictionary words.
		}
		curWords = newCurWords;
	}

	return 0;
}

int main() {
	try {
		const std::string startWord = "hit", endWord = "cog";
		const std::unordered_set<std::string> dict{"hot","dot","dog","lot","log"};
		std::cout << getLengthOfShortestTransform(startWord, endWord, dict);
	} catch(const std::exception& e) {
		std::cerr << "Exception in main(): " << e.what() << '\n';
	} catch(...) {
		return -1;
	}
}
