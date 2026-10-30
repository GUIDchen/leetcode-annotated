# 题目：1770. 执行乘法运算的最大分数（Maximum Score from Performing Multiplication Operations）
# 思路：记忆化搜索。f(i, j, k) 表示 nums 当前可用区间为 [i, j]、接下来用第 k 个乘数时的最大分数；每步只能取左端 nums[i] 或右端 nums[j]，取较大值并用 @cache 缓存。
# 时间复杂度：O(m * n)，状态 (i, j, k) 受已取个数 k 的约束；空间复杂度：O(m * n)，缓存表。
class Solution:  # LeetCode 约定的题解类
    def maximumScore(self, nums: List[int], multipliers: List[int]) -> int:  # nums 是可以取数的数组，multipliers 是按顺序使用的乘数
        @cache  # @cache 把 f 的每个 (i, j, k) 结果缓存起来，避免重复计算
        def f(i, j, k):  # f(i, j, k)：i 是当前可用区间的左端，j 是右端，k 是当前乘数下标
            if k >= m or i >= n or j < 0:  # 乘数用完或可用区间变空时无法继续取数，得分为 0
                return 0
            a = f(i + 1, j, k + 1) + nums[i] * multipliers[k]  # 方案一：取左端 nums[i] 与 multipliers[k] 相乘，再递归剩余区间 [i+1, j]
            b = f(i, j - 1, k + 1) + nums[j] * multipliers[k]  # 方案二：取右端 nums[j] 与 multipliers[k] 相乘，再递归剩余区间 [i, j-1]
            return max(a, b)  # 两种方案取较大值作为当前状态的最优解

        n = len(nums)  # nums 的长度
        m = len(multipliers)  # 乘数的个数（也是最多能执行的运算次数）
        return f(0, n - 1, 0)  # 从整个数组区间与第 0 个乘数开始递归
