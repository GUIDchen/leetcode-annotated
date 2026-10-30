// 题目：2750. 将数组划分成若干好子数组的方式（Ways to Split Array Into Good Subarrays）
// 思路：好子数组必须恰好包含一个 1；相邻两个 1 之间有 i-j 个可选切分位置，按乘法原理把它们累乘起来。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 公有成员：判题器直接调用下面的方法
    int numberOfGoodSubarraySplits(vector<int>& nums) {  // nums：只含 0/1 的数组；返回能划分成“好子数组”的方案数
        const int mod = 1e9 + 7;  // 模数，防止方案数溢出
        int ans = 1, j = -1;  // ans：方案数（乘法原理累乘）；j：上一个 1 的下标，-1 表示还没遇到 1
        for (int i = 0; i < nums.size(); ++i) {  // 从左到右扫描每个位置
            if (nums[i] == 0) {  // 0 不影响切分点位置，直接跳过
                continue;  // 跳过当前位置
            }  // 结束“遇到 0”分支
            if (j > -1) {  // 不是第一个 1，说明可以在与上一个 1 之间选择切分点
                ans = 1LL * ans * (i - j) % mod;  // 两个 1 之间有 i-j 个可选切分位置，按乘法原理累乘
            }  // 结束累乘分支
            j = i;  // 更新上一个 1 的位置
        }  // 结束扫描循环
        return j == -1 ? 0 : ans;  // 数组中没有 1 时无法分成好子数组，返回 0；否则返回累乘结果
    }  // 结束题解方法
// 结束题解类
};