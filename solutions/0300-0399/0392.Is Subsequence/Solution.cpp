// 题目：392. 判断子序列（Is Subsequence）
// 思路：双指针，i 扫 s、j 扫 t，字符相同时 i 前进，j 始终前进，最后看 i 是否走完 s。
// 时间复杂度：O(m + n)，两个串各扫一遍；空间复杂度：O(1)，只用了两个指针。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isSubsequence(string s, string t) {  // s 是待判断的子序列，t 是原字符串
        int m = s.size(), n = t.size();  // 先取两个串的长度，避免循环里反复调用 size
        int i = 0, j = 0;  // i 指向 s 已匹配的位置，j 指向 t 当前字符
        for (; i < m && j < n; ++j) {  // j 每轮都前进；i 只在匹配成功时前进
            if (s[i] == t[j]) {  // 两个字符相同，匹配成功
                ++i;  // 匹配长度加一，s 的指针后移
            }
        }
        return i == m;  // i 走到 m 说明 s 的全部字符都按顺序匹配完
    }
};