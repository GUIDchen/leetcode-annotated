# 题目：1880. 检查某单词是否等于两单词之和（Check if Word Equals Summation of Two Words）
# 思路：把每个字母映射成数字（'a'->0、'b'->1……'j'->9），按十进制逐位拼成整数，最后判断 first + second == target。
# 时间复杂度：O(L)，L 为三个字符串的总长度；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def isSumEqual(self, firstWord: str, secondWord: str, targetWord: str) -> bool:  # firstWord、secondWord、targetWord：三个只含小写字母的单词
        def f(s: str) -> int:  # 局部函数：把字母串翻译成对应的十进制数（'a' 当 0）
            ans, a = 0, ord("a")  # ans：累计数值；a：字母 'a' 的 ASCII 码，供后面相减
            for c in map(ord, s):  # 逐字符取其 ASCII 码
                x = c - a  # 该字母对应的数字 0..9
                ans = ans * 10 + x  # 十进制左移一位，再加上当前数字
            return ans  # 返回整个单词对应的数值
        # 空行：下面的 return 仍属于方法体，缩进保持方法级别

        return f(firstWord) + f(secondWord) == f(targetWord)  # 直接比较前两词之和与目标词
