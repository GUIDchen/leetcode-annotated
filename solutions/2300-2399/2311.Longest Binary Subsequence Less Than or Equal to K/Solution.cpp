// 题目：2311. 小于等于 K 的最长二进制子序列（Longest Binary Subsequence Less Than or Equal to K）
// 思路：从低位向高位贪心扩展，末尾的 0 一定保留；1 只有在当前数值加上该位权重后仍不超过 k 时才保留。
// 时间复杂度：O(n)，n 为字符串长度，只遍历一遍；空间复杂度：O(1)，只用常数个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestSubsequence(string s, int k) {  // s 是二进制字符串，k 是上界，返回满足条件的最长子序列长度
        int ans = 0, v = 0;  // ans 是当前子序列长度，v 是它对应的数值
        for (int i = s.size() - 1; ~i; --i) {  // 从最低位向最高位遍历，~i 等价于 i >= 0
            if (s[i] == '0') {  // 0 放在最低位不增加数值，永远可以保留
                ++ans;  // 保留这个 0，长度加一
            } else if (ans < 30 && (v | 1 << ans) <= k) {  // 1 也只有保留才更优：ans < 30 防止 1 << ans 溢出，且加上该位后数值不能超过 k
                v |= 1 << ans;  // 把这一位的权重并入当前数值
                ++ans;  // 成功保留一个 1，长度加一
            }
        }
        return ans;  // 遍历结束，ans 就是最长子序列长度
    }
};  // 类定义结束，最后一个分号收尾