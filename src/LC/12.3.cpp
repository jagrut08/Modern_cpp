/*
 * 12.3
Best Time to Buy and Sell Stock
Say you have an array for which the i-th element is the price of a given stock on day i.
If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.
 * */

#include <print.h>

#include <iostream>
#include <sstream>
#include <vector>


int maxProfit(const std::vector<int>& v) {
    if(v.empty()) {
        throw std::runtime_error("Empty input");
    }
    int maxProfit = 0, minSeen = v[0], maxSeen = v[0], minIdx = 0, maxIdx = 0;

    for(int i = 0; i < v.size(); ++i) {
        const int val = v[i];
        if(val < minSeen) {
            minSeen = val;
            minIdx = i;
        } else if(val >= maxSeen) { // For {10, 2, 10} => 8 case
            maxSeen = val;
            maxIdx = i;
        }

        if(maxIdx > minIdx) {
            maxProfit = std::max(maxProfit, maxSeen - minSeen);
        }
    }
    return maxProfit;
}

/*
Above code fails for {7, 1, 5, 3, 6, 4} - we don't need to maintain maxSeen, rather it should be maxProfit calculated 
for each point in the array. LC Article: https://leetcode.com/articles/best-time-to-buy-and-sell-stock/ */


int main() {
    const std::vector<std::vector<int>> inputs = {
      /*  {10, 3, 20, 2, 11}, // => 17
        {2, 10, 20}, // => 18
        {20, 10, 2}, // => 0
        {10, 20, 2}, // => 10
        {10, 20, 2, 7}, // => 10
        {3, 4, 5, 1, 6}, // => 5
        {2}, // => 0
        {2, 10}, // => 8
        {10, 2}, // => 0
        {2, 2, 2}, // => 0
        {10, 2, 10}, // => 8
        {10, 10, 2}, // => 0
        {7, 1, 5, 3, 6, 4}, // => 5
        */
    };
    for(const auto& input : inputs) {
        printContainer(input);
        std::cout << maxProfit(input) << '\n';
    }
}

