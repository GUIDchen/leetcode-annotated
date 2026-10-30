// 题目：1857. 有向图中最大颜色值（Largest Color Value in a Directed Graph）
// 思路：拓扑排序 + 26 维 DP。dp[v][k] 表示以 v 结尾的路径上颜色 k 出现的最大次数；按拓扑序把 dp[i] 沿边传给后继 j，并按「颜色相同则 +1」更新；最后取全局最大值，若拓扑序长度小于 n 说明有环，返回 -1。
// 时间复杂度：O((n + m) × 26)，每条边对 26 种颜色各做一次转移；空间复杂度：O(26n)，dp 表加上图与入度数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int largestPathValue(string colors, vector<vector<int>>& edges) {  // colors：每个结点的颜色字母；edges：有向边，求路径上同一颜色出现的最大次数
        int n = colors.size();  // n：结点个数
        vector<vector<int>> g(n);  // 邻接表 g：g[a] 存放 a 的所有后继
        vector<int> indeg(n);  // 入度数组：用于拓扑排序，同时判断是否有环
        for (auto& e : edges) {  // 遍历每条边建立邻接表与入度
            int a = e[0], b = e[1];  // 取出边的起点 a 与终点 b
            g[a].push_back(b);  // a 指向 b
            ++indeg[b];  // b 的入度加一
        }  // 建图结束
        queue<int> q;  // 拓扑排序用的队列
        vector<vector<int>> dp(n, vector<int>(26));  // dp[i][k]：以 i 结尾的路径上颜色 k 出现的最多次数，初始全 0
        for (int i = 0; i < n; ++i) {  // 从所有入度为 0 的结点出发（它们是路径起点）
            if (indeg[i] == 0) {  // 入度为 0 才能作为起点
                q.push(i);  // 入队
                int c = colors[i] - 'a';  // 把起点字母映射到 0..25
                dp[i][c]++;  // 起点自身贡献一次该颜色
            }  // 起点初始化结束
        }  // for 结束
        int cnt = 0;  // cnt：已处理的结点数，用来判断是否存在环
        int ans = 1;  // ans：全局最大颜色值，单个结点至少为 1
        while (!q.empty()) {  // BFS 版拓扑排序
            int i = q.front();  // 取出队首结点
            q.pop();  // 出队
            ++cnt;  // 统计已处理结点数
            for (int j : g[i]) {  // 遍历 i 的所有后继 j
                if (--indeg[j] == 0) q.push(j);  // 入度减一，减到 0 说明 j 的所有前驱都已处理完，可以入队
                int c = colors[j] - 'a';  // j 的颜色下标
                for (int k = 0; k < 26; ++k) {  // 对 26 种颜色逐一做状态转移
                    dp[j][k] = max(dp[j][k], dp[i][k] + (c == k));  // dp[i][k] 加上 j 自身是否含颜色 k，取更优值
                    ans = max(ans, dp[j][k]);  // 用 dp[j][k] 更新全局答案
                }  // 颜色枚举结束
            }  // 后继枚举结束
        }  // 拓扑排序结束
        return cnt == n ? ans : -1;  // cnt == n 说明无环，返回答案；否则有环，任何颜色值都无意义，返回 -1
    }  // 方法结束
};  // 类定义结束