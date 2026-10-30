# 题目：456. 132 模式（132 Pattern）
# 思路：逆序遍历，单调栈保存候选的「3」，vk 记录已确认的最大「2」；遇到比 vk 小的元素即找到 132。
# 时间复杂度：O(n)，每个元素最多入栈出栈一次；空间复杂度：O(n)，栈最多存 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def find132pattern(self, nums: List[int]) -> bool:  # nums 是待判断的数组，返回是否存在 132 模式
        vk = -inf  # vk 保存已确认的「2」的最大值，-inf 表示还没有任何「2」
        stk = []  # 单调栈：从栈底到栈顶递减，栈内元素都能充当「3」
        for x in nums[::-1]:  # 逆序遍历（nums[::-1] 生成反转副本），x 充当模式中最左侧的「1」
            if x < vk:  # 当前元素比已找到的「2」还小，说明 1<2<3 成立
                return True  # 存在 132 模式，返回真
            while stk and stk[-1] < x:  # 把栈中所有小于当前元素的元素弹出，它们可以充当新的「2」
                vk = stk.pop()  # 弹出的元素即候选「2」，取其中最大的
            stk.append(x)  # 当前元素入栈，作为可能的「3」
        return False  # 遍历完仍未找到 132 模式
