// 题目：1392. 最长快乐前缀（Longest Happy Prefix）
// 思路：字符串哈希；预处理前缀哈希 h 与幂次 p，再从长到短枚举长度 l，用 O(1) 比较「前缀哈希」与「后缀哈希」，第一个相等就是最长快乐前缀。
// 时间复杂度：O(n)，预处理 O(n) 加枚举 O(n)；空间复杂度：O(n)，哈希数组与幂次数组。
typedef unsigned long long ULL;  // 定义无符号 64 位整数，靠自然溢出相当于对 2^64 取模，实现滚动哈希

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string longestPrefix(string s) {  // s：待求解的字符串
        int base = 131;  // 哈希进制，取质数 131 以减少冲突
        int n = s.size();  // 字符串长度
        ULL p[n + 10];  // p[i] 表示 base 的 i 次方，用来把前缀哈希按位数平移
        ULL h[n + 10];  // h[i] 表示前 i 个字符组成的字符串的哈希值
        p[0] = 1;  // base 的 0 次方等于 1
        h[0] = 0;  // 空串的哈希值定义为 0
        for (int i = 0; i < n; ++i) {  // 从左到右递推每个前缀的哈希
            p[i + 1] = p[i] * base;  // 递推幂次：p[i+1] = p[i] * base
            h[i + 1] = h[i] * base + s[i];  // 递推前缀哈希：把新字符接到末尾
        }  // 预处理循环结束
        for (int l = n - 1; l > 0; --l) {  // 从最长可能的长度开始枚举；长度必须小于 n 才是「真前缀」
            ULL prefix = h[l];  // 长度为 l 的前缀的哈希值
            ULL suffix = h[n] - h[n - l] * p[l];  // 长度为 l 的后缀的哈希值：用整体哈希减去前面部分再平移得到，无符号溢出等价于取模
            if (prefix == suffix) return s.substr(0, l);  // 前后缀哈希相等，找到最长快乐前缀，直接返回这段前缀
        }  // 枚举结束：说明没有哈希相等的长度
        return "";  // 不存在任何非空真前缀同时是后缀，返回空串
    }
};