# 3871. 统计范围内的逗号 II / Count Commas in Range II
# 核心思路：按位数分段，凡是 ≥ 1000^k 的数都至少含 k 个逗号；对每个阈值 x = 1000, 10^6, ... 把 n - x + 1 累加进答案，即各数量级数字的贡献。
# 复杂度：时间复杂度 O(log_1000 n)，空间复杂度 O(1)。
class Solution:  # LeetCode 题解类
    def countCommas(self, n: int) -> int:  # 返回把 1..n 全部写成十进制后逗号的总数
        ans = 0  # 累加逗号总数
        x = 1000  # 从最小的千进位阈值开始
        while x <= n:  # 阈值未超过 n 时继续统计
            ans += n - x + 1  # 区间 [x, n] 内的每个数都至少多出 1 个逗号
            x *= 1000  # 升到下一个数量级
        return ans  # 返回逗号总数
