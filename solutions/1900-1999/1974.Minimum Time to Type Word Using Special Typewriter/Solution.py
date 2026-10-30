# 题目：1974. 使用特殊打字机键入单词的最少时间（Minimum Time to Type Word Using Special Typewriter）
# 思路：指针初始在 'a'，依次走到每个待键入字符；环形字母表上取顺时针与逆时针距离的较小值，再为每次按键累加 1 秒。
# 时间复杂度：O(n)，只需遍历一遍单词；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minTimeToType(self, word: str) -> int:  # word：待键入的单词
        ans, a = len(word), ord("a")  # ans 先装入按键耗时 n 秒；a 是指针所在字符的 ASCII 码，初始为 'a'
        for c in map(ord, word):  # 把每个字符映射成 ASCII 码后依次处理
            d = abs(c - a)  # 两个字符 ASCII 码之差的绝对值，即在字母表上的直线距离
            ans += min(d, 26 - d)  # 环形字母表上取顺时针/逆时针中较近的一边，累加移动耗时
            a = c  # 指针移到当前字符，作为下一次移动的起点
        return ans  # 返回总耗时（移动时间 + 按键时间）
