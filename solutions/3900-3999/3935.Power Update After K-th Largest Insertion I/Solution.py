# 3935. 插入后第 K 大更新的幂 I / Power Update After K-th Largest Insertion I
# 核心思路：用两个有序表 l、r 维护「最大的 k 个」与「其余元素」，每次插入后调整规模，取 r 的最小值即第 k 大，再对 p 做快速幂。
# 复杂度：时间 O((n + q) log n + q log mod)，空间 O(n)。
class Solution:  # 题解类定义
    def powerUpdate(  # 主函数定义，参数分行书写
        self, nums: list[int], p: int, queries: list[list[int]]  # 参数：初始数组、基数 p、查询列表
    ) -> list[int]:  # 返回每次查询更新后的 p
        l = SortedList()  # 有序表 l，保存较小的元素
        r = SortedList(nums)  # 有序表 r，保存最大的 k 个元素
        ans = []  # 结果列表
        mod = 10**9 + 7  # 快速幂的模数
        for val, k in queries:  # 逐条处理查询
            r.add(val)  # 新值先插入 r
            l.add(r.pop(0))  # 把 r 中最小的元素移到 l
            while len(r) < k:  # r 中元素不足 k 个
                r.add(l.pop())  # 从 l 取最大元素补进 r
            while len(r) > k:  # r 中元素多于 k 个
                l.add(r.pop(0))  # 把 r 中最小元素移回 l
            x = r[0]  # r 的最小元素即第 k 大元素
            p = pow(p, x, mod)  # 更新 p = p^x mod mod
            ans.append(p)  # 记录本次答案
        return ans  # 返回所有答案
