# 题目：2116. 判断一个括号字符串是否有效（Check if a Parentheses String Can Be Valid）
# 思路：先判长度奇偶；正序检查固定的右括号是否总能被左侧左括号（含可改位）配对，逆序再检查固定的左括号。
# 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(1)，只用一个计数器 x。
class Solution:# LeetCode 约定的题解类
    def canBeValid(self, s: str, locked: str) -> bool:# s：括号串；locked[i]=='1' 表示该位不可改动；返回能否变成合法括号串
        n = len(s)# 字符串长度
        if n & 1:# 长度为奇数绝不可能完全配对
            return False# 直接判失败
        x = 0# 正序遍历时的「未配对左括号」计数，可改位也能充当左括号
        for i in range(n):# 从左到右扫描
            if s[i] == '(' or locked[i] == '0':# 本来就是左括号，或该位可自由改动
                x += 1# 都可以贡献一个左括号
            elif x:# 遇到固定的右括号，且左侧还有左括号可与它配对
                x -= 1# 消耗一个左括号
            else:# 没东西可配，说明这个前缀里右括号太多
                return False# 无论如何都补不回来
        x = 0# 复用变量，改为统计「未配对右括号」
        for i in range(n - 1, -1, -1):# 从右到左逆序扫描
            if s[i] == ')' or locked[i] == '0':# 本来就是右括号，或该位可自由改动
                x += 1# 都可以贡献一个右括号
            elif x:# 遇到固定的左括号，且右侧还有右括号可与它配对
                x -= 1# 消耗一个右括号
            else:# 没东西可配，说明这个后缀里左括号太多
                return False# 无论如何都补不回来
        return True# 两个方向都不矛盾，说明能构造出合法括号串
