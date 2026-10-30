# 题目：2036. 最大交替子数组和（Maximum Alternating Subarray Sum）
# 思路：动态规划。f 表示以当前元素结尾且当前元素取正号的最大交替和，g 表示当前元素取负号的最大交替和；转移为 f = max(g, 0) + x、g = f_old - x，答案取三者最大值。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maximumAlternatingSubarraySum(self, nums: List[int]) -> int:  # nums 是输入数组，返回任意子数组的最大交替和
        ans = f = g = -inf  # ans 记录全局最优，f/g 为两种结尾状态，初始都用 -inf 表示不可达
        for x in nums:  # 遍历数组中的每个元素
            f, g = max(g, 0) + x, f - x  # 元组同时赋值：右边用的是旧的 f 和 g，所以 g 依赖的是上一轮的 f
            ans = max(ans, f, g)  # 答案可能停在正号或负号的位置，两者一起比较
        return ans  # 返回最大交替子数组和
