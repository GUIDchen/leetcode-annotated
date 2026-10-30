# 题目：2270. 分割数组的方案数（Number of Ways to Split Array）
# 思路：先求总和 s，再从左往右累加左半和 t，每次判断 t >= s - t 即左半和不小于右半和时方案数加一。
# 时间复杂度：O(n)，求和与一次遍历；空间复杂度：O(1)，只使用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def waysToSplitArray(self, nums: List[int]) -> int:  # nums：输入数组；返回满足「左半和 >= 右半和」的分割方案数
        s = sum(nums)  # 数组总和，用总和减左半和即可 O(1) 得到右半和
        ans = t = 0  # ans：方案数；t：当前分割点左边元素的前缀和
        for x in nums[:-1]:  # 遍历除最后一个元素外的所有位置，保证右半部分非空
            t += x  # 把当前元素归入左半部分
            ans += t >= s - t  # 左半和 t 不小于右半和 s - t 时，布尔值 True 参与加法使计数加一
        return ans  # 返回合法方案数
