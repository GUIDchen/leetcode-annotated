# 题目：503. 下一个更大元素 II（Next Greater Element II）
# 思路：把数组复制一份接到末尾形成长度 2n 的环，从右往左扫描；用单调递减栈，栈顶即右侧第一个更大的元素。
# 时间复杂度：O(n)，每个元素最多入栈出栈各一次；空间复杂度：O(n)，答案数组与栈。
class Solution:  # LeetCode 约定的题解类
    def nextGreaterElements(self, nums: List[int]) -> List[int]:  # nums：环形数组；返回每个位置的下一个更大元素（不存在则为 -1）
        n = len(nums)  # 数组长度 n
        ans = [-1] * n  # 答案先全部置 -1，表示暂时没找到更大的元素
        stk = []  # 单调栈：从栈底到栈顶递减，存还没匹配到答案的元素值
        for i in range(n * 2 - 1, -1, -1):  # 从 2n-1 倒序遍历到 0，即把数组复制一份后从右往左扫
            i %= n  # 把扩展下标折回原数组，得到真实位置
            while stk and stk[-1] <= nums[i]:  # 栈顶不大于当前元素，未来不可能被当作“更大元素”
                stk.pop()  # 弹出这些更小或相等的元素，维持单调性
            if stk:  # 栈非空说明右边存在更大的元素
                ans[i] = stk[-1]  # 栈顶就是右边第一个更大元素
            stk.append(nums[i])  # 当前元素入栈，供更左边的位置查询
        return ans  # 返回答案数组
