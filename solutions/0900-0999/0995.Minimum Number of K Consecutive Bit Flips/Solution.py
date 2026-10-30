# 题目：995. K 连续位的最小翻转次数（Minimum Number of K Consecutive Bit Flips）
# 思路：贪心 + 差分数组。从左到右，若当前位的有效值仍为 0 就必须从这里翻 k 位；越界即无解。
# 时间复杂度：O(n)，每个位置只处理一次；空间复杂度：O(n)，差分数组长度为 n+1。
class Solution:  # LeetCode 约定的题解类
    def minKBitFlips(self, nums: List[int], k: int) -> int:  # nums：01 数组；k：每次必须翻转的连续长度；返回最少翻转次数，无法达成返回 -1
        n = len(nums)  # n 为数组长度
        d = [0] * (n + 1)  # 差分数组：d[i] 表示从位置 i 开始生效的翻转次数增量
        ans = s = 0  # ans 记录翻转次数；s 记录当前位置累计被翻转的次数
        for i, x in enumerate(nums):  # 从左到右依次确定每个位置是否需要翻转
            s += d[i]  # 累加差分，得到当前位置实际被翻转的次数
            if s % 2 == x:  # 累计翻转次数的奇偶性恰好等于当前值，说明这一位最终会是 0，必须再翻一次
                if i + k > n:  # 从这里开始翻 k 个会越界，无法完成
                    return -1  # 返回 -1 表示无解
                d[i] += 1  # 差分标记：区间 [i, i+k) 的翻转次数加一
                d[i + k] -= 1  # 区间右端以外的位置减一，抵消这次翻转的影响
                s += 1  # 当前位置的累计翻转次数同步加一
                ans += 1  # 答案加一
        return ans  # 返回最少翻转次数
