# 题目：1476. 子矩形查询（Subrectangle Queries）
# 思路：惰性更新。每次矩形赋值只把参数追加进 ops，不真正改写矩阵；查询时从最新操作往前找，第一个包含该点的操作即为答案，否则返回初始值。
# 时间复杂度：updateSubrectangle 为 O(1)，getValue 为 O(q)（q 为操作次数）；空间复杂度：O(r*c + q)。
class SubrectangleQueries:  # LeetCode 约定的题解类
    def __init__(self, rectangle: List[List[int]]):  # 构造函数：接收初始矩阵
        self.g = rectangle  # 保存初始矩阵的引用，用来回答没被更新覆盖的位置
        self.ops = []  # 历史操作列表：每项是 (row1, col1, row2, col2, newValue)

    def updateSubrectangle(  # 把子矩形内的值全部更新为 newValue
        self, row1: int, col1: int, row2: int, col2: int, newValue: int  # 子矩形左上角与右下角坐标，以及新值
    ) -> None:  # 无返回值
        self.ops.append((row1, col1, row2, col2, newValue))  # 惰性更新：只记录操作，不真正遍历矩阵

    def getValue(self, row: int, col: int) -> int:  # 查询 (row, col) 处的当前值
        for r1, c1, r2, c2, v in self.ops[::-1]:  # 从最新操作往回遍历（[::-1] 表示反转顺序）
            if r1 <= row <= r2 and c1 <= col <= c2:  # 该点是否落在这次操作的矩形内
                return v  # 最新覆盖它的操作就是最终值
        return self.g[row][col]  # 没有任何更新覆盖过它，返回初始矩阵中的值


# Your SubrectangleQueries object will be instantiated and called as such:  # LeetCode 题面给出的调用示例
# obj = SubrectangleQueries(rectangle)
# obj.updateSubrectangle(row1,col1,row2,col2,newValue)
# param_2 = obj.getValue(row,col)
