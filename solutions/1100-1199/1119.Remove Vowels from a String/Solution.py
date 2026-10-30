# 题目：1119. 删去字符串中的元音（Remove Vowels from a String）
# 思路：用生成器表达式过滤掉 a/e/i/o/u，再以空串拼接，等价于一次遍历且保持原顺序。
# 时间复杂度：O(n)，每个字符判断并拼接一次；空间复杂度：O(n)，需要存放结果字符串。
class Solution:  # LeetCode 约定的题解类
    def removeVowels(self, s: str) -> str:  # 返回删除全部元音后的新字符串
        return "".join(c for c in s if c not in "aeiou")  # 生成器筛出非元音字符，"".join 把它们原序拼成一个新串
