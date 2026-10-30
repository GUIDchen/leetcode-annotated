# 3834. 合并相邻且相等的元素 / Merge Adjacent Equal Elements（中等）
# 核心思路：用列表模拟栈；每处理一个元素就压栈，若栈顶两元素相等则弹出两者、把和压回，并用 while 反复检查，因为新和可能再次与栈顶相等。
# 复杂度：每个元素最多入栈一次，摊还时间 O(n)，空间 O(n)。
class Solution:  # 反复合并相邻且相等的元素，直到无法再合并
    def mergeAdjacent(self, nums: List[int]) -> List[int]:  # 返回合并完成后的数组
        stk = []  # 用列表模拟栈，保存已合并好的结果前缀
        for x in nums:  # 从左到右依次处理每个元素
            stk.append(x)  # 把当前元素压栈
            while len(stk) > 1 and stk[-1] == stk[-2]:  # 栈顶两个元素相等时持续合并（和可能再次与栈顶相等）
                stk.append(stk.pop() + stk.pop())  # 连续弹出两个相等元素并把它们的和压回（加法可交换，弹出顺序不影响结果）
        return stk  # 栈中内容即为最终结果
