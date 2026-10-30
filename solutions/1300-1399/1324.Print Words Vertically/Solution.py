# 题目：1324. 竖直打印单词（Print Words Vertically）
# 思路：s.split() 按空白切出所有单词，最长单词长度 n 即输出行数；逐列 j 取每个单词第 j 个字符（越界补空格），去掉行尾空格后作为第 j 行。
# 时间复杂度：O(n * L)，L 为单词个数；空间复杂度：O(n * L)，存放全部输出字符。
class Solution:  # 题解类
    def printVertically(self, s: str) -> List[str]:  # s：空格分隔的单词串，返回竖直打印后的各行
        words = s.split()  # 按任意空白切分，自动丢掉多余空格
        n = max(len(w) for w in words)  # 最长单词的长度决定要输出多少行
        ans = []  # 结果列表，一行一个字符串
        for j in range(n):  # 逐列（从 0 到 n-1）生成输出
            t = [w[j] if j < len(w) else ' ' for w in words]  # 取每个单词的第 j 个字符，越界时用空格占位
            while t[-1] == ' ':  # 去掉行尾空格：只保留真正有字符的部分
                t.pop()  # 尾字符是空格就弹出
            ans.append(''.join(t))  # 把字符列表拼成字符串并加入结果
        return ans  # 返回所有列
