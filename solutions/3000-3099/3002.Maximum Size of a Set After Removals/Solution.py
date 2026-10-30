# 题目：3002. 移除后集合的最多元素数（Maximum Size of a Set After Removals）
# 思路：两数组各自去重后分成「只属 nums1」「只属 nums2」「两边共有」三块；每边最多只能贡献 n/2 个，独有部分先截到 n/2，再加上共有部分与总数 n 取小。
# 时间复杂度：O(n)，建集合与求交并都是线性；空间复杂度：O(n)，两个去重集合。
class Solution:  # LeetCode 约定的题解类
    def maximumSetSize(self, nums1: List[int], nums2: List[int]) -> int:  # nums1 / nums2：长度同为 n 的两个数组；返回各删掉 n/2 个元素后，两集合元素种类数的最大值
        s1 = set(nums1)  # nums1 去重，得到它包含的全部不同元素
        s2 = set(nums2)  # nums2 去重
        n = len(nums1)  # 两数组等长，记录 n 以确定每边最多只能贡献 n // 2 个元素
        a = min(len(s1 - s2), n // 2)  # 只在 nums1 出现的元素数，但最多只能取 n // 2 个
        b = min(len(s2 - s1), n // 2)  # 只在 nums2 出现的元素数，同样最多取 n // 2 个
        return min(a + b + len(s1 & s2), n)  # 独有部分相加后再加上共有部分（两边都能取），但集合总大小不超过 n
