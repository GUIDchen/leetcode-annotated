# 3875. 构造奇偶一致的数组 I（Construct Uniform Parity Array I）
# 核心思路：I 题条件下任意数组都可以构造成奇偶一致，因此直接返回 True（题目只要求返回布尔值）。
# 复杂度：时间复杂度 O(1)，空间复杂度 O(1)。
class Solution:  # 题解类
    def uniformArray(self, nums1: list[int]) -> bool:  # 判断能否把数组构造成奇偶一致
        return True  # 在 I 题的限制下总是可行
