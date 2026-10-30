// 题目：803. 打砖块（Bricks Falling When Hit）
// 思路：逆向思考——先删掉所有会被击打的砖，算出稳定砖块，再按时间倒序把砖补回，用并查集观察与「屋顶」虚拟节点相连集合的大小增量，减去砖自身就是本次掉落的数量。
// 时间复杂度：O(mn + k·α(mn))，并查集近似 O(1)；空间复杂度：O(mn)，并查集与网格副本。
class Solution {  // LeetCode 约定的题解类
public:  // 成员对外可见
    vector<int> p;  // 并查集父数组
    vector<int> size;  // 每个集合的大小（以树根为下标）

    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {  // grid：砖块矩阵；hits：击打顺序；返回每次击打掉落的砖数
        int m = grid.size(), n = grid[0].size();  // m 行 n 列
        p.resize(m * n + 1);  // 多开一个节点 m*n 作为连接首行的「屋顶」虚拟节点
        size.resize(m * n + 1);  // 集合大小数组同步扩容
        for (int i = 0; i < p.size(); ++i) {  // 初始化并查集
            p[i] = i;  // 每个节点先各自成一个集合
            size[i] = 1;  // 单元素集合大小为 1
        }  // 初始化结束
        vector<vector<int>> g(m, vector<int>(n));  // 网格副本，便于原地删除和恢复砖块
        for (int i = 0; i < m; ++i)  // 逐行复制
            for (int j = 0; j < n; ++j)  // 逐列复制
                g[i][j] = grid[i][j];  // 不破坏输入的 grid
        for (auto& h : hits) g[h[0]][h[1]] = 0;  // 把所有将来会被击打的砖先删掉，得到最终状态
        for (int j = 0; j < n; ++j)  // 首行的砖天然稳定，与屋顶相连
            if (g[0][j] == 1)  // 该位置首行有砖
                merge(j, m * n);  // 并入屋顶虚拟节点
        for (int i = 1; i < m; ++i) {  // 从第二行开始，把砖块与上方、左方合并
            for (int j = 0; j < n; ++j) {  // 逐列处理
                if (g[i][j] == 0) continue;  // 空位不用合并
                if (g[i - 1][j] == 1) merge(i * n + j, (i - 1) * n + j);  // 与上方砖块连通
                if (j > 0 && g[i][j - 1] == 1) merge(i * n + j, i * n + j - 1);  // 与左侧砖块连通（j > 0 防止越界）
            }  // 列循环结束
        }  // 行循环结束
        vector<int> ans(hits.size());  // 每次击打的掉落数
        vector<int> dirs = {-1, 0, 1, 0, -1};  // 四方向偏移，相邻两项拼出一个方向
        for (int k = hits.size() - 1; k >= 0; --k) {  // 按时间倒序回放击打
            int i = hits[k][0], j = hits[k][1];  // 本次击打的坐标
            if (grid[i][j] == 0) continue;  // 原本这里就没有砖，击打无效
            g[i][j] = 1;  // 把砖补回去
            int prev = size[find(m * n)];  // 补砖前，与屋顶连通集合的大小
            if (i == 0) merge(j, m * n);  // 首行的砖直接挂到屋顶上
            for (int l = 0; l < 4; ++l) {  // 枚举上下左右四个邻居
                int x = i + dirs[l], y = j + dirs[l + 1];  // dirs 相邻两项组成一个方向的偏移量
                if (x >= 0 && x < m && y >= 0 && y < n && g[x][y] == 1)  // 邻居在界内且有砖
                    merge(i * n + j, x * n + y);  // 与相邻砖块合并
            }  // 邻居循环结束
            int curr = size[find(m * n)];  // 补砖后，与屋顶连通集合的大小
            ans[k] = max(0, curr - prev - 1);  // 增量减去这块砖自身，就是本次掉落的砖数
        }  // 倒序回放结束
        return ans;  // 返回每次击打的掉落数
    }  // 方法结束

    int find(int x) {  // 并查集查找，带路径压缩
        if (p[x] != x) p[x] = find(p[x]);  // 顺手把沿途父指针直接挂到根上
        return p[x];  // 返回所在集合的根
    }  // find 结束

    void merge(int a, int b) {  // 合并两个集合
        int pa = find(a), pb = find(b);  // 先找出各自的根
        if (pa != pb) {  // 不在同一集合才需要合并
            size[pb] += size[pa];  // 把 a 所在集合的大小累加到 b 所在集合
            p[pa] = pb;  // 让 a 的根指向 b 的根
        }  // 合并分支结束
    }  // merge 结束
};  // 类定义结束