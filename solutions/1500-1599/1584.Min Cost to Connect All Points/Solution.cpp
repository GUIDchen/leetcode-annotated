// 题目：1584. 连接所有点的最小费用（Min Cost to Connect All Points）
// 思路：把点看作完全图，边权为曼哈顿距离，再用 Prim 算法求最小生成树的边权和。
// 时间复杂度：O(n^2)，每轮线性找最近点；空间复杂度：O(n^2)，邻接矩阵。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minCostConnectPoints(vector<vector<int>>& points) {  // points：平面上各点的坐标
        int n = points.size();  // 点的个数，也是完全图的顶点数
        int g[n][n];  // 邻接矩阵：g[i][j] 表示 i 到 j 的曼哈顿距离
        for (int i = 0; i < n; ++i) {  // 枚举边的第一个端点
            int x1 = points[i][0], y1 = points[i][1];  // 取出 i 的坐标
            for (int j = i + 1; j < n; ++j) {  // 只枚举 j > i，无向边不重复计算
                int x2 = points[j][0], y2 = points[j][1];  // 取出 j 的坐标
                int t = abs(x1 - x2) + abs(y1 - y2);  // 题目规定的费用即曼哈顿距离
                g[i][j] = t;  // 对称写入矩阵的两个方向
                g[j][i] = t;  // 保证从 j 也能查到 i
            }
        }
        int dist[n];  // Prim 算法：dist[k] 为 k 到当前生成树的最短边权
        bool vis[n];  // vis[k] 标记 k 是否已经加入生成树
        memset(dist, 0x3f, sizeof(dist));  // 初始化为 INF（0x3f3f3f3f，足够大且累加不溢出）
        memset(vis, false, sizeof(vis));  // 一开始一个点都没加入
        dist[0] = 0;  // 任选 0 号点作为起点，入树代价为 0
        int ans = 0;  // 最小生成树的总费用
        for (int i = 0; i < n; ++i) {  // 一共要加入 n 个点
            int j = -1;  // j 记录本轮 dist 最小的未访问点
            for (int k = 0; k < n; ++k) {  // 线性扫描找最近的点
                if (!vis[k] && (j == -1 || dist[k] < dist[j])) {  // 未访问且距离更小
                    j = k;  // 更新候选点
                }
            }
            vis[j] = true;  // 把 j 并入生成树
            ans += dist[j];  // 累加这条最短的连接边
            for (int k = 0; k < n; ++k) {  // 用 j 松弛其余未访问点的入树距离
                if (!vis[k]) {  // 只更新还在树外的点
                    dist[k] = min(dist[k], g[j][k]);  // 取更短的入树边权
                }
            }
        }
        return ans;  // 返回最小总费用
    }
};