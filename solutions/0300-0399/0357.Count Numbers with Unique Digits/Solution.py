# 题目：357. 统计各位数字都不同的数字个数（Count Numbers with Unique Digits）
# 思路：数位 DP，从最高位逐位填数并用 10 位掩码记录已用数字；lead 标记前导零（即实际位数不足 n 的情况），配合 cache 记忆化。
# 时间复杂度：O(n × 2^10 × 10)；空间复杂度：O(n × 2^10)，即缓存的状态数。
class Solution:  # LeetCode 约定的题解类
    def countNumbersWithUniqueDigits(self, n: int) -> int:  # 统计 [0, 10^n) 内各位数字互不相同的数字个数
        @cache  # 记忆化装饰器：缓存 (i, mask, lead) 组合的结果
        def dfs(i: int, mask: int, lead: bool) -> int:  # i 是剩余位数，mask 是已用数字的位掩码，lead 表示是否仍在处理前导零
            if i < 0:  # 剩余位数用尽，说明已经构成一个合法数字
                return 1  # 计一种方案
            ans = 0  # 累加方案数
            for j in range(10):  # 枚举当前位可以放下的数字
                if mask >> j & 1:  # 该数字对应的位已置一，说明已经用过
                    continue  # 跳过，不能重复使用
                if lead and j == 0:  # 仍在前导零阶段且当前位放 0，等于这一位不填数字
                    ans += dfs(i - 1, mask, True)  # 掩码不变，继续保持前导零状态
                else:  # 否则当前位真正填入数字 j
                    ans += dfs(i - 1, mask | 1 << j, False)  # 把 j 计入掩码，并离开前导零状态
            return ans  # 返回方案数

        return dfs(n - 1, 0, True)  # 从最高位开始，掩码为空，初始处于前导零状态
