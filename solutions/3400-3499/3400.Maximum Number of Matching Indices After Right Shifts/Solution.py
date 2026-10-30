# 3400. 右移后的最大匹配索引数 / Maximum Number of Matching Indices After Right Shifts
# 核心思路：枚举全部 n 种右移量 k，逐位比较 nums1[(i + k) % n] 与 nums2[i]，统计匹配数并取最大值
# 复杂度：时间 O(n^2)，空间 O(1)
class Solution:  # 定义题目解答类
    def maximumMatchingIndices(self, nums1: List[int], nums2: List[int]) -> int:  # 方法入口：nums1 循环右移，nums2 固定，求最多匹配位数
        n = len(nums1)  # 数组长度，也是右移的周期
        ans = 0  # 记录最大匹配数
        for k in range(n):  # 枚举右移量 k
            t = sum(nums1[(i + k) % n] == x for i, x in enumerate(nums2))  # 当前右移量下的匹配数
            ans = max(ans, t)  # 更新全局最大值
        return ans  # 返回最多匹配的索引个数
