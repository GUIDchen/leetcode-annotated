# 题目：1929. 数组串联（Concatenation of Array）
# 思路：Python 列表相加会生成新列表，nums + nums 即为长度 2n 的串联结果。
# 时间复杂度：O(n)，需要复制 2n 个元素；空间复杂度：O(n)，返回的新列表长度为 2n。
class Solution:  # LeetCode 约定的题解类
    def getConcatenation(self, nums: List[int]) -> List[int]:  # nums：原数组
        return nums + nums  # 列表拼接：原数组接上自身，直接作为答案返回
