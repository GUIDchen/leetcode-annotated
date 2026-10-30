# 题目：3174. 清除数字（Clear Digits）
# 思路：列表当栈，字母入栈、遇数字弹出栈顶（删除左边最近的字母），最后拼接栈内容。
# 时间复杂度：O(n)，每个字符进出栈各一次；空间复杂度：O(n)，栈最多 n 个字符。
class Solution:  # LeetCode 约定的题解类
    def clearDigits(self, s: str) -> str:  # s 是小写字母与数字混合的字符串，返回删除所有数字后的字符串
        stk = []  # stk 当作栈使用，保存还没被数字删掉的字母
        for c in s:  # 从左到右扫描每个字符
            if c.isdigit():  # 判断当前字符是不是数字
                stk.pop()  # 数字会删掉它左边最近的字母，即栈顶元素
            else:  # 否则是字母，入栈保留下来
                stk.append(c)  # 字母入栈，等待后面可能出现的数字
        return "".join(stk)  # 把栈中剩下的字母拼成最终字符串
