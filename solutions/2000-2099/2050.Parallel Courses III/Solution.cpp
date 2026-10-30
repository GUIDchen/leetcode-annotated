// 题目：2050. 并行课程 III（Parallel Courses III）
// 思路：把先修关系建成有向图，拓扑排序的同时做最长路 DP：f[i] = time[i] + max(f[前驱])，答案取所有 f 的最大值。
// 时间复杂度：O(n + m)，n 为课程数、m 为先修关系数；空间复杂度：O(n + m)，邻接表、入度数组与 DP 数组。
class Solution {  // 题解类
public:  // 题解方法对外可见
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {  // n 门课程；relations 是先修关系；time 是每门课的耗时
        vector<vector<int>> g(n);  // 邻接表：g[a] 存放所有以 a 为先修课的课程
        vector<int> indeg(n);  // indeg[i] 表示课程 i 还缺多少个先修课
        for (auto& e : relations) {  // 遍历每条先修关系
            int a = e[0] - 1, b = e[1] - 1;  // 题目给的是 1 下标，统一减 1 转成 0 下标
            g[a].push_back(b);  // 从先修课 a 指向后继课 b 连一条有向边
            ++indeg[b];  // b 的入度加一，表示又多了一个前置依赖
        }  // 建图结束
        queue<int> q;  // 拓扑排序队列：存放当前所有可修课程
        vector<int> f(n);  // f[i] 表示课程 i 修完的最早月份
        int ans = 0;  // ans 记录所有课程完成时刻的最大值，即最终答案
        for (int i = 0; i < n; ++i) {  // 扫一遍课程，找出初始入度为 0 的课程
            int v = indeg[i], t = time[i];  // v 是入度，t 是该课程自身需要的月份
            if (v == 0) {  // 入度为 0 说明没有先修课，可以立刻开始
                q.push(i);  // 入队，稍后用它更新后继课程
                f[i] = t;  // 它的最早完成时间就是自身耗时
                ans = max(ans, t);  // 用它的完成时间更新全局答案
            }  // 初始可修课程处理完毕
        }  // 初始课程循环结束
        while (!q.empty()) {  // 队列非空说明还有课程可以继续推进
            int i = q.front();  // 取队首课程编号
            q.pop();  // 出队
            for (int j : g[i]) {  // 遍历以 i 为先修课的所有后继课程 j
                if (--indeg[j] == 0) {  // 消耗一条依赖；入度减到 0 说明 j 的所有先修课都完成了
                    q.push(j);  // j 可以修了，入队
                }  // 入度判断结束
                f[j] = max(f[j], f[i] + time[j]);  // 状态转移：j 必须等 i 修完才能开始，取较晚者
                ans = max(ans, f[j]);  // 用 j 的完成时间更新全局答案
            }  // 后继课程遍历结束
        }  // 队列处理结束
        return ans;  // 返回所有课程的最晚完成时间
    }  // minimumTime 方法结束
};  // 类定义结束