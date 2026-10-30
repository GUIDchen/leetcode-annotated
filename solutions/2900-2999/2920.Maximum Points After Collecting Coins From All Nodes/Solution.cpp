// 题目：2920. 收集所有金币可获得的最大积分（Maximum Points After Collecting Coins From All Nodes）
// 思路：树上记忆化 DFS，状态为（节点，已整体除以 2 的次数），每个节点枚举「按第二类收集扣 k」与「先除 2 再按第一类收集」两种方案取最大。
// 时间复杂度：O(n·log C)，状态数为 n×15，每个状态遍历一次邻接边；空间复杂度：O(n·log C)，记忆化数组与邻接表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumPoints(vector<vector<int>>& edges, vector<int>& coins, int k) {  // edges：树的边；coins：每个节点的金币；k：第二类收集的扣费
        int n = coins.size();  // 节点个数
        int f[n][15];  // 记忆化数组：f[i][j] 表示节点 i 在「已除以 2 共 j 次」时的最大积分
        memset(f, -1, sizeof(f));  // 用 -1 标记该状态还没被计算过
        vector<int> g[n];  // 邻接表：g[u] 存放节点 u 的所有邻居
        for (auto& e : edges) {  // 逐条边建无向图
            int a = e[0], b = e[1];  // 边的两个端点
            g[a].emplace_back(b);  // a 的邻居中加入 b
            g[b].emplace_back(a);  // b 的邻居中加入 a
        }  // 建图完成
        auto dfs = [&](this auto&& dfs, int i, int fa, int j) -> int {  // 记忆化 DFS：i 当前节点，fa 父节点，j 已经除以 2 的次数
            if (f[i][j] != -1) {  // 该状态算过就直接复用
                return f[i][j];  // 返回缓存结果
            }  // 缓存命中分支结束
            int a = (coins[i] >> j) - k;  // 方案一：在 i 处以第二类方式收集，扣掉 k
            int b = coins[i] >> (j + 1);  // 方案二：先把 coins[i] 除以 2（右移一位），再按第一类收集
            for (int c : g[i]) {  // 枚举 i 的所有邻居
                if (c != fa) {  // 跳过父节点，避免走回父节点
                    a += dfs(c, i, j);  // 方案一：子树仍处于「除了 j 次」的状态
                    if (j < 14) {  // 位移次数不能超过记忆化数组的第二维
                        b += dfs(c, i, j + 1);  // 方案二：子树进入「除了 j+1 次」的状态
                    }  // 内层 if 结束
                }  // 邻居分支结束
            }  // 邻居遍历结束
            return f[i][j] = max(a, b);  // 两种方案取较大者，并写入记忆化数组
        };  // lambda 定义结束
        return dfs(0, -1, 0);  // 从根节点 0 出发，还没做过除法
    }  // maximumPoints 结束
};  // 类定义结束
