// 题目：310. 最小高度树（Minimum Height Trees）
// 思路：树的「重心」问题。反过来用拓扑剥叶子：每轮剥掉所有度数为 1 的叶子，最后剩下的 1~2 个节点就是答案。
// 时间复杂度：O(n)，每个节点最多入队、出队一次；空间复杂度：O(n)，邻接表、度数数组与队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {  // n：节点数；edges：无向边列表，每条边是 [a, b]
        if (n == 1) {  // 只有一个节点时它自己就是唯一的最小高度树根
            return {0};  // 直接返回节点 0
        }
        vector<vector<int>> g(n);  // 邻接表：g[u] 保存与 u 相邻的所有节点
        vector<int> degree(n);  // 每个节点的度数（相邻节点个数）
        for (auto& e : edges) {  // 遍历每条无向边
            int a = e[0], b = e[1];  // 取出边的两个端点
            g[a].push_back(b);  // 把 b 加入 a 的邻接表
            g[b].push_back(a);  // 把 a 加入 b 的邻接表（无向边要双向记录）
            ++degree[a];  // a 的度数加一
            ++degree[b];  // b 的度数加一
        }
        queue<int> q;  // 队列：存放当前所有叶子节点（度数为 1）
        for (int i = 0; i < n; ++i) {  // 扫描全部节点
            if (degree[i] == 1) {  // 度数为 1 说明它是叶子
                q.push(i);  // 入队，作为第一轮要剥掉的节点
            }
        }
        vector<int> ans;  // 每轮剥完后剩下的节点，最后一轮剩下的就是候选根
        while (!q.empty()) {  // 不断剥叶子，直到最后只剩 1~2 个节点
            ans.clear();  // 清空上一轮结果，ans 只保留最后一轮剥掉的节点
            for (int i = q.size(); i > 0; --i) {  // 按层处理：只弹出本层现有的 q.size() 个叶子
                int a = q.front();  // 取队头叶子
                q.pop();  // 出队
                ans.push_back(a);  // 记录本轮剥掉的节点
                for (int b : g[a]) {  // 遍历该叶子的所有邻居
                    if (--degree[b] == 1) {  // 剥掉 a 后邻居度数减一，若变成 1 就成为新叶子
                        q.push(b);  // 新叶子入队，留到下一层处理
                    }
                }
            }
        }
        return ans;  // 最后一轮剩下的节点（1~2 个）就是最小高度树的根
    }
};