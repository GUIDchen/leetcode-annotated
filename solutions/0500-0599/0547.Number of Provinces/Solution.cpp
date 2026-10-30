// 题目：547. 省份数量（Number of Provinces）
// 思路：把邻接矩阵看成无向图，用 DFS 逐个遍历连通块，每启动一次新的 DFS 就说明多了一个省份。
// 时间复杂度：O(n^2)，每个城市都要扫描一整行邻接关系；空间复杂度：O(n)，访问数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findCircleNum(vector<vector<int>>& isConnected) {  // isConnected 是 n×n 的邻接矩阵，返回连通分量（省份）的个数
        int n = isConnected.size();  // 城市的数量 n
        int ans = 0;  // 省份计数，每发现一个连通块就加一
        bool vis[n];  // 访问标记：vis[i] 表示城市 i 已被归入某个省份
        memset(vis, false, sizeof(vis));  // 全部初始化为未访问
        auto dfs = [&](this auto&& dfs, int i) -> void {  // C++23 显式对象参数让 lambda 能递归：从城市 i 出发标记整个连通块
            vis[i] = true;  // 标记当前城市已访问，防止重复进入
            for (int j = 0; j < n; ++j) {  // 枚举所有可能与 i 相邻的城市
                if (!vis[j] && isConnected[i][j]) {  // 城市 j 未访问过，且 i 与 j 之间存在直接连接
                    dfs(j);  // 继续深入 j，把同一连通块全部染色
                }  // 结束 if 判断
            }  // 结束 for 循环
        };  // lambda 定义结束
        for (int i = 0; i < n; ++i) {  // 依次检查每个城市
            if (!vis[i]) {  // 发现尚未访问的城市，说明出现了一个新的连通块
                dfs(i);  // 沿这个城市把整个省份都标记为已访问
                ++ans;  // 省份数量加一
            }  // 结束 if 判断
        }  // 结束 for 循环
        return ans;  // 返回省份总数
    }  // 结束 findCircleNum
};  // 类定义结束
