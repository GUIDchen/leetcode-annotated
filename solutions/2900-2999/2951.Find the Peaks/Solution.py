# 题目：2951. 找出峰值（Find the Peaks）
# 思路：用列表推导式线性扫描下标 1..n-2，用链式比较同时判断是否严格大于左右两个邻居。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，除答案列表外只用常数变量。
class Solution:  # LeetCode 约定的题解类
    def findPeaks(self, mountain: List[int]) -> List[int]:  # mountain 是山脉数组；返回峰值下标组成的列表
        return [  # 用列表推导式一次性构造答案列表
            i  # 候选峰值下标
            for i in range(1, len(mountain) - 1)  # 首尾没有两个邻居，从下标 1 扫到 n-2
            if mountain[i - 1] < mountain[i] > mountain[i + 1]  # 链式比较：同时严格大于左右邻居才保留
        ]  # 推导式结束，返回构造好的列表
