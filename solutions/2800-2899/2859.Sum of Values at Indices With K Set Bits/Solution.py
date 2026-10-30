# 题目：2859. 计算 K 置位下标对应元素的和（Sum of Values at Indices With K Set Bits）
# 思路：遍历下标 i，用 int.bit_count() 统计 i 的二进制 1 的个数，等于 k 就把 nums[i] 累加。
# 复杂度：时间 O(n log n)，每个下标做一次位统计；空间 O(1)，生成器不额外占空间。
class Solution:  # LeetCode 约定的题解类
    def sumIndicesWithKSetBits(self, nums: List[int], k: int) -> int:  # nums：输入数组；k：下标二进制中要求为 1 的位数
        return sum(x for i, x in enumerate(nums) if i.bit_count() == k)  # 生成器表达式：只把置位数等于 k 的下标对应的元素求和
