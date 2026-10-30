# 3909. 比较双调部分的和（Compare Sums of Bitonic Parts）
# 思路：先把总和作为右段初值，再从左往右把上升部分的元素并入左段并从右段移除，直到出现下降为止，最后比较两段和的大小。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(1)。
class Solution:  # LeetCode 约定的题解类
    def compareBitonicSums(self, nums: list[int]) -> int:  # 比较双调序列左段与右段的和
        l, r = nums[0], sum(nums)  # l：左段和；r：右段和，两者只在峰值处重叠
        for a, b in pairwise(nums):  # 依次取出相邻的 (前一个, 后一个)
            if a > b:  # 出现下降，说明峰值已过
                break  # 停止扩展左段
            l += b  # 峰值元素并入左段
            r -= a  # 该元素不再算入右段
        if l == r:  # 两段和相等
            return -1  # 返回 -1
        return 0 if l > r else 1  # 左段更大返回 0，否则返回 1
