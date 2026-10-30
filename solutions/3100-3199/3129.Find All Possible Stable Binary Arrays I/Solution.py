# 题目：3129. 找出所有稳定的二进制数组 I（Find All Possible Stable Binary Arrays I）
# 思路：记忆化搜索 + 容斥，dfs(i, j, k) 表示剩余 i 个 0、j 个 1 且末尾为 k 的方案数，减去连续段超过 limit 的非法方案。
# 时间复杂度：O(zero * one)，每个状态只算一次；空间复杂度：O(zero * one)，缓存中保存的状态数。
class Solution:  # LeetCode 约定的题解类
    def numberOfStableArrays(self, zero: int, one: int, limit: int) -> int:  # zero、one 分别是 0 与 1 的个数，limit 是同一数字连续出现的最长长度
        @cache  # functools.cache 做记忆化：相同参数只计算一次
        def dfs(i: int, j: int, k: int) -> int:  # 内部函数 dfs：还剩 i 个 0、j 个 1，k 是当前末尾数字（0 或 1）
            if i == 0:  # 0 已经用完，剩下的一定全是 1
                return int(k == 1 and j <= limit)  # 只有末尾是 1 且剩余 1 的个数不超过 limit 才合法，bool 转成 0/1
            if j == 0:  # 1 已经用完，剩下的一定全是 0
                return int(k == 0 and i <= limit)  # 只有末尾是 0 且剩余 0 的个数不超过 limit 才合法
            if k == 0:  # 末尾是 0，本次往末尾再追加一个 0
                return (  # 用掉一个 0 的方案数：先算两种前驱之和，再容斥
                    dfs(i - 1, j, 0)  # 前一位也是 0 的方案数
                    + dfs(i - 1, j, 1)  # 前一位是 1 的方案数
                    - (0 if i - limit - 1 < 0 else dfs(i - limit - 1, j, 1))  # 容斥：减掉 0 连续长度超过 limit 的非法方案，下标越界时取 0
                )  # 括号闭合，得到 k == 0 的转移结果
            return (  # 末尾是 1，本次往末尾再追加一个 1
                dfs(i, j - 1, 0)  # 前一位是 0 的方案数
                + dfs(i, j - 1, 1)  # 前一位是 1 的方案数
                - (0 if j - limit - 1 < 0 else dfs(i, j - limit - 1, 0))  # 容斥：减掉 1 连续长度超过 limit 的非法方案，下标越界时取 0
            )  # 括号闭合，得到 k == 1 的转移结果

        mod = 10**9 + 7  # 答案取模的模数
        ans = (dfs(zero, one, 0) + dfs(zero, one, 1)) % mod  # 第一个数字既可以是 0 也可以是 1，两种末尾情况相加后取模
        dfs.cache_clear()  # 清空缓存，避免同一实例被多次调用时残留旧状态
        return ans  # 返回最终答案
