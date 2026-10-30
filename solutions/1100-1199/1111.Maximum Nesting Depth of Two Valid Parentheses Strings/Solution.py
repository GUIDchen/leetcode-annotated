# 题目：1111. 有效括号的嵌套深度（Maximum Nesting Depth of Two Valid Parentheses Strings）
# 思路：按深度的奇偶性分组：'(' 用入栈前的深度判奇偶，')' 用出栈后的深度判奇偶，使两个子序列各自深度约为原来的一半。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(n)，ans 保存每个位置的分组编号。
class Solution:  # LeetCode 约定的题解类
    def maxDepthAfterSplit(self, seq: str) -> List[int]:  # seq 是题目保证合法的括号序列
        ans = [0] * len(seq)  # 答案数组：每个位置记录它被分到哪个子序列（0 或 1）
        x = 0  # 当前嵌套深度
        for i, c in enumerate(seq):  # 同时取得下标 i 与字符 c
            if c == "(":  # 左括号会让深度加一
                ans[i] = x & 1  # 用自增前的深度奇偶决定分组
                x += 1  # 进入更深一层
            else:  # 右括号会让深度减一
                x -= 1  # 先退出一层，回到配对左括号的深度
                ans[i] = x & 1  # 再用退层后的深度奇偶决定分组，保证同一对括号落在同一组
        return ans  # 返回每个位置的子序列编号
