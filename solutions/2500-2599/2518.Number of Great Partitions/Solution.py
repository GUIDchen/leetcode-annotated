# 题目：2518. 好分区的数目（Number of Great Partitions）
# 核心思路：总方案 2^n 减去坏分区。某一组元素和 < k 的划分就是坏分区，用 01 背包 f[i][j] 统计前 i 个数中和为 j（j < k）的子集数。
# 时间复杂度：O(n * k)；空间复杂度：O(n * k)，即二维 DP 表 f 的大小。
class Solution:  # LeetCode 约定的题解类
    def countPartitions(self, nums: List[int], k: int) -> int:  # nums：待分区的数组；k：每个分区元素和的下界
        if sum(nums) < k * 2:  # 两组各至少需要 k，总和不足 2k 时一定无解
            return 0  # 直接返回 0 种方案
        mod = 10**9 + 7  # 取模常数，避免方案数溢出
        n = len(nums)  # 元素个数
        f = [[0] * k for _ in range(n + 1)]  # f[i][j]：前 i 个数中选出和为 j（j < k）的方案数
        f[0][0] = 1  # 边界：什么都不选可凑出和 0，方案数为 1
        ans = 1  # ans 从 1 开始，循环中不断翻倍，最终等于 2^n
        for i in range(1, n + 1):  # 逐个把元素加入背包
            ans = ans * 2 % mod  # 每加入一个元素，全部子集方案数翻倍
            for j in range(k):  # 只枚举 0..k-1 的容量，和达到 k 就不算坏分区
                f[i][j] = f[i - 1][j]  # 不选当前元素，方案数继承上一层
                if j >= nums[i - 1]:  # 容量够放当前元素时
                    f[i][j] = (f[i][j] + f[i - 1][j - nums[i - 1]]) % mod  # 选当前元素，累加上剩余容量对应的方案数
        return (ans - sum(f[-1]) * 2 + mod) % mod  # 2^n 减去两类坏划分（每组和 < k 各算一类，故乘 2）；加 mod 防止负数
