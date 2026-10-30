# 题目：2717. 半有序排列（Semi-Ordered Permutation）
# 思路：只需把 1 移到最前、n 移到最末；操作数是 1 左侧个数加 n 右侧个数，若 1 在 n 左边则交换时省一步。
# 时间复杂度：O(n)，两次线性查找；空间复杂度：O(1)，只用常数个下标变量。
class Solution:  # LeetCode 约定的题解类
    def semiOrderedPermutation(self, nums: List[int]) -> int:  # nums：1 到 n 的排列，返回最少操作次数
        n = len(nums)  # n 既是数组长度也是排列中的最大值
        i = nums.index(1)  # 1 所在的下标 i
        j = nums.index(n)  # 最大值 n 所在的下标 j
        k = 1 if i < j else 2  # 1 在 n 左边时两者交叉，交换可省 1 步，否则省 2 步
        return i + n - j - k  # 1 左侧 i 个加上 n 右侧 n-1-j 个，再减去相遇省下的 k
