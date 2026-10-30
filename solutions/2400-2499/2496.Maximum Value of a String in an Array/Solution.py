# 题目：2496. 数组中字符串的最大值（Maximum Value of a String in an Array）
# 思路：单个字符串全为数字时取数值，否则取长度；用内层函数统一换算后对全部元素求最大。
# 时间复杂度：O(所有字符总数)；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maximumValue(self, strs: List[str]) -> int:  # strs 是字符串数组，返回其中最大的「值」
        def f(s: str) -> int:  # 内层函数：把单个字符串换算成题目定义的值
            return int(s) if all(c.isdigit() for c in s) else len(s)  # 全为数字就转成整数，否则按字符串长度计值

        return max(f(s) for s in strs)  # 对所有字符串换算后取最大值，题目保证数组非空
