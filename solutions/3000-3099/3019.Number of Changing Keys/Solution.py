# 题目：3019. 按键变更的次数（Number of Changing Keys）
# 思路：s.lower() 统一小写，pairwise 生成相邻字符对，统计其中 a != b 的对数即按键变更次数。
# 时间复杂度：O(n)，n 为字符串长度，只需一趟遍历；空间复杂度：O(n)，lower() 会生成一个新字符串（辅助计数用常数空间）。
class Solution:  # LeetCode 约定的题解类
    def countKeyChanges(self, s: str) -> int:  # s 是按键序列，返回需要变更按键的次数
        return sum(a != b for a, b in pairwise(s.lower()))  # s.lower() 统一小写，pairwise 产出相邻二元组 (a, b)，把 a != b 的布尔值求和即为变更次数
