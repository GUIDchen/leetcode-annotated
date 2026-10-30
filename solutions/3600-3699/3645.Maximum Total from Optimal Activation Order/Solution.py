# 题目：3645. 最优激活顺序得到的最大总和（Maximum Total from Optimal Activation Order）
# 核心思路：激活上限相同的元素互相竞争同一份名额，而不同上限的组之间互不影响；于是按 limit 分组，组内价值从大到小排序，每组只取最多 min(limit, 组大小) 个最大的价值，累加即为最优。
# 复杂度：时间 O(n log n)，分组后组内排序主导；空间 O(n)，需要存放所有分组。
class Solution:  # LeetCode 题解类
    def maxTotal(self, value: List[int], limit: List[int]) -> int:  # value：各元素的价值；limit：各元素对应的激活上限
        g = defaultdict(list)  # 字典：把「激活上限」映射到该组的价值列表（缺省为空列表）
        for v, lim in zip(value, limit):  # 把价值 v 按其上限 lim 归组
            g[lim].append(v)  # 价值追加到对应组中
        ans = 0  # 累加所有组的最优贡献
        for lim, vs in g.items():  # 逐组处理，lim 为该组上限，vs 为该组价值
            vs.sort()  # 组内升序排序
            ans += sum(vs[-lim:])  # 升序后末尾的 lim 个就是该组最大的 lim 个（该组不足 lim 个时全部取到）
        return ans  # 返回可得到的最大总和
