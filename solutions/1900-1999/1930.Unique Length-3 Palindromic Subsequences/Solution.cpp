// 题目：1930. 长度为 3 的不同回文子序列（Unique Length-3 Palindromic Subsequences）
// 思路：枚举 26 个小写字母作为回文两端，再统计两端之间出现过多少种不同的中间字符。
// 时间复杂度：O(26·n) 即 O(n)；空间复杂度：O(1)，只用一个 26 位的位掩码。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countPalindromicSubsequence(string s) {  // 返回长度为 3 的不同回文子序列个数
        int ans = 0;  // 答案计数器
        for (char c = 'a'; c <= 'z'; ++c) {  // 枚举回文子序列首尾两端使用的字符
            int l = s.find_first_of(c), r = s.find_last_of(c);  // l / r 分别是字符 c 第一次与最后一次出现的位置
            int mask = 0;  // 位掩码：记录两端之间已经出现过哪些字符
            for (int i = l + 1; i < r; ++i) {  // 枚举两端之间的每个位置作为回文中间的字符
                int j = s[i] - 'a';  // 把字符映射成 0..25 的位编号
                if (mask >> j & 1 ^ 1) {  // 先取出第 j 位再与 1 异或，等价于判断「该位仍为 0」，即这个中间字符还没统计过
                    mask |= 1 << j;  // 把第 j 位置 1，标记该中间字符已统计
                    ++ans;  // 得到一个全新的回文子序列
                }  // if 结束
            }  // for 结束
        }  // 外层 for 结束，26 个字符都枚举完
        return ans;  // 返回不同回文子序列的总数
    }  // 方法结束
};  // 类结束
