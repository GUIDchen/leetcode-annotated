// 题目：3244. 新增道路查询后的最短距离 II（Shortest Distance After Road Addition Queries II）
// 思路：用 nxt 维护链 0->1->...->(n-1)，新边覆盖的中间点直接从链上删除，链上剩余边数 cnt 就是答案。
// 时间复杂度：O(n+q)，每个点最多被删除一次；空间复杂度：O(n)，nxt 数组与答案数组。
class Solution {  // // LeetCode 约定的题解类
public:  // // 题解方法对外可见
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {  // // n 为城市数，queries 为依次新增的道路，返回每次加边后 0 到 n-1 的最短距离
        vector<int> nxt(n - 1);  // // nxt[i] 表示从 i 出发、跳过所有已被覆盖的点之后到达的下一个点
        iota(nxt.begin(), nxt.end(), 1);  // // 初始时 i 的下一个点就是 i+1，即整条链 0-1-2-...-(n-1)
        int cnt = n - 1;  // // cnt 维护当前链上的边数，也就是 0 到 n-1 的最短距离
        vector<int> ans;  // // ans 收集每次加边后的答案
        for (const auto& q : queries) {  // // 依次处理每条新增道路
            int u = q[0], v = q[1];  // // u、v 分别是新边的起点与终点
            if (nxt[u] && nxt[u] < v) {  // // 只有 u 还能继续往后走（nxt[u] 非 0）且新边确实能缩短链时才处理
                int i = nxt[u];  // // 从 u 原来的下一个点开始，逐个跳过被新边覆盖的点
                while (i < v) {  // // 被覆盖的区间是 [nxt[u], v)
                    --cnt;  // // 每跳过一个点，链上就少一条边
                    int t = nxt[i];  // // 先记下 i 原来的后继，稍后靠它继续往后走
                    nxt[i] = 0;  // // 把 i 标记为已删除（不再作为链上的点）
                    i = t;  // // 沿着原后继继续前进
                }  // // 覆盖区间处理完毕
                nxt[u] = v;  // // 让 u 直接指向 v，完成链的压缩
            }  // // 本次加边处理结束
            ans.push_back(cnt);  // // 当前链上剩余的边数就是最短距离
        }  // // 查询循环结束
        return ans;  // // 返回全部答案
    }  // // 方法结束
};  // // 类结束
