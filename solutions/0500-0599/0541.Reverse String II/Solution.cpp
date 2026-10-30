// 题目：541. 反转字符串 II（Reverse String II）
// 思路：以 2k 为步长从头扫描，每个区间内只反转前 k 个字符；末尾不足 k 个时就把剩余全部反转（用 min 截断右端点）。
// 时间复杂度：O(n)，每个字符至多被移动一次；空间复杂度：O(1)，除返回值外只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string reverseStr(string s, int k) {  // s 是待处理的字符串，k 是每 2k 个字符中需要反转的前缀长度
        int n = s.size();  // n 为字符串长度，用作循环上界与右端点的截断
        for (int i = 0; i < n; i += 2 * k) {  // i 每轮前进 2k，即跳过一个「反转前 k 个」的区块
            reverse(s.begin() + i, s.begin() + min(i + k, n));  // 反转 [i, i+k)，右端点用 min(i+k, n) 截断：末段不足 k 个时只反转剩下的部分
        }
        return s;  // 返回原地修改后的字符串
    }
};