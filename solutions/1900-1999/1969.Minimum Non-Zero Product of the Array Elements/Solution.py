# 题目：1969. 数组元素的最小非零乘积（Minimum Non-Zero Product of the Array Elements）
# 思路：数组是 1 到 2^p-1，把除最大值外的元素两两配对、把 1 位从一侧挪到另一侧，可让每对乘积最小；答案为 (2^p-1) * (2^p-2)^(2^(p-1)-1)。
# 时间复杂度：O(p)，快速幂指数有 p 位；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minNonZeroProduct(self, p: int) -> int:  # p：数组由 1 到 2^p-1 构成
        mod = 10**9 + 7  # 题目要求的取模模数
        return (2**p - 1) * pow(2**p - 2, 2 ** (p - 1) - 1, mod) % mod  # pow 的三参数形式自带取模，得到 (2^p-1) * (2^p-2)^(2^(p-1)-1) % mod
