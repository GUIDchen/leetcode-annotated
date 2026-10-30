// 题目：42. 接雨水（Trapping Rain Water）
// 核心思路：分别求出每个位置左侧（含自身）与右侧（含自身）的最高柱子，再逐格取两侧较小者减去本柱高度累加，即每格的积水量。
// 时间复杂度：O(n)，只做常数次线性扫描；空间复杂度：O(n)，需要 left、right 两个前缀/后缀最大值数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int trap(vector<int>& height) {  // height 是每根柱子的高度，返回能接住的雨水总量
        int n = height.size();  // 柱子个数
        int left[n], right[n];  // left[i]：i 及其左侧的最大高度；right[i]：i 及其右侧的最大高度
        left[0] = height[0];  // 最左边的柱子左侧没有别的柱子，前缀最大值就是它自己
        right[n - 1] = height[n - 1];  // 最右边柱子右侧没有别的柱子，后缀最大值就是它自己
        for (int i = 1; i < n; ++i) {  // 从第二个位置开始，向右递推前缀最大值
            left[i] = max(left[i - 1], height[i]);  // 前缀最大值 = 上一个前缀最大值与本柱高度取较大者
            right[n - i - 1] = max(right[n - i], height[n - i - 1]);  // 同一轮循环里从右往左递推后缀最大值，省掉一次循环
        }
        int ans = 0;  // 累计接住的雨水量
        for (int i = 0; i < n; ++i) {  // 逐个位置统计它能存住多少水
            ans += min(left[i], right[i]) - height[i];  // 木桶效应：水位由左右最高柱中较矮者决定，减去本柱高度就是这一格的积水
        }
        return ans;  // 返回总积水量
    }
};
