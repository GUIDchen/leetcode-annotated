# 题目：496. 下一个更大元素 I（Next Greater Element I）
# 思路：从右往左扫描 nums2，用单调栈维护右侧候选值，栈顶就是最近的那个更大元素，结果记入哈希表后再按 nums1 的顺序查表回答。
# 时间复杂度：O(m + n)，每个元素最多进栈、出栈各一次；空间复杂度：O(n)，栈与哈希表各最多存 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def nextGreaterElement(self, nums1: List[int], nums2: List[int]) -> List[int]:  # nums1 是查询数组，nums2 是母数组，nums1 中的每个值都能在 nums2 中找到
        stk = []  # 单调栈：从栈底到栈顶递减，栈顶是当前元素右边最近的更大候选
        d = {}  # 哈希表：键是 nums2 中的元素，值是它的下一个更大元素
        for x in nums2[::-1]:  # 反转后从右往左扫描，保证栈里保存的都是当前元素右侧的元素
            while stk and stk[-1] < x:  # 比当前元素小的栈顶值永远不会成为别人的下一个更大元素，直接弹出
                stk.pop()  # 弹出较小值，维持单调性
            if stk:  # 栈非空则栈顶就是 x 右侧第一个更大的元素
                d[x] = stk[-1]  # 记录映射关系
            stk.append(x)  # 当前元素入栈，供它左侧的元素查询
        return [d.get(x, -1) for x in nums1]  # 逐个查表：有记录就取值，没有则按题意返回 -1
