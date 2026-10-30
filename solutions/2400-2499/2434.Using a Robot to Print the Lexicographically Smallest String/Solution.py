# 题目：2434. 使用机器人打印字典序最小的字符串（Using a Robot to Print the Lexicographically Smallest String）
# 思路：用 Counter 统计各字母剩余次数，用 mi 维护尚未打印的最小字母；字符先入栈，栈顶不超过 mi 时立刻出栈写入答案。
# 时间复杂度：O(26n) 即 O(n)，每个字符进出栈各一次、mi 最多前移 26 次；空间复杂度：O(n)，栈与答案各占 O(n)。
class Solution:  # LeetCode 约定的题解类
    def robotWithString(self, s: str) -> str:  # s：输入字符串，返回机器人打印出的字典序最小结果
        cnt = Counter(s)  # 频次表：键是字母，值是该字母在 s 中剩余的个数（判题器已提供 Counter）
        ans = []  # 收集机器人依次打印出的字符，最后再拼接成字符串
        stk = []  # 模拟机器人的栈：取出的字符先暂存在这里
        mi = 'a'  # mi 表示当前还没打印的最小字母，初始从 'a' 开始向右找
        for c in s:  # 按原顺序把 s 的字符一个个送进机器人
            cnt[c] -= 1  # 当前字符已被取出，剩余次数减一，使 cnt 始终代表「还没处理的字符」
            while mi < 'z' and cnt[mi] == 0:  # 剩余次数为 0 的字母已不可能再打印，继续向后找
                mi = chr(ord(mi) + 1)  # 用 ASCII 码加一得到下一个字母
            stk.append(c)  # 机器人把当前字符压入栈
            while stk and stk[-1] <= mi:  # 栈顶不大于剩余最小字母时，现在打印它不会让字典序变差
                ans.append(stk.pop())  # 弹出栈顶字符并追加到答案
        return ''.join(ans)  # 把字符列表拼接成最终字符串返回
