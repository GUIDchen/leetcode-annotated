// 题目：2603. 收集树中金币（Collect Coins in a Tree）
// 思路：先用拓扑剪枝删掉所有不含金币的叶子，再把剩余树的外缘剥掉两层，剩下的边必须走，答案 = 剩余边数 × 2。
// 时间复杂度：O(n)，每个节点与每条边均摊常数次操作；空间复杂度：O(n)，邻接集合与队列。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {  // coins：每个节点是否有金币；edges：无向边；返回收集全部金币所需走过的最少边数
        int n = coins.size();  // 节点个数
        unordered_set<int> g[n];  // 用邻接集合建图，便于后面 O(1) 删除一条边
        for (auto& e : edges) {  // 逐条边建立双向连接
            int a = e[0], b = e[1];  // 取出边的两个端点
            g[a].insert(b);  // a 的邻居中加入 b
            g[b].insert(a);  // b 的邻居中加入 a（无向图）
        }
        queue<int> q;  // 队列存放「无金币且度为 1」的叶子节点，它们一定不会被走到
        for (int i = 0; i < n; ++i) {  // 找出初始的全部无金币叶子
            if (coins[i] == 0 && g[i].size() == 1) {  // 无金币且只剩一条边
                q.push(i);  // 入队，稍后剪掉
            }
        }
        while (!q.empty()) {  // 自外向内地剪掉不含金币的叶子
            int i = q.front();  // 取出队首叶子
            q.pop();  // 出队
            for (int j : g[i]) {  // 枚举它唯一的邻居
                g[j].erase(i);  // 从邻居的邻接集合里删除这条边
                if (coins[j] == 0 && g[j].size() == 1) {  // 邻居被剪后也变成了无金币叶子
                    q.push(j);  // 同样入队等待剪除
                }
            }
            g[i].clear();  // 清空自己的邻接集合，标记该节点已删除
        }
        for (int k = 0; k < 2; ++k) {  // 在剩余树上再剥掉两层叶子（金币到必走边的距离是 2）
            vector<int> q;  // 用 vector 先收集本层叶子，避免边遍历边修改容器
            for (int i = 0; i < n; ++i) {  // 扫描所有节点
                if (g[i].size() == 1) {  // 度数为 1 说明是当前层的叶子
                    q.push_back(i);  // 记录待删除的叶子
                }
            }
            for (int i : q) {  // 逐个删除本层叶子
                for (int j : g[i]) {  // 枚举叶子的邻居
                    g[j].erase(i);  // 从邻居的邻接集合里删除这条边
                }
                g[i].clear();  // 清空叶子自身的邻接集合
            }
        }
        int ans = 0;  // 答案：仍被保留的边数 × 2（来回都要走）
        for (auto& e : edges) {  // 遍历原始边列表
            int a = e[0], b = e[1];  // 边的两个端点
            if (g[a].size() && g[b].size()) {  // 两端都还在剩余树中，说明这条边必须走
                ans += 2;  // 一条边来回共两次
            }
        }
        return ans;  // 返回最少需要走过的边数
    }
};