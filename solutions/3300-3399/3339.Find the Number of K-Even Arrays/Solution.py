# 题目：3339. 查找 K 偶数数组的数量（Find the Number of K-Even Arrays）
# 思路：记忆化搜索。状态为 (已填位数 i, 还差的相邻偶数对 j, 上一位奇偶性 k)；放奇数有 cnt1 种选法，放偶数有 cnt0 种选法。
# 时间复杂度：O(n·k) 个状态、每个 O(1) 转移；空间复杂度：O(n·k)，即缓存占用。
class Solution:  # LeetCode 约定的题解类
    def countOfArrays(self, n: int, m: int, k: int) -> int:  # n 是数组长度，m 是元素上界，k 是要求的相邻偶数对数
        @cache  # 记忆化装饰器：缓存 dfs 每个状态的结果，避免重复搜索
        def dfs(i: int, j: int, k: int) -> int:  # i 已填的位数，j 还差的相邻偶数对数，k 上一位是否为奇数
            if j < 0:  # 还差的相邻偶数对已被减成负数，说明超额
                return 0  # 超额方案不合法，贡献 0
            if i >= n:  # 已经填满 n 个位置
                return int(j == 0)  # 恰好凑够 k 对才合法，int(...) 把布尔值转成 0/1
            return (  # 返回两种选择的方案数之和（表达式跨行书写，下一行是各项）
                cnt1 * dfs(i + 1, j, 1) + cnt0 * dfs(i + 1, j - (k & 1 ^ 1), 0)  # 放奇数不消耗配额；放偶数时 (k & 1 ^ 1) 为 1（上一位是偶数）就消耗一对
            ) % mod  # 求和后对 mod 取模，得到本状态的方案数

        cnt0 = m // 2  # 1..m 中偶数的个数
        cnt1 = m - cnt0  # 1..m 中奇数的个数
        mod = 10**9 + 7  # 取模常量，防止方案数过大
        ans = dfs(0, k, 1)  # 从第 0 位开始搜索；虚拟上一位取 1（奇数），避免首位被误算成一对偶数
        dfs.cache_clear()  # 清空缓存：防止同一实例被多次调用时结果脏读，也避免占用内存
        return ans  # 返回答案
