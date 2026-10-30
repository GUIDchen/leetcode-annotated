# 题目：3330. 找到初始输入字符串 I（Find the Original Typed String I）
# 思路：原串至少可以是 word 本身；每对相邻且相同的字符都可能是一次多按，所以答案是 1 加上这类相邻对的数量。
# 时间复杂度：O(n)，pairwise 只遍历一遍；空间复杂度：O(1)，除生成器外只用常数空间。
class Solution:  # LeetCode 约定的题解类
    def possibleStringCount(self, word: str) -> int:  # word 是敲出来的字符串，其中某些字符可能被多敲了一次
        return 1 + sum(x == y for x, y in pairwise(word))  # 1 是原串就等于 word 的情况；每个相邻相等对再多一种可能
