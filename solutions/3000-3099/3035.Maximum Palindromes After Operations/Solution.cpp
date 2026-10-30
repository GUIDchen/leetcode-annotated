// 题目：3035. 回文字符串的最大数量（Maximum Palindromes After Operations）
// 思路：字符可自由交换，先统计总字符数 s 与各字母出现次数的奇偶性，凑成对子后按单词长度升序贪心地依次拼成回文。
// 时间复杂度：O(L + k log k)，L 为字符总数、k 为单词数；空间复杂度：O(k)，用于排序与位掩码等常数级额外空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxPalindromesAfterOperations(vector<string>& words) {  // words：可以任意交换字符的单词列表
        int s = 0, mask = 0;  // s 统计字符总数；mask 的第 i 位记录字母 i 出现次数的奇偶性
        for (const auto& w : words) {  // 遍历所有单词
            s += w.length();  // 累加字符总数
            for (char c : w) {  // 遍历单词中的每个字符
                mask ^= 1 << (c - 'a');  // 异或翻转对应字母的奇偶位：出现奇数次则置位，偶数次则清零
            }
        }
        s -= __builtin_popcount(mask);  // 出现奇数次的字母各要留下一个做中位，剩下的字符两两成对
        sort(words.begin(), words.end(), [](const string& a, const string& b) { return a.length() < b.length(); });  // 按长度升序排序，短单词更容易用少量字符对凑成回文
        int ans = 0;  // 记录能拼成的回文单词个数
        for (const auto& w : words) {  // 从短到长贪心地尝试每个单词
            s -= w.length() / 2 * 2;  // 该单词需要消耗的字符数：偶数长度全用对子，奇数长度保留一个中位字符
            if (s < 0) {  // 可用字符不够了
                break;  // 后面的单词只会更长，直接结束
            }
            ++ans;  // 当前单词可以拼成回文，计数加一
        }
        return ans;  // 返回最多能拼成的回文单词数
    }
};