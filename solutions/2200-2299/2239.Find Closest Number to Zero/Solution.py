# 题目：2239. 找到最接近 0 的数字（Find Closest Number to Zero）
# 思路：一次遍历，用变量记录「当前最优数字」与它到 0 的距离；距离更小就替换，距离相同时取更大的数字。
# 时间复杂度：O(n)，只遍历数组一遍；空间复杂度：O(1)，只用常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def findClosestNumber(self, nums: List[int]) -> int:  # nums：给定的整数数组
        ans, d = 0, inf  # ans：当前最接近 0 的数字；d：它到 0 的距离，inf 表示初始无穷大
        for x in nums:  # 依次枚举数组中的每个元素
            if (y := abs(x)) < d or (y == d and x > ans):  # 海象运算符先算出距离 y；距离更小就更新，距离相同时取更大的数字
                ans, d = x, y  # 同时更新答案数字与当前的最优距离
        return ans  # 返回最接近 0 的数字
