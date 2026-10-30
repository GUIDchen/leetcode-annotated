# 题目：978. 最长湍流子数组（Longest Turbulent Subarray）
# 思路：线性 DP，f 表示以当前元素结尾且最后一步上升的最长湍流长度，g 表示最后一步下降的长度。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxTurbulenceSize(self, arr: List[int]) -> int:  # arr：输入数组，返回最长湍流子数组的长度
        ans = f = g = 1  # ans 记录答案；f 表示最后一步为上升的最长湍流长度，g 表示最后一步为下降的长度
        for a, b in pairwise(arr):  # pairwise 依次给出相邻的 (前一个, 当前) 元素对
            ff = g + 1 if a < b else 1  # 当前是上升时可接在「下降结尾」的 g 后面，否则湍流断裂重新从 1 开始
            gg = f + 1 if a > b else 1  # 当前是下降时可接在「上升结尾」的 f 后面，否则重新从 1 开始
            f, g = ff, gg  # 同时用新值更新 f 与 g
            ans = max(ans, f, g)  # 答案取三者最大值（含单元素构成的湍流）
        return ans  # 返回最长湍流子数组长度
