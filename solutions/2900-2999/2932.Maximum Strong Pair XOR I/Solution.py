# 题目：2932. 找出强数对的最大异或值 I（Maximum Strong Pair XOR I）
# 思路：数据范围小，直接用生成器表达式枚举所有有序数对，筛出满足 |x - y| <= min(x, y) 的强数对并取最大异或值。
# 时间复杂度：O(n^2)，两层 for 相当于双重循环；空间复杂度：O(1)，max 逐个消费生成器、不会建出列表。
class Solution:  # LeetCode 约定的题解类
    def maximumStrongPairXor(self, nums: List[int]) -> int:  # nums：输入数组，返回其中强数对的最大异或值
        return max(x ^ y for x in nums for y in nums if abs(x - y) <= min(x, y))  # 枚举所有有序数对 (x, y)，过滤出强数对，再对 x ^ y 取最大值
