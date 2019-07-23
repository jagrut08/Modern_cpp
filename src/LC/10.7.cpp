/* Combination sum
 * Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T. The same repeated number may be chosen from C unlimited number of times.Note:
• All numbers (including target) will be positive integers.
• Elements in a combination (a1, a2, ..., ak) must be in non-descending order. (ie, a1 > a2 > ... > ak).
• The solution set must not contain duplicate combinations.
For example, given candidate set 2,3,6,7 and target 7, A solution set is:
[7]
[2, 2, 3]
 * */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

#include <print.h>

void combinationSumHelper(std::vector<int>* curCombPtr, std::vector<std::vector<int>>* resPtr, const int curSum,
        const int idx, const std::vector<int>& candidates, const int target) {
    if(!curCombPtr || !resPtr) {
        throw std::runtime_error("Unexpected input");
    }
    if(curSum == target) {
        resPtr->emplace_back(*curCombPtr);
    } else if (curSum < target) {
        for(int i = idx; i < candidates.size(); ++i) {
            if(curSum + candidates[i] > target) {
                break;
            }
            curCombPtr->emplace_back(candidates[i]);
            combinationSumHelper(curCombPtr, resPtr, curSum + candidates[i], i, candidates, target);
            curCombPtr->pop_back();
        }
    }
}

std::vector<std::vector<int>> combinationSum(std::vector<int> combs, const int target) {
    if(combs.empty()) {
        throw std::runtime_error("Invalid input combs");
    }
    std::sort(std::begin(combs), std::end(combs));
    std::vector<std::vector<int>> res;
    std::vector<int> curComb;
    combinationSumHelper(&curComb, &res, 0, 0, combs, target);
    return res;
}

int main() {

    std::vector<std::vector<int>> inputs = {
            {2, 3, 6, 7},
           // {},
            {10, 11, 12, 13},
            {1, 2, 3}
    };

    const int target = 7;

    for(const auto& input: inputs) {
        const auto& res = combinationSum(input, target);
        printContainer(input);
        std::cout << "Results are: \n";
        printContainer(res);
    }
}
