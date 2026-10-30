# 题目：1950. 所有子数组最小值中的最大值（Maximum of Minimum Values in All Subarrays）
# 思路：单调栈求每个元素左右第一个严格更小值的下标，得到以它为最小值的最大窗口长度，再按长度取最大值并做后缀最大值。
# 时间复杂度：O(n)，两次单调栈加一次线性扫描；空间复杂度：O(n)，左右边界数组与栈。
class Solution:  # LeetCode 约定的题解类
    def findMaximums(self, nums: List[int]) -> List[int]:  # nums：输入数组
        n = len(nums)  # 记录数组长度
        left = [-1] * n  # left[i]：i 左边第一个严格更小元素的下标，默认 -1
        right = [n] * n  # right[i]：i 右边第一个严格更小元素的下标，默认 n
        stk = []  # 单调递增栈，存下标，对应元素值严格递增
        for i, x in enumerate(nums):  # 从左往右求 left
            while stk and nums[stk[-1]] >= x:  # 栈顶值不小于当前值，不能当作左边界
                stk.pop()  # 弹出，保持栈内元素严格递增
            if stk:  # 栈顶就是左边第一个更小值
                left[i] = stk[-1]  # 记下左边界下标
            stk.append(i)  # 当前下标入栈，作为后面元素的候选左边界
        stk = []  # 清空栈，复用于从右往左的扫描
        for i in range(n - 1, -1, -1):  # 从右往左求 right
            while stk and nums[stk[-1]] >= nums[i]:  # 同样维护严格递增栈
                stk.pop()  # 弹出不满足严格更小的元素
            if stk:  # 栈顶就是右边第一个更小值
                right[i] = stk[-1]  # 记下右边界下标
            stk.append(i)  # 当前下标入栈
        ans = [0] * n  # ans[k-1] 表示长度为 k 的子数组其最小值的最大可能值
        for i in range(n):  # 逐个元素作为区间最小值来考察
            m = right[i] - left[i] - 1  # 以 nums[i] 为最小值时能覆盖的最大窗口长度
            ans[m - 1] = max(ans[m - 1], nums[i])  # 该长度下取更大的最小值
        for i in range(n - 2, -1, -1):  # 从后往前做后缀最大值
            ans[i] = max(ans[i], ans[i + 1])  # 更短的子数组总能从更长窗口里取到，故答案单调不降
        return ans  # 返回每个长度对应的最大最小值
