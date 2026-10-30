// 题目：1136. 并行课程（Parallel Courses）
// 思路：Kahn 拓扑排序分层 BFS：每轮把入度为 0 的课程全部修掉，层数就是最少学期数；结束时仍有剩余课程说明有环。
// 时间复杂度：O(n + m)，每条边每个点各访问一次；空间复杂度：O(n + m)，邻接表与入度数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumSemesters(int n, vector<vector<int>>& relations) {  // n 门课程（编号 1..n），relations[i] = [先修课, 后续课]，返回修完全部课程的最少学期数，有环则返回 -1
        vector<vector<int>> g(n);  // 邻接表：g[u] 存放所有以 u 为先修课的后继课程
        vector<int> indeg(n);  // 每个节点的入度，即它还剩几门先修课没修
        for (auto& r : relations) {  // 遍历所有先修关系建图
            int prev = r[0] - 1, nxt = r[1] - 1;  // 课程编号从 1 开始，减 1 转成 0..n-1 的数组下标
            g[prev].push_back(nxt);  // 记录有向边 prev -> nxt
            ++indeg[nxt];  // 后继课程的入度加 1
        }  // 建图循环结束
        queue<int> q;  // Kahn 算法的 BFS 队列，存放当前学期可以修的课程
        for (int i = 0; i < n; ++i) {  // 先扫描一遍，找出初始入度为 0 的课
            if (indeg[i] == 0) {  // 入度为 0 表示没有任何先修要求
                q.push(i);  // 入队，作为第一学期就能修的课
            }  // 判断结束
        }  // 初始入队结束
        int ans = 0;  // 已修完的学期数
        while (!q.empty()) {  // 每一轮 while 处理一个学期
            ++ans;  // 学期数加 1
            for (int k = q.size(); k; --k) {  // 只弹出本轮开始时队列里的节点（用 k 记录个数），保证不同学期的课不会混在一起
                int i = q.front();  // 取出队首课程
                q.pop();  // 出队
                --n;  // 这门课修完了，剩余未修课程数减 1
                for (int& j : g[i]) {  // 遍历它的所有后继课程
                    if (--indeg[j] == 0) {  // 先修课少了一门，入度减 1；减到 0 说明后继课的依赖已全部满足
                        q.push(j);  // 后继课程可以修了，入队等下一学期处理
                    }  // 判断结束
                }  // 后继遍历结束
            }  // 本层（本学期）节点处理完毕
        }  // 队列空说明没有可再修的课
        return n == 0 ? ans : -1;  // n 归 0 表示所有课程都修完且无环，返回学期数；否则图有环，返回 -1
    }  // 方法结束
};  // 类定义结束