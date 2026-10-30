# 3850. 统计结果等于 K 的序列数目 / Count Sequences to K（困难）
# 核心思路：把元素逐个放进分子或分母（也可都不放），全程保持最简分数并记忆化搜索，最终约分为整数 k 即为一种方案。
# 复杂度：时间 O(n·S)，空间 O(S)，S 为不同 (下标, 分子, 分母) 状态数。
class Solution:  # 题解类（LeetCode 约定类名）
    def countSequences(self, nums: List[int], k: int) -> int:  # 返回按规则计算后结果恰好等于 k 的序列数目
        @cache  # 记忆化，避免同一状态重复搜索
        def dfs(i: int, p: int, q: int) -> int:  # 处理到下标 i 时，当前结果为最简分数 p / q
            if i == n:  # 所有元素处理完毕
                return 1 if p == k and q == 1 else 0  # 结果恰为整数 k 时计 1 种方案
            x = nums[i]  # 取出当前元素
            res = dfs(i + 1, p, q)  # 选择一：不把 x 计入分子或分母
            g = gcd(p * x, q)  # 把 x 乘到分子后与分母的最大公约数
            res += dfs(i + 1, p * x // g, q // g)  # 选择二：把 x 计入分子并按最大公约数约分
            g = gcd(p, q * x)  # 把 x 乘到分母后与分子的最大公约数
            res += dfs(i + 1, p // g, q * x // g)  # 选择三：把 x 计入分母并按最大公约数约分
            return res  # 返回该状态的方案数

        n = len(nums)  # 数组长度
        ans = dfs(0, 1, 1)  # 从下标 0、分子分母均为 1 开始搜索
        dfs.cache_clear()  # 清空缓存，避免跨调用污染
        return ans  # 返回方案数
