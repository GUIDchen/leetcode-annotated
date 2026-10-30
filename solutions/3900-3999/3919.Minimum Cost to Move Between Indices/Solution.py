# 题目：3919. 在下标间移动的最小代价（Minimum Cost to Move Between Indices）
# 思路：相邻下标之间要么照价付差值、要么借助 closest 只花 1，因此按「向右」「向左」两个方向各做一遍前缀和，查询时按 l < r 取对应的前缀差。
# 时间复杂度：O(n + m)，n 为数组长度、m 为查询数；空间复杂度：O(n)，两个前缀和数组。
class Solution:  # LeetCode 约定的题解类
    def minCost(self, nums: list[int], queries: list[list[int]]) -> list[int]:  # nums：严格递增数组；queries：每项是 [l, r]，返回每个查询的最小代价
        n = len(nums)  # 数组长度
        s1 = [0] * n  # s1[i]：从下标 0 向右走到 i 的最小累计代价
        s2 = [0] * n  # s2[i]：从下标 0 沿向左方向走到 i 的最小累计代价
        for i in range(1, n):  # 预处理每条相邻边（即 i-1 与 i 之间）的代价
            c1 = (  # 向右跨 (i-1)→i 的代价，先看下面第一个分支
                nums[i] - nums[i - 1]  # 照价付差值：closest(i-1) 不指向 i 时只能这样走
                if i > 1 and nums[i - 1] - nums[i - 2] <= nums[i] - nums[i - 1]  # 判断 i-1 的最近邻是左邻，于是向右一步不能借 closest 省成 1
                else 1  # 否则 closest(i-1) 就是 i，这一步只花 1
            )  # c1 计算结束
            c2 = (  # 向左跨 i→(i-1) 的代价，同样先看第一个分支
                nums[i] - nums[i - 1]  # 照价付差值：closest(i) 指向 i+1 时只能这样走
                if i < n - 1 and nums[i] - nums[i - 1] > nums[i + 1] - nums[i]  # 判断 i 的最近邻是右邻，于是向左一步不能借 closest 省成 1
                else 1  # 否则 closest(i) 就是 i-1，向左一步只花 1
            )  # c2 计算结束
            s1[i] = s1[i - 1] + c1  # 累加得到向右方向的前缀代价
            s2[i] = s2[i - 1] + c2  # 累加得到向左方向的前缀代价
        m = len(queries)  # 查询个数
        ans = [0] * m  # 存放每个查询的答案
        for i, (l, r) in enumerate(queries):  # 逐个查询，同时取出起点 l 与终点 r
            ans[i] = s1[r] - s1[l] if l < r else s2[l] - s2[r]  # l < r 时用向右的 s1 差分，否则用向左的 s2 差分
        return ans  # 返回全部答案
