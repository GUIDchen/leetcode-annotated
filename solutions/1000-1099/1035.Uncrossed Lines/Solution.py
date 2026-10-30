# 题目：1035. 不相交的线（Uncrossed Lines）
# 思路：不相交的连线等价于保序匹配，即最长公共子序列；相等时取左上角加一，否则取上方与左方的较大值。
# 时间复杂度：O(m*n)，两重循环填表；空间复杂度：O(m*n)，二维 DP 表。
class Solution:  # LeetCode 约定的题解类
    def maxUncrossedLines(self, nums1: List[int], nums2: List[int]) -> int:  # 求 nums1 与 nums2 之间最多能连多少条不相交的线（本质是最长公共子序列）
        m, n = len(nums1), len(nums2)  # 两个数组的长度
        f = [[0] * (n + 1) for _ in range(m + 1)]  # 二维 DP 表：(m+1) x (n+1)，第 0 行/列作为空序列的边界，全部初始化为 0
        for i, x in enumerate(nums1, 1):  # 下标从 1 开始遍历 nums1，x 为当前元素，i 为对应的 DP 行号
            for j, y in enumerate(nums2, 1):  # 下标从 1 开始遍历 nums2，y 为当前元素，j 为对应的 DP 列号
                if x == y:  # 两个元素相等，可以连一条线
                    f[i][j] = f[i - 1][j - 1] + 1  # 接在去掉这两个元素的最优解后面，长度加一
                else:  # 元素不等，无法同时使用
                    f[i][j] = max(f[i - 1][j], f[i][j - 1])  # 取上方与左方的较大值
        return f[m][n]  # 返回完整的两个序列的最长公共子序列长度，即最多连线数
