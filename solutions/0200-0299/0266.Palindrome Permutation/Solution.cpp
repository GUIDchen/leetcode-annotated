// 题目：266. 回文排列（Palindrome Permutation）
// 思路：统计每个字符的出现次数，回文排列最多允许一个字符出现奇数次（放在正中间）。
// 时间复杂度：O(n)，扫两遍 26 个字母；空间复杂度：O(1)，计数数组固定 26 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法接口
    bool canPermutePalindrome(string s) {  // s 为待判定的字符串，返回它能否重排成回文
        vector<int> cnt(26);  // 26 个字母的出现次数，元素默认初始化为 0
        for (char& c : s) {  // 遍历字符串，逐字符累计次数
            ++cnt[c - 'a'];  // c - 'a' 把字母映射到 0..25 的下标
        }  // 字符计数结束
        int odd = 0;  // odd 记录出现奇数次的字符个数
        for (int x : cnt) {  // 逐个检查每个字母的计数
            odd += x & 1;  // x & 1 取最低位，为 1 说明是奇数次，累加到 odd
        }  // 计数遍历结束
        return odd < 2;  // 奇数次字符少于 2 个才能组成回文
    }  // 方法结束
};  // 类定义结束