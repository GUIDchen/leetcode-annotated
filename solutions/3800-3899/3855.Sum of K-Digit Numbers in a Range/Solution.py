# 3855. 给定范围内 K 位数字之和 / Sum of K-Digit Numbers in a Range（困难）
# 核心思路：k 位数的每一位权重之和是 k 个 1 组成的十进制数 (10^k - 1) / 9；固定某一位取某个数字后，其余 k-1 位可任选（共 n^(k-1) 种），故总和 = 区间数字和 × n^(k-1) × (10^k - 1) ÷ 9，除法用费马小定理求逆元实现。
# 复杂度：时间 O(log k + log mod)（两次快速幂），空间 O(1)。
class Solution:  # 设计一个算法：求所有 k 位、每位取自 [l, r] 的整数之和
    def sumOfNumbers(self, l: int, r: int, k: int) -> int:  # 返回所有满足条件的 k 位数之和，对 1e9+7 取模
        mod = 10**9 + 7  # 取模常数

        n = r - l + 1  # 可选数字的个数 n = r - l + 1

        # 区间 [l, r] 的等差求和 (l + r) * n // 2
        total = (l + r) * n // 2 % mod  # total = 区间数字和（对 mod 取余）

        # 固定某一位后其余 k - 1 位可任取：n^(k - 1)
        part1 = pow(n % mod, k - 1, mod)  # part1 = n^(k - 1) mod mod

        # k 个 1 组成的十进制数：(10^k - 1) / 9
        part2 = (pow(10, k, mod) - 1) % mod  # part2 = 10^k - 1（Python 取模后天然非负）

        # 费马小定理求 9 的逆元
        inv9 = pow(9, mod - 2, mod)  # inv9 用来代替“除以 9”

        ans = total  # 答案从区间数字和开始
        ans = ans * part1 % mod  # 乘上排列数 n^(k - 1)
        ans = ans * part2 % mod  # 乘上位权之和 10^k - 1
        ans = ans * inv9 % mod  # 乘上 9 的逆元，等价于除以 9

        return ans  # 返回所有 k 位数字之和取模的结果
