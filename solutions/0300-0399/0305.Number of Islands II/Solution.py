# 题目：305. 岛屿数量 II（Number of Islands II）
# 思路：并查集。每开垦一块新陆地先让数量加一，再与四个已开垦邻居合并，每次合并成功就减一。
# 时间复杂度：O(k α(mn))，k 为操作次数、α 为反阿克曼函数；空间复杂度：O(mn)，并查集与网格。
class UnionFind:  # 并查集：维护所有已开垦格子的连通分量
    def __init__(self, n: int):  # n 为元素总数
        self.p = list(range(n))  # 父指针数组，初始每个元素自成一个集合
        self.size = [1] * n  # 每个集合的大小，用于按大小合并

    def find(self, x: int):  # 查找 x 的根，同时做路径压缩
        if self.p[x] != x:  # 若 x 不是根
            self.p[x] = self.find(self.p[x])  # 递归找到根并直接把 x 挂到根上（路径压缩）
        return self.p[x]  # 返回根

    def union(self, a: int, b: int) -> bool:  # 合并 a、b 表示的两个集合，返回是否真的合并
        pa, pb = self.find(a - 1), self.find(b - 1)  # 内部先减 1 再查找，即本实现约定传入的是 1 基下标
        if pa == pb:  # 根相同说明已经属于同一集合
            return False  # 不需要合并
        if self.size[pa] > self.size[pb]:  # 按大小合并：小集合挂到大集合下
            self.p[pb] = pa  # b 的根指向 a 的根
            self.size[pa] += self.size[pb]  # a 的集合大小累加
        else:  # 否则把 a 挂到 b 下
            self.p[pa] = pb  # a 的根指向 b 的根
            self.size[pb] += self.size[pa]  # b 的集合大小累加
        return True  # 确实合并了两个不同集合


class Solution:  # LeetCode 约定的题解类
    def numIslands2(self, m: int, n: int, positions: List[List[int]]) -> List[int]:  # m 行 n 列；positions 依次给出要开垦的格子坐标
        uf = UnionFind(m * n)  # 每个格子对应并查集的一个元素，总数为 m*n
        grid = [[0] * n for _ in range(m)]  # 二维网格记录每个格子是否为陆地
        ans = []  # 每一轮的结果
        dirs = (-1, 0, 1, 0, -1)  # 四个方向的偏移，首尾闭合便于 pairwise 生成相邻对
        cnt = 0  # 当前连通块数量
        for i, j in positions:  # 依次处理每个开垦位置
            if grid[i][j]:  # 已经是陆地，数量不变
                ans.append(cnt)  # 直接记录当前数量
                continue  # 本轮结束，继续下一个位置
            grid[i][j] = 1  # 把该格子标记为陆地
            cnt += 1  # 新格子先自成一个连通块，计数加一
            for a, b in pairwise(dirs):  # pairwise 依次给出上、右、下、左四个方向
                x, y = i + a, j + b  # 计算邻居坐标
                if (  # 多个条件共同决定是否合并：邻居在界内、是陆地、且合并成功
                    0 <= x < m  # 行坐标在界内
                    and 0 <= y < n  # 列坐标在界内
                    and grid[x][y]  # 邻居已经是陆地
                    and uf.union(i * n + j, x * n + y)  # 合并成功说明两块陆地连成了一块
                ):  # if 条件结束（括号收尾）
                    cnt -= 1  # 连通块数量减一
            ans.append(cnt)  # 记录本轮结束后的连通块数量
        return ans  # 返回每一轮的结果
