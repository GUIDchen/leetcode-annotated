# 3495. Minimum Operations to Make Array Elements Zero / 3495. 使数组元素都变为零的最少操作次数
# 核心思路：f(x) 统计 1..x 中每个数各自归零所需次数之和（按 4 的幂分段），一次操作可让两个数同时降一级，故单次查询答案为 max(ceil(s / 2), 最大单点次数)。
# 复杂度：时间 O(m log r)，其中 m 为查询数、r 为区间右端最大值；空间 O(1)。

class Solution:  # LeetCode 题解统一使用 Solution 类
    def minOperations(self, queries: List[List[int]]) -> int:  # queries 为若干闭区间 [l, r]
        def f(x: int) -> int:  # 前缀函数：统计 1..x 中每个数各自归零所需次数之和
            res = 0  # 累计次数
            p = i = 1  # p 为当前 4 的幂次区间左端点，i 为该区间内每个数需要的次数
            while p <= x:  # 区间左端点未超过 x 时继续分段
                cnt = min(p * 4 - 1, x) - p + 1  # 区间 [p, min(4p - 1, x)] 内的整数个数
                res += cnt * i  # 这些数每个都贡献 i 次操作
                i += 1  # 进入下一层，次数加一
                p *= 4  # 左端点扩到 4 倍
            return res  # 返回 1..x 的总次数

        ans = 0  # 所有查询的答案累加
        for l, r in queries:  # 逐个处理查询区间并解包左右端点
            s = f(r) - f(l - 1)  # 区间内所有元素各自归零次数之和
            mx = f(r) - f(r - 1)  # 右端点单个元素所需的次数，即区间内可能的最大单点次数
            ans += max((s + 1) // 2, mx)  # 每次操作最多同时消去两个数的一层，故取 ceil(s / 2) 与单点最大值
        return ans  # 返回全部查询的最少操作次数之和
