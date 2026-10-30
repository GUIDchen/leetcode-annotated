# 题目：135. 分发糖果（Candy）
# 思路：贪心两遍扫描。先从左往右满足“比左邻分高则多一颗”，再从右往左满足“比右邻分高则多一颗”，每个位置取两个方向的较大值。
# 时间复杂度：O(n)，两次线性扫描加一次求和；空间复杂度：O(n)，两个辅助数组。
class Solution:  # LeetCode 约定的题解类
    def candy(self, ratings: List[int]) -> int:  # 返回最少糖果总数
        n = len(ratings)  # n 是孩子数量
        left = [1] * n  # left[i]：只看左邻居约束时，第 i 个孩子至少需要的糖数
        right = [1] * n  # right[i]：只看右邻居约束时，第 i 个孩子至少需要的糖数
        for i in range(1, n):  # 从左往右扫描，处理“比左邻分高”的情形
            if ratings[i] > ratings[i - 1]:  # 比左邻分高就要比左邻多拿
                left[i] = left[i - 1] + 1  # 在左邻基础上加一颗
        for i in range(n - 2, -1, -1):  # 从右往左扫描，处理“比右邻分高”的情形
            if ratings[i] > ratings[i + 1]:  # 比右邻分高就要比右邻多拿
                right[i] = right[i + 1] + 1  # 在右邻基础上加一颗
        return sum(max(a, b) for a, b in zip(left, right))  # 两个方向的约束同时满足，逐个位置取较大值后求和
