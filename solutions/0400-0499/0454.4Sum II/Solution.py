# 题目：454. 四数相加 II（4Sum II）
# 思路：先枚举 nums1、nums2 的所有两数组合，用计数器统计每种和出现的次数；再枚举 nums3、nums4，累加 -(c+d) 的次数即为 a+b+c+d=0 的四元组数。
# 时间复杂度：O(n^2)，两组两两组合各枚举一次；空间复杂度：O(n^2)，计数器最多存 n^2 个不同的和。
class Solution:  # LeetCode 约定的题解类
    def fourSumCount(  # 返回满足 a+b+c+d == 0 的下标元组个数
        self, nums1: List[int], nums2: List[int], nums3: List[int], nums4: List[int]  # 四个等长的整数数组（方法签名续行，参数在下一行）
    ) -> int:  # 返回类型为 int
        cnt = Counter(a + b for a in nums1 for b in nums2)  # 统计 nums1 与 nums2 所有两数之和各自出现的次数（Counter 由判题环境提供）
        return sum(cnt[-(c + d)] for c in nums3 for d in nums4)  # 对 nums3、nums4 的每一对，累加补数 -(c+d) 的出现次数
