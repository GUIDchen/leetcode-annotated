// 题目：214. 最短回文串（Shortest Palindrome）
// 核心思路：用滚动哈希同时维护前缀的正向哈希与反向哈希，找出最长的回文前缀；把剩余后缀反转后拼到原串前面即为答案。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(n)，substr 与反转产生额外字符串。
typedef unsigned long long ull;  // 无符号 64 位整数别名：哈希值会很大，用 ull 避免溢出

class Solution {  // LeetCode 约定的题解类
public:  // 对外接口
    string shortestPalindrome(string s) {  // 在 s 前面补最少字符使其成为回文，返回该最短回文串
        int base = 131;  // 滚动哈希的进制，取大于字母表大小(26)的质数可减少碰撞
        ull mul = 1;  // 当前位的权重 base^i，用于从右往左累加反向哈希
        ull prefix = 0;  // 前缀的正向哈希（从左往右累积）
        ull suffix = 0;  // 前缀的反向哈希（相当于把该前缀反转后算正向哈希）
        int idx = 0, n = s.size();  // idx 记录最长的回文前缀长度；n 是串长
        for (int i = 0; i < n; ++i) {  // 从左往右扩展前缀，逐位判断当前前缀是否为回文
            int t = s[i] - 'a' + 1;  // 把字符映射到 1..26，避免 0 使不同串得到相同哈希
            prefix = prefix * base + t;  // 正向哈希：整体左移一位（乘进制）后接上当前字符
            suffix = suffix + mul * t;  // 反向哈希：当前字符乘上权重后追加到最右端
            mul *= base;  // 权重翻倍，供下一个字符使用
            if (prefix == suffix) idx = i + 1;  // 两个哈希相等说明 s[0..i] 是回文，更新最长回文前缀长度
        }  // 循环结束
        if (idx == n) return s;  // 整个串本身就是回文，不需要补任何字符
        string x = s.substr(idx, n - idx);  // 取出回文前缀之后、需要被镜像复制的那一段
        reverse(x.begin(), x.end());  // 反转它，作为要补到最前面的部分
        return x + s;  // 反转段接上原串，得到最短回文串
    }  // 方法结束
};  // 类定义结束