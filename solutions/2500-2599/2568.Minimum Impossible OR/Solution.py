# 题目：2568. 最小无法得到的或值（Minimum Impossible OR）
# 思路：任意子集的按位或若要等于 2^i，数组中必须存在 2^i（更大的数会带上别的二进制位）；因此答案就是最小的、不在数组中的 2 的幂。
# 时间复杂度：O(n + 32)，建集合 O(n)，再检查 32 个 2 的幂；空间复杂度：O(n)，集合存放所有元素。
class Solution:  # LeetCode 约定的题解类
    def minImpossibleOR(self, nums: List[int]) -> int:  # nums：可用元素（每个最多用一次）的数组
        s = set(nums)  # 转成集合，便于 O(1) 判断某个值是否存在
        return next(1 << i for i in range(32) if 1 << i not in s)  # 从小到大生成 2 的幂，取第一个不在集合中的那个作为答案
