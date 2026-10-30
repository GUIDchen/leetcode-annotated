# 题目：339. 嵌套列表加权和（Nested List Weight Sum）
# 核心思路：对嵌套列表做 DFS，整数按其所在深度加权后累加；每下探一层深度加 1，根层深度为 1。
# 时间复杂度：O(N)，N 为所有整数元素的个数；空间复杂度：O(D)，D 为最大嵌套深度（递归栈）。
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
class Solution:  # LeetCode 约定的题解类
    def depthSum(self, nestedList: List[NestedInteger]) -> int:  # nestedList 是根层嵌套列表，返回按深度加权的元素和
        def dfs(nestedList, depth):  # 内部 DFS：处理一层嵌套列表，depth 是当前层的深度权重
            depth_sum = 0  # 本层加权和的累加器，从 0 开始
            for item in nestedList:  # 遍历这一层的每个元素
                if item.isInteger():  # 元素是单个整数
                    depth_sum += item.getInteger() * depth  # 整数按当前深度加权后累加
                else:  # 元素是子列表
                    depth_sum += dfs(item.getList(), depth + 1)  # 递归下探一层，深度加 1，把子树的和累加进来
            return depth_sum  # 返回本层的加权和

        return dfs(nestedList, 1)  # 从根层（深度 1）开始递归求加权和
