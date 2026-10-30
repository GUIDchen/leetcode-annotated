# 3391. 设计一个高效的层跟踪三维二进制矩阵 / Design a 3D Binary Matrix with Efficient Layer Tracking
# 核心思路：三维数组 g 记录每个格子状态，cnt[x] 统计第 x 层中 1 的个数，SortedList 以 (-cnt[x], -x) 为键排序，首元素即 1 最多的层，每次更新只需摘除并重新插入一条记录
# 复杂度：时间 O(log n)（有序表增删为 O(log n)，其余操作 O(1)）、空间 O(n^3)
class matrix3D:  # 定义 matrix3D 类
    def __init__(self, n: int):  # 构造函数，建立 n * n * n 的三维矩阵
        self.g = [[[0] * n for _ in range(n)] for _ in range(n)]  # g[x][y][z] 记录第 x 层第 (y, z) 个位置是否为 1
        self.cnt = [0] * n  # cnt[x] 记录第 x 层中 1 的个数
        self.sl = SortedList(key=lambda x: (-x[0], -x[1]))  # 有序表按 (1 的个数降序, 层号降序) 排序，首元素即 1 最多的层

    def setCell(self, x: int, y: int, z: int) -> None:  # 把 (x, y, z) 位置置为 1
        if self.g[x][y][z]:  # 该位置已经是 1
            return  # 无需重复操作，直接返回
        self.g[x][y][z] = 1  # 将该格子置为 1
        self.sl.discard((self.cnt[x], x))  # 先从有序表中移除第 x 层的旧记录
        self.cnt[x] += 1  # 第 x 层 1 的个数加一
        self.sl.add((self.cnt[x], x))  # 再把第 x 层的新记录插入有序表

    def unsetCell(self, x: int, y: int, z: int) -> None:  # 把 (x, y, z) 位置置为 0
        if self.g[x][y][z] == 0:  # 该位置本来就是 0
            return  # 无需重复操作，直接返回
        self.g[x][y][z] = 0  # 将该格子置为 0
        self.sl.discard((self.cnt[x], x))  # 先从有序表中移除第 x 层的旧记录
        self.cnt[x] -= 1  # 第 x 层 1 的个数减一
        if self.cnt[x]:  # 只有该层还剩 1 时才需要记录
            self.sl.add((self.cnt[x], x))  # 把更新后的记录重新插入有序表

    def largestMatrix(self) -> int:  # 返回 1 的个数最多的层号（并列取层号较大者）
        return self.sl[0][1] if self.sl else len(self.g) - 1  # 有序表非空取首元素层号；全为 0（表空）时返回最大层号


# Your matrix3D object will be instantiated and called as such:
# obj = matrix3D(n)
# obj.setCell(x,y,z)
# obj.unsetCell(x,y,z)
# param_3 = obj.largestMatrix()
