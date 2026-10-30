# 题目：2006. 差的绝对值为 K 的数对数目（Count Number of Pairs With Absolute Difference K）
# 思路：数据范围很小，用一个生成器表达式枚举所有 i < j 的下标对，把布尔结果累加即可。
# 时间复杂度：O(n^2)，两层推导；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def countKDifference(self, nums: List[int], k: int) -> int:  # nums 是输入数组，k 是要求的绝对差；返回满足条件的数对个数
        n = len(nums)  # n 是数组长度
        return sum(  # 用 sum 统计所有满足条件的下标对（True 记作 1，False 记作 0）
            abs(nums[i] - nums[j]) == k for i in range(n) for j in range(i + 1, n)  # 生成器表达式：枚举 i < j 的所有下标对，判断绝对差是否恰好等于 k
        )  # 生成器表达式结束，sum 把布尔值累加成最终计数
