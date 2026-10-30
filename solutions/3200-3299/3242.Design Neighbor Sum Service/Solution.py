# 题目：3242. 设计相邻元素求和服务（Design Neighbor Sum Service）
# 思路：构造时把每个值映射到坐标，查询时用方向表上的四个偏移取邻居，判越界后累加。
# 时间复杂度：构造 O(m × n)，单次查询 O(1)；空间复杂度：O(m × n)，矩阵副本与坐标字典。
class NeighborSum:  # 设计题：按 value 查询相邻格与对角格之和

    def __init__(self, grid: List[List[int]]):  # 构造时建立「值 → 坐标」索引，之后每次查询 O(1) 定位
        self.grid = grid  # 保存矩阵引用
        self.d = {}  # 值到坐标的字典
        self.dirs = ((-1, 0, 1, 0, -1), (-1, 1, 1, -1, -1))  # 方向表：[0] 是上下左右四方向，[1] 是四个对角方向；末尾重复首元素，方便 pairwise 成对读取
        for i, row in enumerate(grid):  # 逐行遍历，i 是行号
            for j, x in enumerate(row):  # 逐列遍历，j 是列号，x 是格子里的值
                self.d[x] = (i, j)  # 记录该值的坐标（题目保证值互不相同）

    def adjacentSum(self, value: int) -> int:  # 返回 value 上下左右四个相邻格之和
        return self.cal(value, 0)  # 复用 cal，k=0 选择相邻方向表

    def cal(self, value: int, k: int):  # 通用求和：k 选方向表，value 指定中心格
        i, j = self.d[value]  # 取出中心坐标
        s = 0  # 累加四个合法邻居的值
        for a, b in pairwise(self.dirs[k]):  # pairwise 把一维方向表切成 (dx, dy) 偏移逐个产出
            x, y = i + a, j + b  # 邻居坐标
            if 0 <= x < len(self.grid) and 0 <= y < len(self.grid[0]):  # 只累加仍在矩阵范围内的邻居
                s += self.grid[x][y]  # 在界内则加进总和
        return s  # 返回四个邻居之和

    def diagonalSum(self, value: int) -> int:  # 返回 value 四个对角格之和
        return self.cal(value, 1)  # 复用 cal，k=1 选择对角方向表


# 下面是 LeetCode 判题器给出的调用示例，属于注释，原样保留
# Your NeighborSum object will be instantiated and called as such:
# obj = NeighborSum(grid)
# param_1 = obj.adjacentSum(value)
# param_2 = obj.diagonalSum(value)
