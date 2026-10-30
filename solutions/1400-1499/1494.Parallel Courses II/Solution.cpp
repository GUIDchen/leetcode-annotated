// 题目：1494. 并行课程 II（Parallel Courses II）
// 思路：把「已修课程集合」压成位掩码，在状态图上做 BFS；每学期从当前可修课程里挑不超过 k 门，超过 k 时枚举大小为 k 的子集。
// 时间复杂度：O(n·2^n + 3^n)，状态转移与子集枚举；空间复杂度：O(2^n)，访问集合与队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {  // 返回修完全部 n 门课所需的最少学期数
        vector<int> d(n + 1);  // d[i] 是修课程 i 之前必须先修完的课程集合（用位掩码表示）
        for (auto& e : relations) {  // 遍历每条先修关系
            d[e[1]] |= 1 << e[0];  // 课程 e[1] 依赖 e[0]，把 e[0] 对应的位打上标记
        }  // 关系遍历结束
        queue<pair<int, int>> q;  // BFS 队列：first 是已修课程掩码，second 是已用学期数
        q.push({0, 0});  // 初始状态：一门课都没修，用了 0 个学期
        unordered_set<int> vis{{0}};  // 记录已经访问过的掩码，避免重复入队
        while (!q.empty()) {  // 队列非空就继续扩展状态
            auto [cur, t] = q.front();  // 结构化绑定取出队首的掩码与学期数
            q.pop();  // 弹出队首
            if (cur == (1 << (n + 1)) - 2) {  // 目标掩码：第 1..n 位全为 1（第 0 位不用，所以再减 2）
                return t;  // 全部修完，当前学期数就是最少学期数
            }  // 到达目标状态
            int nxt = 0;  // 记录本学期可以修的课程
            for (int i = 1; i <= n; ++i) {  // 检查每一门课
                if ((cur & d[i]) == d[i]) {  // 该课程的所有先修课都已修完（先修集合是已修集合的子集）
                    nxt |= 1 << i;  // 把这门课加入本学期可修集合
                }  // if 结束
            }  // for 结束，nxt 收集了所有当前可修的课程
            nxt ^= cur;  // 异或掉已经修过的位，只留下还没修的课程
            if (__builtin_popcount(nxt) <= k) {  // 可修课程数不超过一学期容量 k，可以一次全部修完
                if (!vis.count(nxt | cur)) {  // 新状态没有被访问过
                    vis.insert(nxt | cur);  // 标记新状态已访问
                    q.push({nxt | cur, t + 1});  // 学期数加一后入队
                }  // if 结束
            } else {  // 可修课程超过 k 门，需要从中挑出恰好 k 门
                int x = nxt;  // 保存候选集合，子集枚举时作为掩码上限
                while (nxt) {  // 枚举 x 的所有非空子集
                    if (__builtin_popcount(nxt) == k && !vis.count(nxt | cur)) {  // 子集大小正好是 k，且该状态尚未访问
                        vis.insert(nxt | cur);  // 标记新状态
                        q.push({nxt | cur, t + 1});  // 学期数加一后入队
                    }  // if 结束
                    nxt = (nxt - 1) & x;  // 子集枚举的标准写法：得到下一个更小的子集
                }  // while 结束
            }  // else 结束
        }  // while 结束
        return 0;  // 理论上不会执行到这里（题目保证可以修完）
    }  // 方法结束
};  // 类定义结束