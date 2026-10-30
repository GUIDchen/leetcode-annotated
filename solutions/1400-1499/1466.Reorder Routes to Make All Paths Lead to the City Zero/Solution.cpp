// 题目：1466. 重新规划路线（Reorder Routes to Make All Paths Lead to the City Zero）
// 核心思路：把每条有向边建成带权无向边，从父侧走向子侧记代价 1（需要改向），从子侧走向父侧记代价 0；从 0 号城市 DFS 累加代价即为答案。
// 时间复杂度：O(n)，每条边只被访问两次；空间复杂度：O(n)，邻接表存 2(n-1) 条记录。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minReorder(int n, vector<vector<int>>& connections) {  // n 是城市数，connections 里每条记录是一条有向边 a -> b
        vector<pair<int, int>> g[n];  // 邻接表：pair 的第二项表示「走这条边是否需要改向」的代价
        for (auto& e : connections) {  // 遍历每条原始有向边
            int a = e[0], b = e[1];  // 取出这条边的方向 a -> b
            g[a].emplace_back(b, 1);  // 从 a 走到 b 时 a 是父侧、b 是子侧，最终需要 b -> a，与原方向相反，代价 1
            g[b].emplace_back(a, 0);  // 从 b 走到 a 时 b 是父侧、a 是子侧，最终需要 a -> b，与原方向一致，代价 0
        }  // 建图结束
        function<int(int, int)> dfs = [&](int a, int fa) {  // 递归 lambda：a 是当前城市，fa 是它的父城市（用来避免回溯）
            int ans = 0;  // 统计以 a 为根的子树中需要改向的边数
            for (auto& [b, c] : g[a]) {  // 结构化绑定取出邻居 b 与这条边的改向代价 c
                if (b != fa) {  // 跳过回到父节点的那条边，防止死循环
                    ans += c + dfs(b, a);  // 累加当前边的代价与子树内部的代价
                }  // 非父邻居分支结束
            }  // 所有邻居遍历完毕
            return ans;  // 返回子树的统计结果
        };  // lambda 定义结束
        return dfs(0, -1);  // 从 0 号城市出发，-1 表示没有父节点
    }  // 方法结束
};  // 类定义结束
