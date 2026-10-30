# 题目：829. 连续整数求和（Consecutive Numbers Sum）
# 思路：若 N 能拆成 k 个连续正整数，则 2N = k*(2a+k-1)，即 2N 能被 k 整除且 2N/k+1-k 为偶数。枚举合法的 k 并计数。
# 时间复杂度：O(sqrt(N))，k 枚举到 k(k+1) <= 2N 为止；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def consecutiveNumbersSum(self, n: int) -> int:  # n 是待拆分的正整数，返回能写成连续正整数之和的方案数
        n <<= 1  # 换成 2N，后面只需判断整除与奇偶
        ans, k = 0, 1  # ans 记方案数；k 从 1（只含 n 自己）开始枚举项数
        while k * (k + 1) <= n:  # k(k+1) <= 2N 保证首项至少为 1；更长的 k 一定不合法，循环可以到此为止
            if n % k == 0 and (n // k - k + 1) % 2 == 0:  # 2N 能被 k 整除，且首项 a = (2N/k - k + 1)/2 为整数（括号内为偶）
                ans += 1  # 找到一组合法 k，方案数加一
            k += 1  # 试下一个项数
        return ans  # 返回方案数
