# 题目：1732. 找到最高海拔（Find the Highest Altitude）
# 思路：对高差数组做前缀和即得每个点的海拔，initial=0 把起点海拔 0 也纳入比较。
# 时间复杂度：O(n)，一次前缀和遍历；空间复杂度：O(n)，accumulate 内部需要保存累加状态。
class Solution:  # LeetCode 约定的题解类
    def largestAltitude(self, gain: List[int]) -> int:  # gain 是相邻两点的海拔差数组
        return max(accumulate(gain, initial=0))  # 前缀和得到各点海拔，max 取其中最大值
