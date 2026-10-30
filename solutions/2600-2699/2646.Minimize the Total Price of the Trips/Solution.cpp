// 题目：2646. 最小化旅行的价格总和（Minimize the Total Price of the Trips）
// 思路：先对每条行程 DFS 统计每个节点被经过的次数，再在树上做 DP：节点减半时子节点必须原价，取两种决策的较小值。
// 时间复杂度：O(m × n)，m 为行程数、n 为节点数；空间复杂度：O(n)，邻接表、计数数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    // n：节点数；edges：树边；price：每个节点的价格；trips：全部行程；返回所有行程的最小价格总和
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {  // 入口方法
        vector<vector<int>> g(n);  // 邻接表：g[i] 保存与节点 i 相邻的所有节点
        vector<int> cnt(n);  // cnt[i]：节点 i 在所有行程中被经过的次数，初值为 0
        for (auto& e : edges) {  // 用边表构建无向图
            int a = e[0], b = e[1];  // 取出这条边的两个端点
            g[a].push_back(b);  // a 的邻接表里加入 b
            g[b].push_back(a);  // b 的邻接表里加入 a，无向边双向登记
        }
        // 第一遍 DFS：从 i 出发（父节点 fa）寻找通往 k 的路径，途中把经过节点的 cnt 加一
        // 找到返回 true；若子树里都没有 k，说明 i 不在路径上，需要把多加的计数撤销
        function<bool(int, int, int)> dfs = [&](int i, int fa, int k) -> bool {  // 递归 lambda
            ++cnt[i];  // 先假设 i 在路径上，计数加一
            if (i == k) {  // 到达终点，路径成立
                return true;  // 成功时保留计数
            }
            bool ok = false;  // ok 标记子树里是否找到了通往 k 的路径
            for (int j : g[i]) {  // 枚举 i 的邻居
                if (j != fa) {  // 不走回父节点，避免在树上绕圈
                    ok = dfs(j, i, k);  // 递归搜索这棵子树
                    if (ok) {  // 子树里找到了终点
                        break;  // 提前结束枚举，不再搜索其他子树
                    }
                }
            }
            if (!ok) {  // 所有子树都没有 k，说明 i 不在路径上
                --cnt[i];  // 撤销刚才多加的计数
            }
            return ok;  // 把结果回传给父节点
        };
        // 第二遍 DFS（树形 DP）：返回 {a, b}，a 表示 i 不减半、b 表示 i 减半时子树的最小价格总和
        function<pair<int, int>(int, int)> dfs2 = [&](int i, int fa) -> pair<int, int> {  // 树形 DP
            int a = cnt[i] * price[i];  // i 不减半时，它自身贡献 cnt[i] * price[i]
            int b = a >> 1;  // i 减半：price 是偶数，右移一位等价于除以 2
            for (int j : g[i]) {  // 枚举子节点
                if (j != fa) {  // 跳过父节点
                    auto [x, y] = dfs2(j, i);  // x：子节点不减半的最优值；y：子节点减半的最优值
                    a += min(x, y);  // i 不减半 → 子节点可任选，取较小者
                    b += x;  // i 减半 → 相邻子节点不能减半，只能取 x
                }
            }
            return {a, b};  // 返回两种决策下的最小总价
        };
        for (auto& t : trips) {  // 逐条行程统计路径经过次数
            int start = t[0], end = t[1];  // 行程的起点与终点
            dfs(start, -1, end);  // -1 表示起点没有父节点
        }
        auto [a, b] = dfs2(0, -1);  // 以 0 为根做树形 DP
        return min(a, b);  // 根节点减半或不减半，取较小值
    }
};  // 类定义结束