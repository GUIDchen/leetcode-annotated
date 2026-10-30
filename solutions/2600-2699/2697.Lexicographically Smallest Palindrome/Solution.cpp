// 题目：2697. 字典序最小回文串（Lexicographically Smallest Palindrome）
// 核心思路：双指针从两端向中间夹逼，每对对称位置都改成两者中字典序更小的字符，这样既保证回文，又让整体字典序最小。
// 时间复杂度：O(n)，只遍历一半长度；空间复杂度：O(1) 额外空间，参数是值传递，直接原地修改副本。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string makeSmallestPalindrome(string s) {  // s：待改造的字符串（值传递，可以直接改）；返回字典序最小的回文串
        for (int i = 0, j = s.size() - 1; i < j; ++i, --j) {  // i 从左端出发、j 从右端出发相向而行，i < j 保证每对只处理一次
            s[i] = s[j] = min(s[i], s[j]);  // 对称的两个位置统一替换成较小的那个字符，字典序才能最小
        }
        return s;  // 改造后的回文串
    }
};