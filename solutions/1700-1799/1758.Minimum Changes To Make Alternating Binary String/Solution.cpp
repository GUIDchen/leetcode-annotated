// 题目：1758. 生成交替二进制字符串的最少操作数（Minimum Changes To Make Alternating Binary String）
// 思路：统计改成 "0101..." 需要改的位数 cnt，那么改成 "1010..." 需要 n - cnt 位，答案取两者较小值。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(string s) {  // s 是给定的二进制字符串
        int cnt = 0, n = s.size();  // cnt 统计按 "0101..." 模式需要翻转的位数，n 是串长
        for (int i = 0; i < n; ++i) cnt += s[i] != "01"[i & 1];  // 偶数位期望 '0'、奇数位期望 '1'，不一致则累加 1
        return min(cnt, n - cnt);  // "0101..." 与 "1010..." 两种方案取更小的修改次数
    }
};