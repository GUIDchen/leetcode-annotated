# 题目：3703. 移除 K-平衡子字符串（Remove K-Balanced Substrings）
# 核心思路：用「字符 + 连续出现次数」的栈表示当前串并模拟删除：遇到右括号后，若栈顶是一段长度恰为 k 的 ')' 且其下方紧跟一段长度至少 k 的 '('，就把这两段各削去 k 个，等价于删掉最近的 k 个 '(' 与 k 个 ')'。
# 复杂度：时间 O(n)，每个字符均摊入栈出栈一次；空间 O(n)，栈最多存 n 个字符段。
class Solution:  # LeetCode 约定的题解类
    def removeSubstring(self, s: str, k: int) -> str:  # 返回反复删除所有 K-平衡子串后的结果
        stk = []  # 栈元素是 [字符, 该字符的连续个数] 这样的段
        for c in s:  # 从左到右扫描每个字符
            if stk and stk[-1][0] == c:  # 栈顶段字符相同，可以并入这一段
                stk[-1][1] += 1  # 该段长度加一
            else:  # 字符与栈顶不同，或者栈为空
                stk.append([c, 1])  # 新开一段，初始长度 1
            if c == ")" and len(stk) > 1 and stk[-1][1] == k and stk[-2][1] >= k:  # ')' 段恰好 k 个且紧邻的 '(' 段不少于 k 个，凑成 K-平衡子串
                stk.pop()  # 先弹出 ')' 段：删除 k 个右括号后该段归零
                stk[-1][1] -= k  # 再从 '(' 段削去 k 个左括号
                if stk[-1][1] == 0:  # '(' 段被削空后不应留在栈里
                    stk.pop()  # 弹出空的 '(' 段
        return "".join(c * v for c, v in stk)  # 按顺序把每个字符段重复其次数展开成结果字符串
