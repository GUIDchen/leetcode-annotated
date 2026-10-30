// 题目：2207. 字符串中最多数目的子序列（Maximize Number of Subsequences in a String）
// 核心思路：先统计原串里已有的子序列数；插入 pattern[0] 最多能与右侧所有 pattern[1] 配对，
//           插入 pattern[1] 最多能与左侧所有 pattern[0] 配对，取两者较大值累加到答案。
// 时间复杂度：O(n)，只扫描一遍字符串；空间复杂度：O(1)，只用常数个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maximumSubsequenceCount(string text, string pattern) {  // text 是原串，pattern 是长度为 2 的目标子序列
        long long ans = 0;  // 记录原串中已经存在的 pattern 子序列个数
        int x = 0, y = 0;  // x 统计 pattern[0] 出现次数，y 统计 pattern[1] 出现次数
        for (char& c : text) {  // 从左到右扫描每个字符
            if (c == pattern[1]) {  // 当前字符是目标子序列的第二个字符
                ++y;  // 第二个字符的计数加一
                ans += x;  // 它能和此前出现的每个 pattern[0] 组成一个子序列
            }
            if (c == pattern[0]) {  // 当前字符是目标子序列的第一个字符
                ++x;  // 第一个字符的计数加一；放在第二次判断里才能兼容 pattern 两字符相同的情况
            }
        }
        ans += max(x, y);  // 插入的字符最多贡献另一侧同伴字符的总数，取较大者
        return ans;  // 返回最多能得到的子序列数目
    }
};
