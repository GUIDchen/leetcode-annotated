# 题目：2683. 相邻值的按位异或（Neighboring Bitwise XOR）
# 思路：原数组相邻异或一圈后每项出现两次，整体异或必为 0；故 derived 全体异或为 0 就等价于原数组存在。
# 时间复杂度：O(n)，一次归约；空间复杂度：O(1)，只保留一个中间结果。
class Solution:  # LeetCode 约定的题解类
    def doesValidArrayExist(self, derived: List[int]) -> bool:  # derived 是相邻异或得到的结果数组
        return reduce(xor, derived) == 0  # 用 reduce 把所有元素异或起来，结果为 0 说明存在合法原数组
