// 题目：740. 删除并获得点数（Delete and Earn）
// 思路：先把相同数值的点数聚合到值域桶里，问题就变成「选数值 x 就不能选 x-1、x+1」，即值域上的打家劫舍 DP。
// 时间复杂度：O(n + V)，V 为值域上界（这里固定取 10010）；空间复杂度：O(V)，值域桶数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int deleteAndEarn(vector<int>& nums) {  // nums：给定的整数数组，返回能获得的最大点数
        vector<int> vals(10010);  // 值域桶：下标即点数值，桶里存「选中该数值能一次性拿到的总分」
        for (int& num : nums) {  // 遍历每个数
            vals[num] += num;  // 把当前数值累加到它对应的桶里（同值的数可以一次全拿走）
        }  // 结束 for
        return rob(vals);  // 值域桶上做「相邻不能同时选」的 DP
    }  // 结束 deleteAndEarn

    int rob(vector<int>& nums) {  // 打家劫舍式 DP：相邻两项不能同时选，返回最大值
        int a = 0, b = nums[0];  // a 表示「不选前一项」的最优值，b 表示「考虑前一项」的最优值；初值取下标 0
        for (int i = 1; i < nums.size(); ++i) {  // 从下标 1 开始向后推进
            int c = max(nums[i] + a, b);  // 两种决策取大：选 nums[i] 则加上隔一项的 a，不选则沿用 b
            a = b;  // 滚动：a 前进到上一轮的 b
            b = c;  // 滚动：b 更新为当前最优值
        }  // 结束 for
        return b;  // 扫完全部后 b 即最大值
    }  // 结束 rob
};  // 结束 Solution 类