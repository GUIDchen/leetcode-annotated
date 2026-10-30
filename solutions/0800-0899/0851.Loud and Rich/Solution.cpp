// 题目：851. 喧闹和富有（Loud and Rich）
// 思路：把 richer 看成「更有钱 → 更穷」的有向边，从每个人出发做记忆化 DFS，取子树中 quiet 最小的编号。
// 时间复杂度：O(n + m)，每个点只求解一次；空间复杂度：O(n + m)，邻接表与答案数组。
class Solution {  // 题解类
public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {  // richer[i] = [a, b] 表示 a 比 b 有钱；quiet[i] 越小代表越安静
        int n = quiet.size();  // 人数
        vector<vector<int>> g(n);  // 邻接表：g[b] 存放所有比 b 更有钱的人（即 b 的上游）
        for (auto& r : richer) {  // 遍历所有贫富关系
            g[r[1]].push_back(r[0]);  // 建边 b → a，表示从 b 可以往上找到更有钱的 a
        }  // 关系处理完毕
        vector<int> ans(n, -1);  // ans[i] 是 i 及其所有更有钱者中 quiet 最小的编号，-1 表示尚未计算（记忆化标记）
        function<void(int)> dfs = [&](int i) {  // 递归函数：求 i 可达范围内 quiet 最小的编号
            if (ans[i] != -1) {  // 已经算过就直接复用，避免重复搜索
                return;  // 提前返回
            }  // 未计算分支结束
            ans[i] = i;  // 先假设答案是自己
            for (int j : g[i]) {  // 遍历所有比 i 有钱的人
                dfs(j);  // 先递归求出 j 的答案
                if (quiet[ans[j]] < quiet[ans[i]]) {  // 若 j 的答案更安静，则用它更新 i 的答案
                    ans[i] = ans[j];  // 记录更安静的编号
                }  // 比较分支结束
            }  // 邻接表遍历结束
        };  // lambda 定义结束
        for (int i = 0; i < n; ++i) {  // 对每个人都求一次答案
            dfs(i);  // 记忆化 DFS
        }  // 外层循环结束
        return ans;  // 返回每个人的答案
    }  // 方法结束
};  // 题解类结束