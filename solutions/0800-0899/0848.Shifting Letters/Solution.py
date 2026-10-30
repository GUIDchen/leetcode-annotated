# 题目：848. 字母移位（Shifting Letters）
# 思路：从右往左累加位移量，第 i 个字母实际移动 shifts[i..n-1] 之和，累加后对 26 取模。
# 时间复杂度：O(n)，只遍历一次；空间复杂度：O(n)，把字符串转成列表后原地修改。
class Solution:  # LeetCode 约定的题解类
    def shiftingLetters(self, s: str, shifts: List[int]) -> str:  # s 是待移位的小写字母串，shifts[i] 表示前 i + 1 个字母都要移动的位数；返回移位后的字符串
        n, t = len(s), 0  # 字符串长度 n 与累计位移量 t 一起初始化
        s = list(s)  # 字符串不可变，先转成列表才能原地修改每个字符
        for i in range(n - 1, -1, -1):  # 从右往左遍历
            t += shifts[i]  # 累加位移，t 就是当前字符实际要移动的总步数
            j = (ord(s[i]) - ord("a") + t) % 26  # 偏移加上位移后对 26 取模，得到新字母的下标
            s[i] = ascii_lowercase[j]  # 用 ascii_lowercase（判题环境提供的小写字母表）取回新字母
        return "".join(s)  # 把列表重新拼成字符串返回
