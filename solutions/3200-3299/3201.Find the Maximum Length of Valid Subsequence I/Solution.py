# 3201. 找出有效子序列的最大长度 I（Find the Maximum Length of Valid Subsequence I）
# 核心思路：有效子序列相邻两项之和的奇偶性恒定，只需看元素模 2 的余数；f[x][y] 表示以余数 x 结尾、搭档余数为 y 的最长长度，遍历时即时转移。
# 复杂度：时间 O(n·k)，空间 O(k^2)，其中 k = 2

class Solution:  # 定义题解类
    def maximumLength(self, nums: List[int]) -> int:  # 返回相邻两项之和奇偶性恒定的最长子序列长度
        k = 2  # 只关心元素模 2 的余数
        f = [[0] * k for _ in range(k)]  # f[x][y]：以余数 x 结尾、与之配对的余数为 y 时的最长长度
        ans = 0  # 记录答案
        for x in nums:  # 依次处理每个元素
            x %= k  # 只保留余数
            for j in range(k):  # 枚举上一项的余数
                y = (j - x + k) % k  # 由 (x + y) % 2 == j 反推出需要的搭档余数 y
                f[x][y] = f[y][x] + 1  # 在「以 y 结尾、搭档为 x」的序列后接上当前的 x
                ans = max(ans, f[x][y])  # 用新长度更新答案
        return ans  # 返回最长长度
