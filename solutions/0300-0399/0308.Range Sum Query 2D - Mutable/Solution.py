# 题目：308. 二维区域和检索 - 矩阵可修改（Range Sum Query 2D - Mutable）
# 思路：每行建一棵树状数组；单点修改只更新所在行，子矩阵求和按行累加一维区间和。
# 时间复杂度：更新 O(log n)、查询 O(m log n)；空间复杂度：O(mn)，每行一棵树状数组。
class BinaryIndexedTree:  # 一维树状数组：二维问题中每行建一棵
    def __init__(self, n):  # 构造函数：n 为列数
        self.n = n  # 记录长度
        self.c = [0] * (n + 1)  # 树状数组本体，1 基下标，多开一位

    @staticmethod  # 声明为静态方法，调用时不必绑定实例
    def lowbit(x):  # 取 x 最低位的 1 所对应的值
        return x & -x  # 位运算 x & -x

    def update(self, x, delta):  # 在下标 x 处加 delta
        while x <= self.n:  # 向上更新所有管辖 x 的节点
            self.c[x] += delta  # 当前节点累加增量
            x += BinaryIndexedTree.lowbit(x)  # 通过类名调用静态方法，向上跳一级

    def query(self, x):  # 查询前缀和 [1, x]
        s = 0  # 累加器
        while x > 0:  # 向下切分前缀
            s += self.c[x]  # 累加当前段
            x -= BinaryIndexedTree.lowbit(x)  # 去掉最低位的 1，跳到前一段
        return s  # 返回前缀和


class NumMatrix:  # LeetCode 约定的题解类
    def __init__(self, matrix: List[List[int]]):  # 构造函数：matrix 是输入矩阵
        self.trees = []  # 每行一个树状数组
        n = len(matrix[0])  # 列数（各行列数相同）
        for row in matrix:  # 逐行建树
            tree = BinaryIndexedTree(n)  # 当前行的树状数组
            for j, v in enumerate(row):  # 逐列插入
                tree.update(j + 1, v)  # 从 1 开始编号，符合树状数组的 1 基下标
            self.trees.append(tree)  # 挂到列表里，保持行号与下标一致

    def update(self, row: int, col: int, val: int) -> None:  # 把 (row, col) 处的值改为 val
        tree = self.trees[row]  # 取出该行对应的树状数组
        prev = tree.query(col + 1) - tree.query(col)  # 先求原值（单点查询 = 两个前缀和相减）
        tree.update(col + 1, val - prev)  # 只更新差值

    def sumRegion(self, row1: int, col1: int, row2: int, col2: int) -> int:  # 查询子矩阵 (row1,col1)-(row2,col2) 的和
        return sum(  # 对 row1..row2 的每一行求一维区间和再求和
            tree.query(col2 + 1) - tree.query(col1)  # 该行的区间和：两个前缀和相减
            for tree in self.trees[row1 : row2 + 1]  # 生成器遍历 self.trees[row1 : row2 + 1] 中的每一行
        )  # sum 调用结束


# Your NumMatrix object will be instantiated and called as such:
# obj = NumMatrix(matrix)
# obj.update(row,col,val)
# param_2 = obj.sumRegion(row1,col1,row2,col2)
