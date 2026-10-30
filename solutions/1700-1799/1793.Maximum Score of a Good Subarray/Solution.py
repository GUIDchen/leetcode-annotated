# 题目：1793. 好子数组的最大分数（Maximum Score of a Good Subarray）
# 思路：两遍单调栈求出每个位置左侧第一个严格更小、右侧第一个小于等于它的下标，得到以 nums[i] 为最小值的最大区间；只统计覆盖下标 k 的区间，用「最小值 × 区间长度」更新答案。
# 时间复杂度：O(n)，每个下标最多进出栈各一次；空间复杂度：O(n)，left/right 数组与栈。
class Solution:  # LeetCode 约定的题解类
    def maximumScore(self, nums: List[int], k: int) -> int:  # nums：分数数组；k：好子数组必须包含的下标
        n = len(nums)  # 数组长度
        left = [-1] * n  # left[i]：i 左边第一个严格更小值的下标，缺省 -1
        right = [n] * n  # right[i]：i 右边第一个小于等于它的下标，缺省 n
        stk = []  # 单调栈：存下标，值从栈底到栈顶递增
        for i, v in enumerate(nums):  # 从左往右扫，求 left
            while stk and nums[stk[-1]] >= v:  # 栈顶值不小于 v 就弹掉
                stk.pop()  # 弹出偏高的下标
            if stk:  # 剩下的栈顶就是左侧第一个更小值
                left[i] = stk[-1]  # 记录左边界
            stk.append(i)  # 当前下标入栈
        stk = []  # 清空栈，换成从右往左扫
        for i in range(n - 1, -1, -1):  # 倒序遍历求 right
            v = nums[i]  # 当前元素值
            while stk and nums[stk[-1]] > v:  # 这里用严格大于，与左侧条件配合避免等值重复
                stk.pop()  # 弹出更大的下标
            if stk:  # 栈顶是右侧第一个小于等于 v 的下标
                right[i] = stk[-1]  # 记录右边界
            stk.append(i)  # 下标入栈
        ans = 0  # 答案初值
        for i, v in enumerate(nums):  # 枚举区间最小值的位置
            if left[i] + 1 <= k <= right[i] - 1:  # 链式比较：区间必须覆盖 k
                ans = max(ans, v * (right[i] - left[i] - 1))  # 最小值 × 最大区间长度
        return ans  # 返回最大分数
