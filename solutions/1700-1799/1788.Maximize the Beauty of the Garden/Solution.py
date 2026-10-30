# 题目：1788. 最大化花园的美观度（Maximize the Beauty of the Garden）
# 思路：最优方案两端是相同数值、中间取全部正值；用只累加正数的前缀和配合「值 → 首次下标」哈希表，一次遍历枚举右端点。
# 时间复杂度：O(n)，字典查询均摊 O(1)；空间复杂度：O(n)，前缀和数组与首次出现位置表。
class Solution:  # LeetCode 约定的题解类
    def maximumBeauty(self, flowers: List[int]) -> int:  # 返回能获得的最大美观度
        s = [0] * (len(flowers) + 1)  # 前缀和：s[i] 是前 i 朵花中正数之和（负值花不采，不计入）
        d = {}  # 记录每种花值第一次出现的下标
        ans = -inf  # 答案初始化为负无穷，保证任何合法方案作为候选时都能被 max 更新到
        for i, v in enumerate(flowers):  # 同时取得下标 i 与花值 v，从左到右枚举右端点
            if v in d:  # 这种花以前出现过，就能把它当作区间的两端
                ans = max(ans, s[i] - s[d[v] + 1] + v * 2)  # 两端各算一次 v，再加上区间内部的正数之和（前缀和区间差）
            else:  # 第一次见到这种花
                d[v] = i  # 记录首次出现的下标，供后续配对
            s[i + 1] = s[i] + max(v, 0)  # 维护前缀和：只累加正值，负值花不采、贡献为 0
        return ans  # 返回最大美观度
