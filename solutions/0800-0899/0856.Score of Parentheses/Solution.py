# 题目：856. 括号的分数（Score of Parentheses）
# 思路：记录当前嵌套深度 d；遇到相邻的 "()" 这一最小单元时，它对答案的贡献是 2^d（d 为匹配后所在深度）。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用两个变量。
class Solution:  # 题解类
    def scoreOfParentheses(self, s: str) -> int:  # s 是合法的括号字符串
        ans = d = 0  # ans 累计分数，d 为当前嵌套深度
        for i, c in enumerate(s):  # 同时取下标与字符，便于回看前一个字符
            if c == '(':  # 左括号：深度加一
                d += 1  # 进入更深一层
            else:  # 右括号：先退出一层
                d -= 1  # 得到这一对括号所在的深度
                if s[i - 1] == '(':  # 形如 "()" 的最小单元贡献 2^d
                    ans += 1 << d  # 1 << d 即 2 的 d 次方
        return ans  # 返回总得分
