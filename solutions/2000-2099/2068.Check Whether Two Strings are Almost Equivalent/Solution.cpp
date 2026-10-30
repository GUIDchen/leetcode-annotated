// 题目：2068. 检查两个字符串是否几乎相等（Check Whether Two Strings are Almost Equivalent）
// 思路：用一个长度 26 的计数数组做词频差，word1 的字母加一、word2 的字母减一，最后检查每个字母的差值绝对值是否都不超过 3。
// 时间复杂度：O(n + 26)，n 为字符串长度；空间复杂度：O(26) = O(1)，只用了固定大小的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkAlmostEquivalent(string word1, string word2) {  // word1、word2 是两个待比较的字符串
        int cnt[26]{};  // 26 个字母的频次差，{} 保证全部初始化为 0
        for (char& c : word1) {  // 遍历 word1，逐个字母累加频次
            ++cnt[c - 'a'];  // 字符 c 对应的下标计数加 1
        }
        for (char& c : word2) {  // 遍历 word2，把它的字母频次从差值中减掉
            --cnt[c - 'a'];  // 字符 c 对应的下标计数减 1，最终得到频次差
        }
        for (int i = 0; i < 26; ++i) {  // 逐个检查每个字母在两串中的频次差
            if (abs(cnt[i]) > 3) {  // 差的绝对值超过 3，说明两串不满足「几乎相等」
                return false;  // 发现一个不合法的字母就可以直接返回 false
            }
        }
        return true;  // 所有字母的频次差都不超过 3，返回 true
    }
};