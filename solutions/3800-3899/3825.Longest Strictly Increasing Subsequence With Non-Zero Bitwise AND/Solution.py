# 3825. Longest Strictly Increasing Subsequence With Non-Zero Bitwise AND | 3825. 按位与结果非零的最长上升子序列
# 核心思路：按位与非零等价于存在某一位全为 1，枚举该位筛出元素后求最长严格上升子序列，所有位取最大值
# 复杂度：时间 O(log M · n log n)，空间 O(n)
class Solution:
    def longestSubsequence(self, nums: List[int]) -> int:  # 求按位与结果非零的最长严格递增子序列长度
        def lis(arr: List[int]) -> int:  # 求 arr 的最长严格上升子序列长度（贪心 + 二分，即耐心排序）
            g = []  # g[i] 表示长度为 i+1 的上升子序列中可能的最小结尾值
            for x in arr:  # 依次处理 arr 中的每个元素
                j = bisect_left(g, x)  # 找到第一个大于等于 x 的位置
                if j == len(g):  # x 比所有结尾都大
                    g.append(x)  # 说明可以接出更长的上升子序列
                else:  # 否则替换同长度的结尾值
                    g[j] = x  # 让该长度的结尾更小，便于后续继续延长
            return len(g)  # g 的长度即最长严格上升子序列长度

        ans = 0  # 答案初始为 0
        m = max(nums).bit_length()  # 最大值的二进制位数，即需要枚举的位数上界
        for i in range(m):  # 枚举子序列全体共同为 1 的那一位
            arr = [x for x in nums if x >> i & 1]  # 该位为 1 的元素按原相对顺序组成的候选序列
            ans = max(ans, lis(arr))  # 用该位候选序列的 LIS 长度更新答案
        return ans  # 返回所有位中的最大长度
