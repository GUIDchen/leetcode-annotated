# 题目：251. 展开二维向量（Flatten 2D Vector）
# 思路：维护二维下标 (i, j)，next/hasNext 前先用 forward() 跳过空行和已遍历完的行，实现惰性按行展开。
# 时间复杂度：均摊 O(1)，每个元素最多被跳过一次；空间复杂度：O(1)，只保存两个下标。
class Vector2D:  # 迭代器类：把二维列表按行展开成线性序列
    def __init__(self, vec: List[List[int]]):  # 构造函数：保存外部传入的二维列表
        self.i = 0  # 当前行下标
        self.j = 0  # 当前行内的列下标
        self.vec = vec  # 被遍历的二维列表

    def next(self) -> int:  # 返回下一个元素，并把游标后移一位
        self.forward()  # 先跳过已遍历完的行
        ans = self.vec[self.i][self.j]  # 记录当前元素的值
        self.j += 1  # 列下标后移一位
        return ans  # 返回取到的元素

    def hasNext(self) -> bool:  # 是否还有元素可读
        self.forward()  # 先把游标规整到有效位置
        return self.i < len(self.vec)  # 行下标未越界说明还有剩余元素

    def forward(self):  # 把 (i, j) 推进到下一个有效元素的位置
        while self.i < len(self.vec) and self.j >= len(self.vec[self.i]):  # 当前行已到末尾（含空行）就换到下一行
            self.i += 1  # 行下标加一
            self.j = 0  # 新行从第 0 列开始


# Your Vector2D object will be instantiated and called as such:
# obj = Vector2D(vec)
# param_1 = obj.next()
# param_2 = obj.hasNext()
