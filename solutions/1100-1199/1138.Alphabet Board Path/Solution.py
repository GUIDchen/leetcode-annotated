# 题目：1138. 字母板上的路径（Alphabet Board Path）
# 思路：字母序号整除/取余得到坐标，按 L→U→R→D 的固定顺序逐字符移动并点击 '!'，先左后上可避免踩到不存在的格子。
# 时间复杂度：O(总移动步数 + |target|)；空间复杂度：O(总移动步数)。
class Solution:  # LeetCode 约定的题解类
    def alphabetBoardPath(self, target: str) -> str:  # target 是目标单词，返回字母板上的移动与点击指令串
        i = j = 0  # 当前坐标（行 i、列 j），起点是 'a'
        ans = []  # 用列表累积指令，最后统一拼接
        for c in target:  # 依次处理目标单词的每个字符
            v = ord(c) - ord("a")  # 字母转成 0..25 的序号
            x, y = v // 5, v % 5  # 整除取行、取余取列（每行 5 个字母）
            while j > y:  # 先左移：第 5 行只有 'z' 一格，必须先离开该行再上下走，否则会越界
                j -= 1  # 列号减 1
                ans.append("L")  # 追加 'L'
            while i > x:  # 接着向上移（行号变小）
                i -= 1  # 行号减 1
                ans.append("U")  # 追加 'U'
            while j < y:  # 再向右移
                j += 1  # 列号加 1
                ans.append("R")  # 追加 'R'
            while i < x:  # 最后向下移
                i += 1  # 行号加 1
                ans.append("D")  # 追加 'D'
            ans.append("!")  # 到达目标格后点击选中
        return "".join(ans)  # 把列表拼成字符串返回
