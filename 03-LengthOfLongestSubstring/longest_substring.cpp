// /*QUESTION*/
// Given a string, find the length of the longest substring without repeating characters.
// Examples:
// Given "abcabcbb", the answer is "abc", which the length is 3.
// Given "bbbbb", the answer is "b", with the length++ of 1.
// Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring,
// "pwke" is a subsequence and not a substring.

//include
#include <string>
#include <iostream>
#include <math.h>

//define
#define max(a,b) a > b ? a : b

//namespace
using namespace std;

class Solution {
public:
    static int lengthOfLongestSubstring(string s) {
        int length = 0;
        int arrayAscii[128] = {0}; //保存每个字符最后出现的位置
        for( int index = 0,currentStartIndex = 0; index < s.length(); index++){
            currentStartIndex = max(arrayAscii[s.at(index)],currentStartIndex);
            length = max(length,index - currentStartIndex + 1);
            arrayAscii[s.at(index)] = index + 1;
        }
        return length;
    }
};

int main()
{
    //test case
    string sTest = "abcabcbb";
    std::cout<<"lengthOfLongestSubstring(\""<<sTest<<"\") = "<<Solution::lengthOfLongestSubstring(sTest)<<"\n";

    sTest = "bbbbb";
    std::cout<<"lengthOfLongestSubstring(\""<<sTest<<"\") = "<<Solution::lengthOfLongestSubstring(sTest)<<"\n";

    sTest = "pwwkew";
    std::cout<<"lengthOfLongestSubstring(\""<<sTest<<"\") = "<<Solution::lengthOfLongestSubstring(sTest)<<"\n";
    return 0;
}
