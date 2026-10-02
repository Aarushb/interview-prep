/*
PROBLEM: Group Anagrams
DESCRIPTION: Given an array of strings strs, group the anagrams together. You can return the answer in any order.
An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.
CONSTRAINTS:
- 1 <= strs.length <= 10^4
- 0 <= strs[i].length <= 100
- strs[i] consists of lowercase English letters.
EXAMPLE INPUT/OUTPUT:
Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

Input: strs = [""]
Output: [[""]]

Input: strs = ["a"]
Output: [["a"]]
*/

/*
APPROACH:
Anagrams share the same letters, just rearranged, so if I sort each string's characters I get a
canonical signature that's identical for every anagram of it. I use that sorted string as a hash
map key and push each original string into the bucket for its signature. After processing every
string, the map's values are exactly the groups I need. This fits the hashing pattern because
grouping by an equivalence relation is best done by normalizing each item to a shared key.
*/

#include <bits/stdc++.h>
using namespace std;

/*
SOLUTION APPROACH:

The key insight is: Anagrams have the same characters, just in different order.
So if we sort the characters of each word, anagrams will produce the same sorted string!

Example: "eat", "tea", "ate" all become "aet" when sorted

APPROACH 1: Sorting as Key (Most Common)
- For each string, create a "signature" by sorting its characters
- Use this sorted string as the key in hash map
- All anagrams will map to the same key
- Time: O(n * k log k) where n = number of strings, k = average string length
- Space: O(n * k)

APPROACH 2: Character Count as Key (More Optimal)
- Instead of sorting, count frequency of each character
- Use frequency array as key: "aabbcc" → "a2b2c2"
- Time: O(n * k) - no sorting needed
- Space: O(n * k)

TRICK:
We use unordered_map<string, vector<string>> where:
- Key = sorted string (signature)
- Value = list of all original strings with that signature

Since we only care about grouping, the order of groups doesn't matter.
*/

class Solution {
public:
    // Approach 1: Using sorted string as key
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        
        for (string& str : strs) {
            // Create signature by sorting the string
            string key = str;
            sort(key.begin(), key.end());
            
            // Add original string to the group with this signature
            groups[key].push_back(str);
        }
        
        // Extract all groups into result
        vector<vector<string>> result;
        for (auto& [key, group] : groups) {
            result.push_back(group);
        }
        
        return result;
    }
    
    // Approach 2: Using character frequency as key (More optimal)
    vector<vector<string>> groupAnagramsOptimized(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        
        for (string& str : strs) {
            // Create frequency signature
            string key = getFrequencyKey(str);
            groups[key].push_back(str);
        }
        
        vector<vector<string>> result;
        for (auto& [key, group] : groups) {
            result.push_back(group);
        }
        
        return result;
    }
    
private:
    // Generate key based on character frequency
    // Example: "aabbcc" → "a2b2c2" or "#2#2#2#0#0..." (26 positions)
    string getFrequencyKey(const string& str) {
        vector<int> count(26, 0);
        
        for (char c : str) {
            count[c - 'a']++;
        }
        
        // Build key from frequency array
        string key = "";
        for (int i = 0; i < 26; i++) {
            key += "#";
            key += to_string(count[i]);
        }
        
        return key;
    }
};

void printResult(vector<vector<string>>& result) {
    cout << "[";
    for (int i = 0; i < result.size(); i++) {
        cout << "[";
        for (int j = 0; j < result[i].size(); j++) {
            cout << "\"" << result[i][j] << "\"";
            if (j < result[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < result.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution sol;
    
    // Test Case 1
    vector<string> strs1 = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> result1 = sol.groupAnagrams(strs1);
    cout << "Test 1 (Sorting): ";
    printResult(result1);
    // Expected (any order, since unordered_map iteration order is unspecified): 3 groups -- {"bat"}, {"tan","nat"}, {"eat","tea","ate"}
    
    // Test Case 2 - Empty string
    vector<string> strs2 = {""};
    vector<vector<string>> result2 = sol.groupAnagrams(strs2);
    cout << "Test 2: ";
    printResult(result2);
    // Expected: [[""]]
    
    // Test Case 3 - Single character
    vector<string> strs3 = {"a"};
    vector<vector<string>> result3 = sol.groupAnagrams(strs3);
    cout << "Test 3: ";
    printResult(result3);
    // Expected: [["a"]]
    
    // Test Case 4 - All same anagrams
    vector<string> strs4 = {"abc", "bca", "cab", "bac"};
    vector<vector<string>> result4 = sol.groupAnagrams(strs4);
    cout << "Test 4: ";
    printResult(result4);
    // Expected: [["abc","bca","cab","bac"]]
    
    // Test Case 5 - Using optimized version
    cout << "\n=== Using Optimized (Frequency-based) ===" << endl;
    vector<string> strs5 = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> result5 = sol.groupAnagramsOptimized(strs5);
    cout << "Test 5 (Frequency): ";
    printResult(result5);
    
    return 0;
}
