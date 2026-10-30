# 题目：2572. 无平方子集计数（Count the Number of Square-Free Subsets）
# 思路：把数值映射成质因子位掩码后做状压 DP，含平方因子的数不能入选，数字 1 只贡献 2 的幂次种选择。
# 时间复杂度：O(30 × 2^10)；空间复杂度：O(2^10)，DP 数组大小。
class Solution:  # LeetCode 约定的题解类
    def squareFreeSubsets(self, nums: List[int]) -> int:  # nums 是输入数组，返回其中无平方因子的子集个数
        primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]  # 1..30 内的全部质数，用 10 个二进制位分别表示
        cnt = Counter(nums)  # 统计每个数值在数组里出现的次数
        mod = 10**9 + 7  # 取模常量，防止答案超出范围
        n = len(primes)  # 质数个数，也就是掩码的位数
        f = [0] * (1 << n)  # f[mask]：已选质因子集合恰好为 mask 的子集方案数
        f[0] = pow(2, cnt[1])  # 数字 1 不含质因子，每个 1 可选可不选
        for x in range(2, 31):  # 从小到大枚举可能被选中的数值
            if cnt[x] == 0 or x % 4 == 0 or x % 9 == 0 or x % 25 == 0:  # 该数值没出现过，或是 4/9/25 的倍数（含平方因子），不能入选
                continue  # 直接跳过这个数值
            mask = 0  # 用来记录当前数值的质因子集合
            for i, p in enumerate(primes):  # 逐个质数检查它是否能整除 x
                if x % p == 0:  # x 含有质因子 p
                    mask |= 1 << i  # 在掩码的第 i 位上打标记
            for state in range((1 << n) - 1, 0, -1):  # 倒序枚举状态，保证同一个数值最多被用一次
                if state & mask == mask:  # 判断 state 是否覆盖 mask 的全部位（注意 == 的优先级高于 &）
                    f[state] = (f[state] + cnt[x] * f[state ^ mask]) % mod  # 从去掉 mask 的状态转移过来，累加 cnt[x] 种选法并取模
        return sum(v for v in f) % mod - 1  # 所有状态求和后减掉空集
