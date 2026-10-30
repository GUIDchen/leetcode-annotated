# 题目：42. 接雨水（Trapping Rain Water）
# 核心思路：分别求出每个位置左侧（含自身）与右侧（含自身）的最高柱子，再逐格取两侧较小者减去本柱高度累加，即每格的积水量。
# 时间复杂度：O(n)，只做常数次线性扫描；空间复杂度：O(n)，需要 left、right 两个前缀/后缀最大值数组。
class Solution:  # LeetCode 约定的题解类
    def trap(self, height: List[int]) -> int:  # height 是每根柱子的高度，返回能接住的雨水总量
        n = len(height)  # 柱子个数
        left = [height[0]] * n  # 先全填成最左柱高度，left[i] 之后表示 i 左侧（含 i）的最大高度
        right = [height[-1]] * n  # 先全填成最右柱高度，right[i] 之后表示 i 右侧（含 i）的最大高度
        for i in range(1, n):  # 从第二个位置开始向右递推
            left[i] = max(left[i - 1], height[i])  # 前缀最大值 = 上一个前缀最大值与本柱高度取较大者
            right[n - i - 1] = max(right[n - i], height[n - i - 1])  # 同一轮里从右往左计算后缀最大值，省掉一次循环
        return sum(min(l, r) - h for l, r, h in zip(left, right, height))  # 逐格累加：水位取左右最高柱的较小者，再减去本柱高度
