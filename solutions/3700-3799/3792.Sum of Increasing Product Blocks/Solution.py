# 3792. 递增乘积块之和 / Sum of Increasing Product Blocks
# 核心思路：按块模拟，第 i 块由从 k 开始的 i 个连续整数相乘，累加各块乘积并随时对 1e9+7 取模，随后把 k 前移 i。
# 复杂度：时间 O(n²)，空间 O(1)。
class Solution:  # 定义 LeetCode 题解类
    def sumOfBlocks(self, n: int) -> int:  # 返回前 n 块乘积之和对 1e9+7 取模的结果
        ans = 0  # 累加结果
        mod = 10**9 + 7  # 取模常量
        k = 1  # 当前块的起始整数
        for i in range(1, n + 1):  # 依次处理第 i 块（共 i 个数）
            x = 1  # 第 i 块的乘积
            for j in range(k, k + i):  # 块内包含从 k 开始的 i 个连续整数
                x = (x * j) % mod  # 边乘边取模，防止溢出
            ans = (ans + x) % mod  # 把当前块乘积累加到答案
            k += i  # 起点后移 i 个数，作为下一块的起点
        return ans  # 返回结果
