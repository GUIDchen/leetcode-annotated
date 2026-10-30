# 题目：2219. 数组的最大总分（Maximum Sum Score of Array）
# 思路：维护左前缀和 l 与右后缀和 r，遍历每个下标求两者的较大值，再在所有下标的结果里取最大。
# 时间复杂度：O(n)，求总和与遍历各一次；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maximumSumScore(self, nums: List[int]) -> int:  # nums：输入数组，返回所有下标得分中的最大值
        l, r = 0, sum(nums)  # l 是左前缀和，r 先取整个数组的总和
        ans = -inf  # 用负无穷初始化答案，保证任何得分都能覆盖它
        for x in nums:  # 从左到右依次把当前元素当作分割点
            l += x  # 把 x 并入左半部分，l 变成「包含 x 的前缀和」
            ans = max(ans, l, r)  # 当前下标的得分是 max(前缀和, 后缀和)，用它刷新答案
            r -= x  # 把 x 从右半部分拿掉，让 r 成为下一个位置的后缀和
        return ans  # 返回所有下标得分中的最大值
