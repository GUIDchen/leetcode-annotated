# 题目：1526. 形成目标数组的子数组最少增加次数（Minimum Number of Increments on Subarrays to Form a Target Array）
# 核心思路：答案 = target[0] + Σ max(0, target[i] - target[i-1])，即每处上升都要新开一批子数组操作。
# 时间复杂度：O(n)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def minNumberOperations(self, target: List[int]) -> int:  # target：目标数组
        return target[0] + sum(max(0, b - a) for a, b in pairwise(target))  # target[0] 次起底，加上每一处上升的差值；pairwise 依次给出相邻的 (a, b)
