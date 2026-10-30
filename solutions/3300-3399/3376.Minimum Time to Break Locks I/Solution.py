# 题目：3376. 破解锁的最少时间 I（Minimum Time to Break Locks I）
# 思路：状态压缩 DP + 记忆化搜索。i 的二进制位记录已破解的锁，当前能量 x = 1 + K*popcount(i)，破解锁 j 需 ⌈strength[j]/x⌉ 次，枚举下一把锁取最小。
# 时间复杂度：O(2^n · n)；空间复杂度：O(2^n)，n 为锁的数量（n ≤ 8）。
class Solution:  # LeetCode 约定的题解类
    def findMinimumTime(self, strength: List[int], K: int) -> int:  # strength：每把锁的强度；K：每破一把锁后能量增加的系数
        @cache  # @cache 记忆化：同一个掩码状态只计算一次，避免指数级重复搜索
        def dfs(i: int) -> int:  # i 是状态压缩掩码，第 j 位为 1 表示第 j 把锁已破解
            if i == (1 << len(strength)) - 1:  # mask 全 1 说明所有锁都已破解，到达递归终点
                return 0  # 没有剩下的锁，剩余代价为 0
            cnt = i.bit_count()  # bit_count() 统计掩码中 1 的个数，即已破解的锁数
            x = 1 + cnt * K  # 当前能量 x：破解第一把锁时为 1，之后每破解一把增加 K
            ans = inf  # 初始化为正无穷，用于下面逐个取最小值
            for j, s in enumerate(strength):  # 枚举下一把要破解的锁：j 是下标，s 是它的强度
                if i >> j & 1 ^ 1:  # 运算符优先级为 ((i >> j) & 1) ^ 1，即第 j 位为 0，说明锁 j 还没被破解
                    ans = min(ans, dfs(i | 1 << j) + (s + x - 1) // x)  # 破解 j 需要向上取整 ⌈s/x⌉ 次，加上后续最优解后取最小
            return ans  # 返回当前状态的最优总时间

        return dfs(0)  # 从「一把锁都没破解」的初始 mask 开始搜索，答案即最少时间
