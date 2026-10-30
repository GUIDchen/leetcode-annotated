# 题目：364. 嵌套列表加权和 II（Nested List Weight Sum II）
# 思路：DFS 同时求最大深度 maxDepth、元素总和 s 与按真实深度加权的和 ws，答案 = (maxDepth+1)*s - ws 即按反深度加权。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归深度 h。
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
class Solution:  # LeetCode 题解类
    def depthSumInverse(self, nestedList: List[NestedInteger]) -> int:  # nestedList 是嵌套列表的根层元素集合
        def dfs(x, d):  # 内层递归函数：x 是当前节点，d 是当前深度
            nonlocal maxDepth, s, ws  # 声明要修改外层的三个统计变量
            maxDepth = max(maxDepth, d)  # 维护遍历到的最大深度
            if x.isInteger():  # 是单个整数则直接累加
                s += x.getInteger()  # 累加原始值到 s
                ws += x.getInteger() * d  # 按「当前深度」加权计入 ws
            else:  # 否则是嵌套列表
                for y in x.getList():  # 遍历每个子元素
                    dfs(y, d + 1)  # 子元素深度加一递归

        maxDepth = s = ws = 0  # 初始化最大深度、元素总和、深度加权和
        for x in nestedList:  # 遍历根层的每个元素
            dfs(x, 1)  # 根层深度为 1，开始 DFS
        return (maxDepth + 1) * s - ws  # 反深度权 = (maxDepth+1-d)，展开后即 (maxDepth+1)*s - ws
