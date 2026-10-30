# 题目：2334. 元素值大于变化阈值的子数组（Subarray With Elements Greater Than Varying Threshold）
# 思路：元素按值从大到小依次「激活」，用并查集维护已激活的连续段长度；当激活值 v 满足 v > threshold // 段长 s 时，该段就是长度 s 的合法子数组。
# 时间复杂度：O(n log n)，主要是排序（并查集近似 O(1)）；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def validSubarraySize(self, nums: List[int], threshold: int) -> int:  # nums 为数组，threshold 为阈值；返回合法子数组长度或 -1
        def find(x):  # 内层函数：并查集查找，返回 x 所在集合的根
            if p[x] != x:  # 父节点不是自己，说明还没到根
                p[x] = find(p[x])  # 递归找根，并把 x 直接挂到根上（路径压缩）
            return p[x]  # 返回根节点

        def merge(a, b):  # 内层函数：合并 a、b 所在的两个连续段
            pa, pb = find(a), find(b)  # 分别求出两段的根
            if pa == pb:  # 根相同说明本就在同一段
                return  # 无需合并，直接返回
            p[pa] = pb  # 把 a 的根挂到 b 的根下面
            size[pb] += size[pa]  # 新段长度累加

        n = len(nums)  # 元素个数
        p = list(range(n))  # 并查集初始化：每个元素自成一棵树，父节点是自己
        size = [1] * n  # 每段初始长度为 1
        arr = sorted(zip(nums, range(n)), reverse=True)  # 把 (值, 下标) 按值从大到小排好
        vis = [False] * n  # 标记下标是否已激活
        for v, i in arr:  # 按值从大到小依次激活位置 i
            if i and vis[i - 1]:  # 左邻存在且已激活
                merge(i, i - 1)  # 与左邻合并成一段
            if i < n - 1 and vis[i + 1]:  # 右邻存在且已激活
                merge(i, i + 1)  # 与右邻合并成一段
            if v > threshold // size[find(i)]:  # 整数除法等价于 v * 段长 > threshold，且不会溢出
                return size[find(i)]  # 该段就是合法子数组，返回它的长度
            vis[i] = True  # 标记当前下标已激活
        return -1  # 全部激活完仍没找到，返回 -1
