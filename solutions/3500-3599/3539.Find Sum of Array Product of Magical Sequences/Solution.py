# 3539. 魔法序列的数组乘积之和 / Find Sum of Array Product of Magical Sequences
# 核心思路：按二进制位做数位 DP，枚举每个数被选的次数 t，用组合数分配下标、幂次贡献乘积，进位逐位消耗统计 popcount 恰为 k 的方案数。
# 复杂度：时间 O(n·m·k·m·log(max))（含快速幂），空间 O(n·m·k·N) 的记忆化缓存。
mx = 30  # 组合数的最大规模（m、k 不超过 30）
mod = 10**9 + 7  # 取模常数
f = [1] + [0] * mx  # f 存阶乘，f[0] = 1
g = [1] + [0] * mx  # g 存阶乘的模逆元，g[0] = 1

for i in range(1, mx + 1):  # 从小到大预计算
    f[i] = f[i - 1] * i % mod  # i! = (i-1)! × i
    g[i] = pow(f[i], mod - 2, mod)  # 用费马小定理求 i! 的逆元


def comb(m: int, n: int) -> int:  # 计算组合数 C(m, n)
    return f[m] * g[n] * g[m - n] % mod  # m! / (n! (m-n)!)，除法用乘逆元实现


class Solution:  # 定义题解类
    def magicalSum(self, m: int, k: int, nums: List[int]) -> int:  # 主函数：返回所有魔法序列的数组乘积之和
        @cache  # 记忆化装饰器，缓存 dfs 结果
        def dfs(i: int, j: int, k: int, st: int) -> int:  # 处理前 i 个数、还需选 j 个、剩余 k 个 1、当前进位 st
            if k < 0 or (i == len(nums) and j > 0):  # 进位已为负，或数用完了却还没选够 j 个
                return 0  # 该方案不合法，贡献 0
            if i == len(nums):  # 所有数都已处理完毕
                while st:  # 把剩余进位逐位消耗
                    k -= st & 1  # 减去该位上 1 的个数
                    st >>= 1  # 进位右移一位
                return int(k == 0)  # 恰好消耗掉 k 个 1 则计 1 种方案
            res = 0  # 累加初值为 0
            for t in range(j + 1):  # 枚举当前数字被选中的次数 t
                nt = t + st  # 加上已有进位
                p = pow(nums[i], t, mod)  # nums[i] 的 t 次幂
                nk = k - (nt & 1)  # 当前位贡献的 1 从 k 中扣掉
                res += comb(j, t) * p * dfs(i + 1, j - t, nk, nt >> 1)  # 选出 t 个位置 × 幂次 × 子问题方案数
                res %= mod  # 随时取模防止溢出
            return res  # 返回该状态的方案数

        ans = dfs(0, m, k, 0)  # 从初始状态开始求解
        dfs.cache_clear()  # 清空缓存，避免影响后续调用
        return ans  # 返回答案
