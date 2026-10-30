# 题目：1614. 括号的最大嵌套深度（Maximum Nesting Depth of the Parentheses）
# 思路：一次扫描，遇到左括号先深度加一再更新答案，遇到右括号深度减一；其余字符不影响深度。
# 时间复杂度：O(n)，字符串只扫一遍；空间复杂度：O(1)，只用两个整型变量。
class Solution:  # LeetCode 约定的题解类
    def maxDepth(self, s: str) -> int:  # s：由括号、字母和运算符组成的合法字符串
        ans = d = 0  # 链式赋值：ans 记录历史最大深度，d 记录当前嵌套深度
        for c in s:  # 逐字符扫描整个字符串
            if c == '(':  # 遇到左括号，进入新的一层
                d += 1  # 当前深度加一
                ans = max(ans, d)  # 用当前深度更新历史最大值
            elif c == ')':  # 遇到右括号，退出一层
                d -= 1  # 当前深度减一
        return ans  # 返回扫描过程中出现的最大嵌套深度
