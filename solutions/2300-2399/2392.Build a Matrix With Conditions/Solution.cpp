// 题目：2392. 给定条件下构造矩阵（Build a Matrix With Conditions）
// 思路：行、列约束各做一次拓扑排序得到顺序；数字按行序放行、按列序放列，行列条件同时满足。
// 时间复杂度：O(k + m + n)，m、n 为两组约束条数；空间复杂度：O(k + m + n)，图与队列的开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int k;  // 成员变量：数字范围 1..k，供内部拓扑排序函数 f 使用

    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {  // k 阶矩阵；rowConditions 约束行的上下顺序，colConditions 约束列的左右顺序
        this->k = k;  // 保存到成员变量，内部函数 f 才能访问到 k
        auto row = f(rowConditions);  // 对行约束做拓扑排序，得到数字从上到下的排列
        auto col = f(colConditions);  // 对列约束做拓扑排序，得到数字从左到右的排列
        if (row.empty() || col.empty()) return {};  // 任一方向拓扑排序失败（存在环）则无解，直接返回空矩阵
        vector<vector<int>> ans(k, vector<int>(k));  // k×k 答案矩阵，未填的位置保持 0
        vector<int> m(k + 1);  // 映射「数字 → 应放的列下标」
        for (int i = 0; i < k; ++i) {  // 遍历列方向的拓扑序
            m[col[i]] = i;  // col 中第 i 个数字应该放在第 i 列
        }  // 列映射建立完毕
        for (int i = 0; i < k; ++i) {  // 遍历行方向的拓扑序，逐行放置数字
            ans[i][m[row[i]]] = row[i];  // 第 i 行放 row[i]，列位置由列映射决定，从而同时满足行列两组约束
        }  // 所有数字放置完毕
        return ans;  // 返回构造出的矩阵
    }  // buildMatrix 方法结束

    vector<int> f(vector<vector<int>>& cond) {  // 辅助函数：对一组先后约束做拓扑排序，返回节点顺序
        vector<vector<int>> g(k + 1);  // 邻接表，节点编号 1..k
        vector<int> indeg(k + 1);  // 入度数组，用来找出拓扑排序的起点
        for (auto& e : cond) {  // 遍历每条约束 [a, b]，表示 a 必须排在 b 前面
            int a = e[0], b = e[1];  // 取出前驱 a 与后继 b
            g[a].push_back(b);  // 建一条有向边 a → b
            ++indeg[b];  // b 多了一个前驱，入度加一
        }  // 图建好
        queue<int> q;  // BFS 队列，存放当前入度为 0（可以放置）的节点
        for (int i = 1; i < k + 1; ++i) {  // 枚举所有数字 1..k
            if (!indeg[i]) {  // 入度为 0 说明它没有前置要求，可以最先放置
                q.push(i);  // 加入队列作为排序起点
            }  // if 判断结束
        }  // 初始队列构造完毕
        vector<int> res;  // 记录拓扑序
        while (!q.empty()) {  // BFS 直到没有可放节点
            for (int n = q.size(); n; --n) {  // 按层处理：先固定本层节点数，避免新入队的节点影响本层
                int i = q.front();  // 取出队首节点
                res.push_back(i);  // 把它加入拓扑序
                q.pop();  // 弹出已处理节点
                for (int j : g[i]) {  // 遍历 i 的所有后继
                    if (--indeg[j] == 0) {  // 后继少了一个前驱；入度减到 0 说明它现在可以放置了
                        q.push(j);  // 入队等待处理
                    }  // if 判断结束
                }  // 后继遍历结束
            }  // 本层处理结束
        }  // BFS 结束
        return res.size() == k ? res : vector<int>();  // 只有 k 个数字都被排出（无环）才有效，否则返回空表示无解
    }  // 辅助函数结束
};  // 题解类结束