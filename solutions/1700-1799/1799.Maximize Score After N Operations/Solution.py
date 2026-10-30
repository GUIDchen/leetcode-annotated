# 题目：1799. N 次操作后的最大分数和（Maximize Score After N Operations）
# 思路：状压 DP，f[mask] 表示已用元素集合为 mask 时的最大得分；已用个数 cnt 为偶数时，枚举最后取出的两个下标 i、j，本轮倍数恰为 cnt/2，用 max 转移。
# 时间复杂度：O(2^m · m^2)，m = 2n 为元素个数；空间复杂度：O(2^m + m^2)。
class Solution:  # LeetCode 约定的题解类
    def maxScore(self, nums: List[int]) -> int:  # nums：长度为 2n 的数组，返回 n 次操作的最大得分和
        m = len(nums)  # 元素个数，必为偶数
        f = [0] * (1 << m)  # f[mask]：已用集合为 mask 时的最大得分
        g = [[0] * m for _ in range(m)]  # g[i][j]：i、j 两个数的最大公约数
        for i in range(m):  # 预处理所有数对
            for j in range(i + 1, m):  # 只算上三角 i < j
                g[i][j] = gcd(nums[i], nums[j])  # 计算并缓存 gcd
        for k in range(1 << m):  # 按 mask 递增枚举状态
            if (cnt := k.bit_count()) % 2 == 0:  # 海象运算符取已用个数；偶数才是合法状态
                for i in range(m):  # 枚举这一轮的第一个下标
                    if k >> i & 1:  # i 必须已在集合中
                        for j in range(i + 1, m):  # 枚举第二个下标，只取 i < j
                            if k >> j & 1:  # j 也必须在集合中
                                f[k] = max(  # 以 i、j 作为最后一对来转移
                                    f[k],  # 保留已有的更优值
                                    f[k ^ (1 << i) ^ (1 << j)] + cnt // 2 * g[i][j],  # 去掉 i、j 的状态得分加上本轮得分
                                )  # max 调用结束
        return f[-1]  # 全集对应的答案
