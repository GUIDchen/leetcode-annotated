# 题目：284. 窥视迭代器（Peeking Iterator）
# 思路：用一个布尔标记加一个缓存值实现预读：peek 时按需取一次，next 时优先消费缓存，hasNext 把缓存计入剩余元素。
# 时间复杂度：均摊 O(1) 每次操作；空间复杂度：O(1)，只多存一个缓存元素。
# Below is the interface for Iterator, which is already defined for you.
#
# class Iterator:
#     def __init__(self, nums):
#         """
#         Initializes an iterator object to the beginning of a list.
#         :type nums: List[int]
#         """
#
#     def hasNext(self):
#         """
#         Returns true if the iteration has more elements.
#         :rtype: bool
#         """
#
#     def next(self):
#         """
#         Returns the next element in the iteration.
#         :rtype: int
#         """


class PeekingIterator:  # 包装题目给定的迭代器
    def __init__(self, iterator):  # 构造函数：iterator 是题目提供的 Iterator 实例
        """
        Initialize your data structure here.
        :type iterator: Iterator
        """
        self.iterator = iterator  # 保存底层迭代器的引用
        self.has_peeked = False  # 是否已经预取过元素
        self.peeked_element = None  # 预取已取出的元素缓存

    def peek(self):  # 查看下一个元素但不推进迭代器
        """
        Returns the next element in the iteration without advancing the iterator.
        :rtype: int
        """
        if not self.has_peeked:  # 还没预取过，就真正取一个出来缓存
            self.peeked_element = self.iterator.next()  # 调用底层 next 前进并缓存结果
            self.has_peeked = True  # 标记已预取
        return self.peeked_element  # 重复 peek 时直接返回缓存值

    def next(self):  # 取下一个元素并推进迭代器
        """
        :rtype: int
        """
        if not self.has_peeked:  # 没有预取，直接让底层迭代器前进
            return self.iterator.next()  # 直接返回底层下一个元素
        result = self.peeked_element  # 先取出缓存值，稍后返回
        self.has_peeked = False  # 缓存被消费，清除标记
        self.peeked_element = None  # 清空缓存引用，避免重复返回
        return result  # 返回暂存的缓存值

    def hasNext(self):  # 是否还有剩余元素
        """
        :rtype: bool
        """
        return self.has_peeked or self.iterator.hasNext()  # 有缓存 或者 底层还有元素


# Your PeekingIterator object will be instantiated and called as such:
# iter = PeekingIterator(Iterator(nums))
# while iter.hasNext():
#     val = iter.peek()   # Get the next element but not advance the iterator.
#     iter.next()         # Should return the same value as [val].
