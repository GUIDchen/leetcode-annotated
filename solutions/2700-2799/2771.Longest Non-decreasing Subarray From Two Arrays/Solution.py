# 题目：2771. 构造最长非递减子数组（Longest Non-decreasing Subarray From Two Arrays）
# 思路：线性 DP。f / g 分别表示以当前下标 i 结尾、且第 i 位取 nums1[i] / nums2[i] 时最长的非递减子数组长度，按四种前驱情况转移。
# 时间复杂度：O(n)，只遍历一遍数组；空间复杂度：O(1)，仅保存常数个状态变量。
class Solution:  # LeetCode 约定的题解类
    def maxNonDecreasingLength(self, nums1: List[int], nums2: List[int]) -> int:  # nums1、nums2 是两个等长的备选数组
        n = len(nums1)  # 数组长度（两数组等长）
        f = g = 1  # 初始状态：只看第一个元素时，选 nums1[0] 或 nums2[0] 的长度都是 1
        ans = 1  # 答案至少为 1，单个元素自成非递减子数组
        for i in range(1, n):  # 从下标 1 开始逐个向右扩展子数组
            ff = gg = 1  # 本层的新状态，先按“只含当前元素”初始化
            if nums1[i] >= nums1[i - 1]:  # 情况一：当前位与前一位都选 nums1，且值不下降
                ff = max(ff, f + 1)  # 可以接在 f 后面，长度加一
            if nums1[i] >= nums2[i - 1]:  # 情况二：当前位选 nums1、前一位选 nums2，且值不下降
                ff = max(ff, g + 1)  # 可以接在 g 后面，长度加一
            if nums2[i] >= nums1[i - 1]:  # 情况三：当前位选 nums2、前一位选 nums1，且值不下降
                gg = max(gg, f + 1)  # 可以接在 f 后面，长度加一
            if nums2[i] >= nums2[i - 1]:  # 情况四：当前位与前一位都选 nums2，且值不下降
                gg = max(gg, g + 1)  # 可以接在 g 后面，长度加一
            f, g = ff, gg  # 滚动更新：用本层结果覆盖旧状态，保证下一轮只用当前层
            ans = max(ans, f, g)  # 两种结尾方式中的较大者参与更新全局答案
        return ans  # 返回最长非递减子数组的长度
