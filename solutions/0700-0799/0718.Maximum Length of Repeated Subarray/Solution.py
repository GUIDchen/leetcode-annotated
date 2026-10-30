# 题目：718. 最长重复子数组（Maximum Length of Repeated Subarray）
# 核心思路：经典二维 DP。f[i][j] 表示以 nums1[i-1]、nums2[j-1] 结尾的最长公共连续子数组长度；末尾元素相同则 f[i-1][j-1] + 1，否则为 0，全程取最大值。
# 时间复杂度：O(m·n)，DP 表每个位置算一次；空间复杂度：O(m·n)，需要保存整张 DP 表。
class Solution:  # LeetCode 约定的题解类
    def findLength(self, nums1: List[int], nums2: List[int]) -> int:  # 返回两个数组的最长公共连续子数组的长度
        m, n = len(nums1), len(nums2)  # 两个数组的长度，用于建立 DP 表
        f = [[0] * (n + 1) for _ in range(m + 1)]  # f[i][j]：以 nums1 前 i 个、nums2 前 j 个元素结尾的最长公共子数组长度，初始全 0
        ans = 0  # 记录遍历过程中出现过的最大匹配长度
        for i in range(1, m + 1):  # 枚举 nums1 的前缀长度 i
            for j in range(1, n + 1):  # 枚举 nums2 的前缀长度 j
                if nums1[i - 1] == nums2[j - 1]:  # 两个末尾元素相同，匹配长度可以在左上角的状态上继续延长
                    f[i][j] = f[i - 1][j - 1] + 1  # 以这两个位置结尾的最长公共子数组长度
                    ans = max(ans, f[i][j])  # 随时更新全局最大值
        return ans  # 返回整张表中出现过的最大长度
