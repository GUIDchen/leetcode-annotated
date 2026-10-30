# 题目：1537. 最大得分（Get the Maximum Score）
# 思路：双指针各走一条递增路径，f、g 记录停在 nums1/nums2 当前位置的最大得分；遇到相同值就从较大的那条切换。
# 时间复杂度：O(m+n)，两个指针只前进不后退；空间复杂度：O(1)，只用几个变量。
class Solution:  # LeetCode 约定的题解类
    def maxSum(self, nums1: List[int], nums2: List[int]) -> int:  # nums1、nums2 是两条严格递增的路径
        mod = 10**9 + 7  # 答案取模用的常数 1e9+7
        m, n = len(nums1), len(nums2)  # 两条路径的长度
        i = j = 0  # 双指针，指向两条路径当前的元素
        f = g = 0  # f、g 分别是以 nums1、nums2 当前元素结尾时的最大得分
        while i < m or j < n:  # 只要有一条路径没走完就继续
            if i == m:  # nums1 已走完，只能走 nums2
                g += nums2[j]  # 取走 nums2 当前元素
                j += 1  # nums2 指针后移
            elif j == n:  # nums2 已走完，只能走 nums1
                f += nums1[i]  # 取走 nums1 当前元素
                i += 1  # nums1 指针后移
            elif nums1[i] < nums2[j]:  # nums1 当前值更小，先取它
                f += nums1[i]  # 计入 nums1 路径的得分
                i += 1  # nums1 指针后移
            elif nums1[i] > nums2[j]:  # nums2 当前值更小
                g += nums2[j]  # 计入 nums2 路径的得分
                j += 1  # nums2 指针后移
            else:  # 两值相等，到达两条路径的汇合点
                f = g = max(f, g) + nums1[i]  # 从得分更高的那条路径切换过来，并加上交点值
                i += 1  # 交点共享，nums1 指针前进
                j += 1  # nums2 指针同时前进
        return max(f, g) % mod  # 取两条路径的较大得分并按题目要求取模
