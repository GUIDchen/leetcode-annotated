# 题目：3542. 将所有元素变为 0 的最少操作次数（Minimum Operations to Convert All Elements to Zero）
# 思路：用单调递增栈维护当前尚未结算的层级，遇到更小的值就把被截断的层依次结算，最后把栈中剩余的层一次性计入答案。
# 时间复杂度：O(n)，每个元素最多入栈、出栈各一次；空间复杂度：O(n)，栈最多保存 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int]) -> int:  # nums：非负整数数组
        stk = []  # 单调递增栈，保存尚未结算的正数层级
        ans = 0  # 已经统计出的操作次数
        for x in nums:  # 从左到右扫描数组
            while stk and stk[-1] > x:  # 栈顶比当前值大，说明这一层到这里被截断
                ans += 1  # 被截断的这一层单独贡献一次操作
                stk.pop()  # 弹出已经结算的层级
            if x and (not stk or stk[-1] != x):  # 当前值非 0 且与栈顶不同，才需要新开一层
                stk.append(x)  # 记录这一层，后面相同的值可以复用同一段操作
        ans += len(stk)  # 栈中剩余的每个层级都还需要一次独立操作
        return ans  # 返回最少操作次数
