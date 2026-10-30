# 题目：1994. 好子集的数目（The Number of Good Subsets）
# 思路：状压 DP。1 与其他质因子都不冲突，单独折成 2^cnt[1] 的系数；对 2..30 中没有重复质因子的数，把质因子集合压成 10 位掩码，逆序枚举状态做 0/1 背包式转移。
# 时间复杂度：O(30 * 2^10)；空间复杂度：O(2^10)。
class Solution:  # LeetCode 约定的题解类
    def numberOfGoodSubsets(self, nums: List[int]) -> int:  # nums：输入数组，元素取值 1..30
        primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]  # 30 以内的 10 个质数，用来把质因子集合压成二进制的位
        cnt = Counter(nums)  # 统计每个数的出现次数
        mod = 10**9 + 7  # 答案取模用的大质数
        n = len(primes)  # 质数个数，也就是状态位数
        f = [0] * (1 << n)  # f[mask]：质因子集合恰好为 mask 的好子集个数
        f[0] = pow(2, cnt[1])  # 所有 1 都可自由取舍，空掩码的基础方案数是 2^cnt[1]
        for x in range(2, 31):  # 枚举 2..30 中可能被选入子集的数值
            if cnt[x] == 0 or x % 4 == 0 or x % 9 == 0 or x % 25 == 0:  # 没出现过；或被 4/9/25 整除说明质因子有重复，不能进好子集
                continue  # 这种数直接跳过
            mask = 0  # x 的质因子掩码
            for i, p in enumerate(primes):  # 同时取到质数的位下标 i 与质数 p
                if x % p == 0:  # x 含有该质因子
                    mask |= 1 << i  # 把对应的状态位置 1
            for state in range((1 << n) - 1, 0, -1):  # 逆序枚举状态，保证每个数最多被使用一次（0/1 背包）
                if state & mask == mask:  # 状态包含 x 的全部质因子时才能加入 x
                    f[state] = (f[state] + cnt[x] * f[state ^ mask]) % mod  # 转移：加上 cnt[x] 种选法与 state^mask 的方案数，并取模
        return sum(f[i] for i in range(1, 1 << n)) % mod  # 累加全部非空掩码的方案数，取模后返回
