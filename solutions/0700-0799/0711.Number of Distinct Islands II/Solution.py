# 题目：711. 不同岛屿的数量 II（Number of Distinct Islands II）
# 核心思路：DFS 取出每座岛的全部坐标，再生成 8 种旋转/镜像形态，各自平移到左上角后取字典序最小者作为规范形状，用 set 去重统计。
# 时间复杂度：O(m·n·log(m·n))，每个格子访问一次、每座岛做 8 次排序；空间复杂度：O(m·n)，递归栈与形状集合。
class Solution:  # LeetCode 约定的题解类
    def numDistinctIslands2(self, grid: List[List[int]]) -> int:  # grid 中 1 表示陆地，返回本质不同的岛屿形状数量
        def dfs(i, j, shape):  # 内部 DFS：从 (i, j) 出发收集整座岛的坐标到 shape 中
            shape.append([i, j])  # 记录当前陆地格子（用列表便于后面平移修改坐标）
            grid[i][j] = 0  # 置 0 表示已访问，避免同一格子被重复收集
            for a, b in [[1, 0], [-1, 0], [0, 1], [0, -1]]:  # 枚举上、下、左、右四个方向
                x, y = i + a, j + b  # 计算邻居坐标 x、y
                if 0 <= x < m and 0 <= y < n and grid[x][y] == 1:  # 邻居在界内且是未访问的陆地，才继续搜索
                    dfs(x, y, shape)  # 递归洪泛，把相连的陆地全部并入当前岛屿

        def normalize(shape):  # 把一座岛的坐标转成 8 种对称形态下的字典序最小表示
            shapes = [[] for _ in range(8)]  # shapes[k] 保存第 k 种变换（旋转/镜像）后的坐标列表
            for i, j in shape:  # 遍历岛上的每个格子
                shapes[0].append([i, j])  # 原样，即旋转 0°
                shapes[1].append([i, -j])  # 沿列方向镜像
                shapes[2].append([-i, j])  # 沿行方向镜像
                shapes[3].append([-i, -j])  # 旋转 180°
                shapes[4].append([j, i])  # 主对角线翻转（行列互换）
                shapes[5].append([j, -i])  # 旋转 90°
                shapes[6].append([-j, i])  # 副对角线翻转
                shapes[7].append([-j, -i])  # 旋转 270°（即 -90°）
            for e in shapes:  # 对每一种形态分别做平移规范化
                e.sort()  # 先按 (行, 列) 排序，得到与遍历起点无关的序列
                for i in range(len(e) - 1, -1, -1):  # 倒序平移，避免先改掉作为基准的 e[0]
                    e[i][0] -= e[0][0]  # 行坐标减去最小行坐标，把形状整体移到第 0 行
                    e[i][1] -= e[0][1]  # 列坐标减去最小列坐标，把形状整体移到第 0 列
            shapes.sort()  # 8 种形态之间按字典序排序
            return tuple(tuple(e) for e in shapes[0])  # 取字典序最小的形态并转成元组（列表不可哈希，元组可作 set 的键）

        m, n = len(grid), len(grid[0])  # 提前取出行列数，供内层 dfs 判断边界时使用（闭包会捕获它）
        s = set()  # 存放每座岛的规范形状，set 自动去重
        for i in range(m):  # 逐行扫描网格
            for j in range(n):  # 逐列扫描网格
                if grid[i][j]:  # 找到一块尚未访问的陆地，作为新岛屿的起点
                    shape = []  # 收集这座岛所有格子的坐标
                    dfs(i, j, shape)  # 洪泛填充整座岛，同时把访问过的陆地置 0
                    s.add(normalize(shape))  # 计算规范形状后加入集合，同一形状只会保留一份
        return len(s)  # 集合大小即不同岛屿的数量
