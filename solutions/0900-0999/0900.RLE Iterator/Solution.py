# 题目：900. RLE 迭代器（RLE Iterator）
# 核心思路：指针 i 指向当前段的计数字段，j 记录该段已消耗数量，next 时按需跨段推进。
# 时间复杂度：next 均摊 O(1)，单次最坏 O(n)；空间复杂度：O(n) 保存编码数组。
class RLEIterator:  # 行程长度编码迭代器
    def __init__(self, encoding: List[int]):  # encoding：交替存放「次数、数值」的数组
        self.encoding = encoding  # 保存编码数组，供后续 next 使用
        self.i = 0  # 当前段计数字段在数组中的下标（偶数位）
        self.j = 0  # 当前段内已消耗的元素个数

    def next(self, n: int) -> int:  # 消耗 n 个元素，返回最后一个被消耗的元素值
        while self.i < len(self.encoding):  # 还有段没被消耗完就继续找
            if self.encoding[self.i] - self.j < n:  # 当前段剩余数量不够本次消耗
                n -= self.encoding[self.i] - self.j  # 把当前段剩余的全部消耗掉
                self.i += 2  # 跳过计数字段，指向下一个数值段
                self.j = 0  # 新段从 0 开始计已消耗数量
            else:  # 当前段剩余数量足够
                self.j += n  # 在本段内前移 n 个位置
                return self.encoding[self.i + 1]  # 返回本段对应的数值
        return -1  # 所有段都耗尽，按题意返回 -1


# Your RLEIterator object will be instantiated and called as such:
# obj = RLEIterator(encoding)
# param_1 = obj.next(n)
