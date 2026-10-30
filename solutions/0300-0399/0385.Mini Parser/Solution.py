# 题目：385. 迷你语法分析器（Mini Parser）
# 思路：递归下降；按深度为 0 的逗号或结尾把内层切成若干段子串递归解析，首字符不是 '[' 时整段就是一个整数。
# 时间复杂度：O(n^2)，每层递归都要扫描并切分字符串；空间复杂度：O(n)，递归栈深度与嵌套层数同阶。
# """
# This is the interface that allows for creating nested lists.
# You should not implement it, or speculate about its implementation
# """
# class NestedInteger:
#    def __init__(self, value=None):
#        """
#        If value is not specified, initializes an empty list.
#        Otherwise initializes a single integer equal to value.
#        """
#
#    def isInteger(self):
#        """
#        @return True if this NestedInteger holds a single integer, rather than a nested list.
#        :rtype bool
#        """
#
#    def add(self, elem):
#        """
#        Set this NestedInteger to hold a nested list and adds a nested integer elem to it.
#        :rtype void
#        """
#
#    def setInteger(self, value):
#        """
#        Set this NestedInteger to hold a single integer equal to value.
#        :rtype void
#        """
#
#    def getInteger(self):
#        """
#        @return the single integer that this NestedInteger holds, if it holds a single integer
#        Return None if this NestedInteger holds a nested list
#        :rtype int
#        """
#
#    def getList(self):
#        """
#        @return the nested list that this NestedInteger holds, if it holds a nested list
#        Return None if this NestedInteger holds a single integer
#        :rtype List[NestedInteger]
#        """
class Solution:  # 题解类
    def deserialize(self, s: str) -> NestedInteger:  # s 是不含空格的序列化字符串，返回对应的 NestedInteger 结构
        if not s or s == '[]':  # 空串或空列表，都表示一个不装东西的嵌套列表
            return NestedInteger()  # 无参构造出来的就是空列表
        if s[0] != '[':  # 首字符不是 '['，说明整段就是一个整数
            return NestedInteger(int(s))  # int() 转成整数，再包成单值节点
        ans = NestedInteger()  # 当前这一层要构造的嵌套列表
        depth, j = 0, 1  # depth 记录未配对的 '[' 层数，j 记录本层当前子串的起点
        for i in range(1, len(s)):  # i 从 1 开始，跳过开头的 '['
            if depth == 0 and (s[i] == ',' or i == len(s) - 1):  # 在本层遇到逗号，或已到闭括号前的最后一个字符，说明一段结束
                ans.add(self.deserialize(s[j:i]))  # 切出 s[j:i] 递归解析，并挂到当前列表下
                j = i + 1  # 下一段的起点跳过这个逗号
            elif s[i] == '[':  # 遇到 '[' 表示进入更深一层
                depth += 1  # 层数加一，此后的逗号属于内层
            elif s[i] == ']':  # 遇到 ']' 表示退回上一层
                depth -= 1  # 层数减一
        return ans  # 返回这一层解析出的嵌套列表
