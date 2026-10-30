# 题目：341. 扁平化嵌套列表迭代器（Flatten Nested List Iterator）
# 核心思路：初始化时用 DFS 把嵌套列表一次性展平成一维列表，next/hasNext 只需按下标顺序返回元素。
# 时间复杂度：初始化 O(N) 展平全部元素，next/hasNext 均为 O(1)；空间复杂度：O(N)，用一个列表保存所有整数。
# """
# This is the interface that allows for creating nested lists.
# You should not implement it, or speculate about its implementation
# """
# class NestedInteger:
#    def isInteger(self) -> bool:
#        """
#        @return True if this NestedInteger holds a single integer, rather than a nested list.
#        """
#
#    def getInteger(self) -> int:
#        """
#        @return the single integer that this NestedInteger holds, if it holds a single integer
#        Return None if this NestedInteger holds a nested list
#        """
#
#    def getList(self) -> [NestedInteger]:
#        """
#        @return the nested list that this NestedInteger holds, if it holds a nested list
#        Return None if this NestedInteger holds a single integer
#        """


class NestedIterator:  # 迭代器类：先把嵌套列表展平成列表，再按下标逐个取出
    def __init__(self, nestedList: [NestedInteger]):  # 构造函数：把传入的嵌套列表一次性展平
        def dfs(ls):  # 内部递归函数，负责展平任意一层列表
            for x in ls:  # 遍历当前层的每个元素
                if x.isInteger():  # 元素是单个整数
                    self.nums.append(x.getInteger())  # 按顺序追加到结果列表
                else:  # 元素是子列表
                    dfs(x.getList())  # 递归展平子列表

        self.nums = []  # 先建好结果列表，供上面的 dfs 闭包写入
        self.i = -1  # 当前已返回元素的下标，从 -1 开始（下次 next 时先加一）
        dfs(nestedList)  # 调用 dfs 完成展平

    def next(self) -> int:  # 返回下一个整数
        self.i += 1  # 下标前移一位
        return self.nums[self.i]  # 返回该下标处的元素

    def hasNext(self) -> bool:  # 判断是否还有下一个整数
        return self.i + 1 < len(self.nums)  # 下标 i+1 未越界就说明还有元素


# Your NestedIterator object will be instantiated and called as such:
# i, v = NestedIterator(nestedList), []
# while i.hasNext(): v.append(i.next())
