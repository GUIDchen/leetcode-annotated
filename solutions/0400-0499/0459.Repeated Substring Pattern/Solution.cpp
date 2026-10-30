// 题目：459. 重复的子字符串（Repeated Substring Pattern）
// 思路：把 s 拼成 s+s，从下标 1 开始查找 s；若匹配位置小于 len(s)，说明 s 是某个更短子串重复拼接而成。
// 时间复杂度：O(n^2)（标准 find 最坏为朴素匹配），n 为字符串长度；空间复杂度：O(n)（临时拼接的 s+s）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool repeatedSubstringPattern(string s) {  // s 是待判断的字符串，判断它能否由某个子串重复多次构成
        return (s + s).find(s, 1) < s.size();  // 在 s+s 中从下标 1 开始找 s：若在 len(s) 之前就匹配上，说明存在循环位移，即 s 由更短子串重复而成
    }
};