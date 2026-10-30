# 题目：3930. 插入后第 K 大更新的幂 II（Power Update After K-th Largest Insertion II）
# 思路：用 SortedList 维护当前所有元素的有序序列，支持 O(log n) 插入与按下标取数；每次插入后取倒数第 k 个即第 k 大，再用内置 pow 做快速幂取模更新 p。
# 时间复杂度：O((n + q) log(n + q) + q log p)；空间复杂度：O(n + q)。
class Solution:  # LeetCode 约定的题解类
    def powerUpdate(  # nums：初始数组；p：初始底数；queries：每项是 [val, k]
        self, nums: list[int], p: int, queries: list[list[int]]  # 参数列表：self 与三个入参
    ) -> list[int]:  # 返回每次查询后的 p
        ans = []  # 存放每次查询后的 p
        sl = SortedList(nums)  # 有序列表维护当前所有元素，支持按下标取第几大
        mod = 10**9 + 7  # 取模常数 10^9+7
        for val, k in queries:  # 逐个处理查询：val 待插入，k 是第几大
            sl.add(val)  # 先把 val 插入有序结构
            p = pow(p, sl[-k], mod)  # 第 k 大即倒数第 k 个，用内置快速幂取模更新 p
            ans.append(p)  # 记录本次查询后的 p
        return ans  # 返回所有答案
