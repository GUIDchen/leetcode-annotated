// 题目：207. 课程表（Course Schedule）
// 思路：Kahn 拓扑排序。先修关系建有向图并统计入度，入度为 0 的课入队，逐个出队消去出边，最后看是否所有课都被消掉。
// 时间复杂度：O(n + m)，n 为课程数、m 为先修关系数；空间复杂度：O(n + m)，需要邻接表和入度数组。
class Solution {  // LeetCode 约定的题解类
public:  // 解题接口对外可见
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {  // numCourses 是课程总数，prerequisites[i] = [a, b] 表示修 a 之前必须先修 b
        vector<vector<int>> g(numCourses);  // 邻接表：g[b] 存放所有以 b 为先修课的课程 a，即 b -> a 的有向边
        vector<int> indeg(numCourses);  // 入度数组：indeg[a] 表示课程 a 还有多少门先修课没完成
        for (auto& p : prerequisites) {  // 遍历每一条先修关系，建图并累计入度
            int a = p[0], b = p[1];  // 拆出两个端点：a 是后继课程，b 是先修课程
            g[b].push_back(a);  // 建一条 b -> a 的有向边
            ++indeg[a];  // a 的入度加一
        }  // 建图结束
        queue<int> q;  // BFS 队列：存放入度为 0、可以立刻学习的课程
        for (int i = 0; i < numCourses; ++i) {  // 扫描所有课程
            if (indeg[i] == 0) {  // 入度为 0，说明没有未完成的先修课
                q.push(i);  // 入队，作为学习的起点
            }  // if 分支结束
        }  // 初始队列构造完成
        while (!q.empty()) {  // 队列非空就继续：每弹出一门课等价于把它修完
            int i = q.front();  // 取出队首课程
            q.pop();  // 弹出队首，避免重复处理
            --numCourses;  // 修完一门课，剩余未修课程数减一
            for (int j : g[i]) {  // 遍历这门课的所有后继课程
                if (--indeg[j] == 0) {  // 后继课程入度减一；减到 0 说明它的先修课全部完成
                    q.push(j);  // 入度归零，可以入队等待学习
                }  // if 分支结束
            }  // 后继课程遍历结束
        }  // 队列为空，能修的课已经全部修完
        return numCourses == 0;  // 所有课程都被修完说明不存在环，可以完成全部课程
    }  // 方法结束
};  // 类定义结束
