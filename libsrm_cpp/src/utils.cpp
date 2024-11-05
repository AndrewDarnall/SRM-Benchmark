/**
 * This module contains the implementation of utility functions used in the Algorithm
 *
 */
#include <algorithm>
#include <climits>
#include <cmath>
#include <numeric>

#include "../include/libsrm_cpp/utils.hpp"


/**
 * findMax: Finds the maximum element in a given array of numbers
 * @param std::vector<int>& numbers: An array of positive valued integers
 */
int findMax(const std::vector<int>& numbers) {
    return std::accumulate(
        numbers.begin(), numbers.end(), INT_MIN, [](int maxNum, int num)
        {
            return std::max(maxNum, num);
        }
    );
}


/**
 * radixSort: Sorts a given array of positive integers based on their radix
 * @param std::vector<int>& v: the array of positive integers
 * @param int numDigits: the highest ammount of digits
 */
void radixSort(std::vector<int>& v, int numDigits) {
    std::vector<std::vector<int>> buckets;
    buckets.resize(10);
    for (int iteration = 0; iteration < numDigits; ++iteration) {
        // Copy items from vector into the appropriate buckets
        for (int i = 0; i < v.size(); ++i) {
            int digit = (v[i] / int(std::pow(10, iteration)) % 10);
            buckets[digit].push_back(v[i]);
        }
        // Copy everything from buckets back into vector in the appropriate order
        int i = 0;
        for (int bucket = 0; bucket < buckets.size(); ++bucket) {
            for (int item = 0; item < buckets[bucket].size(); ++item) {
                v[i] = buckets[bucket][item];
                ++i;
            }
            buckets[bucket].clear();
        }
    }
}

/**
 * radixSort: A wrapper for the actual radixSort function
 * @param std::vector<int>& v: the array of values to be sorted
 */
void radixSort(std::vector<int>& v) {
    int maxNum = 0;
    maxNum = findMax(v);
    int numDigits = int(std::log10(maxNum) + 1);
    radixSort(v, numDigits);
}
