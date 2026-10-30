# 题目：2786. 访问数组中的位置使分数最大（Visit Array Positions to Maximize Score）
# 核心思路：按奇偶性分两状态的线性 DP。f[p] 表示最后停留位置奇偶性为 p 时的最大得分；从同奇偶位置接过来不扣 x，从另一奇偶接过来扣 x，再加当前值。
# 时间复杂度：O(n)，每个元素常数次运算；空间复杂度：O(1)，只维护两个状态。
class Solution:  # LeetCode 约定的题解类
    def maxScore(self, nums: List[int], x: int) -> int:  # nums：数组；x：切换奇偶性要扣的分数；返回最高分数
        f = [-inf] * 2  # f[p]：最后停留位置奇偶性为 p 时的最大得分，-inf 表示不可达
        f[nums[0] & 1] = nums[0]  # 必须从下标 0 出发，所以只有 nums[0] 所在的奇偶状态可达
        for v in nums[1:]:  # 逐个尝试后面的元素作为新的落点
            f[v & 1] = max(f[v & 1], f[v & 1 ^ 1] - x) + v  # 同奇偶续接不扣 x，换奇偶扣 x，再加上当前值 v
        return max(f)  # 两种终态取最大值
