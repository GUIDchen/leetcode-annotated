// 题目：2874. 有序三元组中的最大值 II（Maximum Value of an Ordered Triplet II）
// 思路：与 2873 相同的单次遍历：维护前缀最大值 mx 与最大差值 mxDiff，用 mxDiff * x 更新答案，避免 O(n^3) 暴力。
// 时间复杂度：O(n)，n 更大也只扫一遍；空间复杂度：O(1)，只用了三个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maximumTripletValue(vector<int>& nums) {  // nums 为输入数组；返回值用 long long 防止乘积溢出
        long long ans = 0, mxDiff = 0;  // ans 是当前最大三元组值；mxDiff 是下标 i<j 时 nums[i] - nums[j] 的最大值
        int mx = 0;  // 前缀最大值，即 max(nums[0..j])
        for (int x : nums) {  // 依次把 x 当作第三个下标 k 位置的元素
            ans = max(ans, mxDiff * x);  // 先用「之前的最佳差值 * 当前 x」尝试更新答案
            mxDiff = max(mxDiff, 1LL * mx - x);  // 再把 x 当作 j，用「前缀最大值 - x」更新最佳差值（1LL 保证按 64 位计算）
            mx = max(mx, x);  // 最后更新前缀最大值，供后面的元素使用
        }  // 遍历结束
        return ans;  // 返回最大三元组值（没有正收益时保持 0）
    }  // 方法结束
};  // 类定义结束
