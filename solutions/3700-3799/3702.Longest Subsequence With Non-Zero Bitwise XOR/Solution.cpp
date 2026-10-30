// 题目：3702. 按位异或非零的最长子序列（Longest Subsequence With Non-Zero Bitwise XOR）
// 核心思路：先求全数组异或和：若不为 0，整个数组就是答案；若为 0 且存在非零元素，去掉任意一个非零元素即可让异或非零，答案为 n-1；若全是 0，则任何子序列异或都为 0，答案为 0。
// 复杂度：时间 O(n)，只扫一遍数组；空间 O(1)，只有几个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestSubsequence(vector<int>& nums) {  // 返回异或和非零的最长子序列长度
        int xor_ = 0, cnt0 = 0;  // xor_ 累计全体异或和，cnt0 统计 0 的个数
        int n = nums.size();  // 数组长度
        for (int x : nums) {  // 遍历数组的每个元素
            xor_ ^= x;  // 把当前元素异或进全体异或和
            cnt0 += x == 0 ? 1 : 0;  // 当前元素为 0 时让计数器加一
        }  // 结束遍历
        if (xor_ != 0) {  // 全体异或和已经非零，可以直接全选
            return n;  // 整段数组就是最长子序列
        }  // 结束第一种情形
        return cnt0 == n ? 0 : n - 1;  // 全是 0 时无解返回 0，否则去掉一个非零元素可得 n-1
    }  // 结束 longestSubsequence
};  // 结束题解类
