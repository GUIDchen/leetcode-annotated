# 题目：2809. 使数组和小于等于 x 的最少时间（Minimum Time to Make Array Sum At Most x）
# 思路：把 (nums1, nums2) 按 nums2 升序排序，越早操作的元素会多付几次 nums2；再做背包式 DP，f[i][j] 表示前 i 个元素里选 j 个（共操作 j 秒）能减掉的最大和，最后枚举最小的可行秒数 j。
# 时间复杂度：O(n^2)，两层 DP 循环；空间复杂度：O(n^2)，二维 DP 表。
class Solution:  # LeetCode 约定的题解类
    def minimumTime(self, nums1: List[int], nums2: List[int], x: int) -> int:  # nums1/nums2：两个等长数组；x：目标和；返回最少秒数
        n = len(nums1)  # n：数组长度，最多只需 n 秒（每秒操作一个下标）
        f = [[0] * (n + 1) for _ in range(n + 1)]  # f[i][j]：前 i 个元素中选 j 个操作（共 j 秒）能减少的最大和
        for i, (a, b) in enumerate(sorted(zip(nums1, nums2), key=lambda z: z[1]), 1):  # 按 nums2 升序排序后枚举，i 从 1 开始计数；同时解包出 a=nums1 值、b=nums2 值
            for j in range(n + 1):  # 枚举一共操作了几秒（也就是选了几个元素）
                f[i][j] = f[i - 1][j]  # 不选当前元素：直接继承上一行的最优值
                if j > 0:  # 只有 j > 0 才可能发生「选它」的转移
                    f[i][j] = max(f[i][j], f[i - 1][j - 1] + a + b * j)  # 选它：它排在第 j 秒被操作，收益是 a + b * j（b 要多付 j 次）
        s1 = sum(nums1)  # nums1 的元素和，即一次都不操作时的总和
        s2 = sum(nums2)  # nums2 的元素和，每过一秒所有尚未归零的元素都会再加一遍
        for j in range(n + 1):  # 从小到大枚举秒数，第一个可行的即最少时间
            if s1 + s2 * j - f[n][j] <= x:  # j 秒后的总和 = s1 + s2 * j 减去最大减少量 f[n][j]
                return j  # 已经不超过 x，直接返回 j
        return -1  # 全部枚举完仍不满足，返回 -1 表示无解
