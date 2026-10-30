# 题目：186. 反转字符串中的单词 II（Reverse Words in a String II）
# 思路：先逐个翻转单词内部字符，再整体翻转整个字符串，等价于只颠倒单词的先后顺序。
# 时间复杂度：O(n)，每个字符至多被交换两次；空间复杂度：O(1)，只用常数额外变量。
class Solution:  # LeetCode 约定的题解类
    def reverseWords(self, s: List[str]) -> None:  # s 是字符列表，要求原地修改（返回 None）
        def reverse(i: int, j: int):  # 内层函数：原地翻转 s[i..j]（闭区间）
            while i < j:  # 双指针从两端向中间靠拢，相遇即停
                s[i], s[j] = s[j], s[i]  # Python 元组解包，同时交换两个字符
                i, j = i + 1, j - 1  # 左指针右移、右指针左移，继续处理下一对

        i, n = 0, len(s)  # i 记录当前单词起点，n 是字符总数
        for j, c in enumerate(s):  # 同时取得下标 j 和字符 c，顺序扫描
            if c == " ":  # 遇到空格，说明当前单词结束
                reverse(i, j - 1)  # 翻转 s[i..j-1] 这个单词（不含空格本身）
                i = j + 1  # 下一个单词从空格后一位开始
            elif j == n - 1:  # 扫描到最后一个字符，最后一个单词没有空格收尾
                reverse(i, j)  # 单独翻转最后一个单词
        reverse(0, n - 1)  # 整体翻转，使单词顺序颠倒、单词内部恢复原样
