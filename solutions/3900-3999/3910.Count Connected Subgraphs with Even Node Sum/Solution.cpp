// 3910. Count Connected Subgraphs with Even Node Sum | 统计节点和为偶数的连通子图（困难）
// 核心思路：n 很小，枚举 2^n 个非空节点子集，先判断节点值之和是否为偶数；再把子集之外的位预置为已访问，从子集内某个节点做 DFS，若最终所有位都被访问，说明子集本身连通，计数加一。
// 复杂度：时间 O(2^n * (n + m))，m 为边数（每个子集一次求和 + 一次 DFS）；空间 O(n + m)（邻接表与递归栈）。
class Solution {  // 定义题解类
public:  // 公有接口
    int evenSumSubgraphs(vector<int>& nums, vector<vector<int>>& edges) {  // 返回节点值之和为偶数、且点集本身连通的子图个数
        int n = nums.size();  // 节点个数
        vector<vector<int>> g(n);  // 邻接表，共 n 个空列表
        for (auto& e : edges) {  // 遍历每条无向边
            g[e[0]].push_back(e[1]);  // 建立 u -> v 的单向边
            g[e[1]].push_back(e[0]);  // 建立 v -> u 的反向边，凑成无向图
        }  // 边建完
        int m = (1 << n) - 1;  // n 位全为 1 的掩码，代表“全集”
        int ans = 0;  // 答案计数
        int vis;  // 访问位掩码，每枚举一个子集都要重置

        auto dfs = [&](this auto dfs, int u) -> void {  // 递归 lambda（C++23 的 this auto 写法，方便引用自身），用于把与 u 连通的点都染色
            vis |= 1 << u;  // 把 u 这一位标记为已访问
            for (int v : g[u]) {  // 枚举 u 的所有邻居
                if (((vis >> v) & 1) == 0) {  // 邻居 v 还没有被访问过
                    dfs(v);  // 继续向 v 深入染色
                }  // if 结束
            }  // 邻居枚举结束
        };  // lambda 结束

        for (int sub = 1; sub <= m; sub++) {  // 枚举所有非空的节点子集（1 .. 全集）
            int s = 0;  // 当前子集内节点的取值之和
            for (int i = 0; i < n; i++) {  // 逐位检查这 n 个节点
                if ((sub >> i) & 1) {  // 第 i 位为 1 表示节点 i 属于该子集
                    s += nums[i];  // 把节点 i 的值计入总和
                }  // if 结束
            }  // 位检查结束
            if (s % 2 != 0) {  // 节点值之和为奇数，不满足题目要求
                continue;  // 直接跳过该子集
            }  // if 结束
            vis = m ^ sub;  // 关键一步：把子集之外的位预先标记为已访问，这样 DFS 只会在子集内部扩展
            dfs(31 - __builtin_clz(sub));  // 从 sub 的最高位（31 - 前导零个数）对应的节点出发染色，该节点必定属于子集
            if (vis == m) {  // 若全集所有位都被染色，说明子集内部被一次 DFS 走遍，即子集连通
                ans++;  // 连通子图计数加一
            }  // if 结束
        }  // 子集枚举结束
        return ans;  // 返回满足条件的连通子图个数
    }  // 方法结束
};  // 类定义结束
