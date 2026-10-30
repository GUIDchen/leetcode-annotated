# 题目：1427. 字符串的左右移（Perform String Shifts）
# 思路：把每条指令折算成「右移为正、左移为负」的步数求和，对长度取模后一次切片拼接。
# 时间复杂度：O(n + m)，n 为串长、m 为指令数；空间复杂度：O(n)，拼接产生新字符串。
class Solution:  # LeetCode 约定的题解类
    def stringShift(self, s: str, shift: List[List[int]]) -> str:  # s：待平移字符串；shift[i] = [方向, 步数]，方向 0 为左移、1 为右移
        x = sum((b if a else -b) for a, b in shift)  # 方向 a 为真（1）取 +b 表示右移，否则取 -b 表示左移，求和得到净右移量
        x %= len(s)  # Python 的取模结果恒非负，直接把净步数折到 [0, len(s)) 内
        return s[-x:] + s[:-x]  # 右移 x 步：末尾 x 个字符移到前面；x 为 0 时两段切片分别是空串与原串，结果不变
