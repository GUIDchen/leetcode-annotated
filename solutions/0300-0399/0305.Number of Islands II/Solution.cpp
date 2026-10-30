// 题目：305. 岛屿数量 II（Number of Islands II）
// 思路：并查集。每开垦一块新陆地先让数量加一，再与四个已开垦邻居合并，每次合并成功就减一。
// 时间复杂度：O(k α(mn))，k 为操作次数、α 为反阿克曼函数；空间复杂度：O(mn)，并查集与网格。
class UnionFind {  // 并查集：维护每个已开垦格子的连通分量
public:  // 对外接口
    UnionFind(int n) {  // n 是元素总数（本题为 m*n 个格子）
        p = vector<int>(n);  // 父指针数组
        size = vector<int>(n, 1);  // 每个连通块的大小，用于按大小合并（启发式合并）
        iota(p.begin(), p.end(), 0);  // iota 把 p 填成 0,1,2,...,n-1，初始每个元素自成一类
    }  // 构造函数结束

    bool unite(int a, int b) {  // 合并 a、b 所在的两个连通块，返回是否真的发生了合并
        int pa = find(a), pb = find(b);  // 先分别找到两个元素的根
        if (pa == pb) {  // 根相同说明本来就在同一个连通块
            return false;  // 无需合并，返回失败
        }  // 结束 if
        if (size[pa] > size[pb]) {  // 小树挂到大树上，保证树高接近对数级
            p[pb] = pa;  // a 的连通块更大，把 b 的根指向 a 的根
            size[pa] += size[pb];  // 同时把 b 的大小累加到 a 上
        } else {  // 否则把 a 的根挂到 b 的根上
            p[pa] = pb;  // b 的根成为新的代表元
            size[pb] += size[pa];  // 累加大小
        }  // 大小比较分支结束
        return true;  // 确实合并了两个不同的连通块
    }  // unite 结束

    int find(int x) {  // 查找 x 的根，并做路径压缩
        if (p[x] != x) {  // 若 x 不是根
            p[x] = find(p[x]);  // 递归找到根后直接把 x 挂到根上（路径压缩）
        }  // 递归返回
        return p[x];  // 返回根
    }  // find 结束

private:  // 私有数据成员
    vector<int> p, size;  // p 为父指针数组，size 为连通块大小
};  // UnionFind 类结束

class Solution {  // LeetCode 约定的题解类
public:  // 对外接口
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {  // m 行 n 列；positions 依次给出要开垦的格子坐标
        int grid[m][n];  // 用二维数组记录每个格子是否为陆地（0 水，1 陆地）；VLA 为 GNU 扩展，clang 支持
        memset(grid, 0, sizeof(grid));  // 全部清零
        UnionFind uf(m * n);  // 每个格子对应并查集里的一个元素，编号 i*n+j
        int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组：用 (dirs[k], dirs[k+1]) 一次遍历上下左右四个方向
        int cnt = 0;  // 当前陆地的连通块数量
        vector<int> ans;  // 每一轮操作的答案
        for (auto& p : positions) {  // 依次处理每次开垦
            int i = p[0], j = p[1];  // 取出本次要开垦的坐标
            if (grid[i][j]) {  // 如果这里已经是陆地
                ans.push_back(cnt);  // 连通块数量不变，直接记录当前数量
                continue;  // 本轮结束，处理下一个位置
            }  // 结束 if
            grid[i][j] = 1;  // 把该格子标记为陆地
            ++cnt;  // 新出现的格子先自成一个连通块，计数加一
            for (int k = 0; k < 4; ++k) {  // 检查上下左右四个邻居
                int x = i + dirs[k], y = j + dirs[k + 1];  // 邻居的坐标
                if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] && uf.unite(i * n + j, x * n + y)) {  // 邻居在界内且是陆地，并且合并成功，说明两块陆地连成了一块
                    --cnt;  // 连通块数量减一
                }  // 结束 if
            }  // 四个方向遍历结束
            ans.push_back(cnt);  // 记录本轮结束后的连通块数量
        }  // positions 遍历结束
        return ans;  // 返回每一轮的答案
    }  // numIslands2 结束
};  // Solution 类结束