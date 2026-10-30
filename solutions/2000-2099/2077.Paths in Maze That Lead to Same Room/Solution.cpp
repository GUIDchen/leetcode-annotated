// 题目：2077. 殊途同归（Paths in Maze That Lead to Same Room）
// 思路：走廊构成无向图，枚举每个房间作为三元环的中间点，统计它任意两个邻居之间是否也有边；每个三元环被数 3 次，最后除以 3。
// 时间复杂度：O(n + m + Σ deg(v)²)，m 为走廊数；空间复杂度：O(n + m)，邻接表存储整张图。
class Solution {  // 题解类：所有题解方法都写在这里
public:  // 方法对外可见（LeetCode 约定）
    int numberOfPaths(int n, vector<vector<int>>& corridors) {  // n 是房间数（编号 1..n），corridors 是无向边列表
        vector<unordered_set<int>> g(n + 1);  // 邻接表：每个房间用一个哈希集合存邻居，便于 O(1) 判断两点是否相邻
        for (auto& c : corridors) {  // 逐条读入走廊
            int a = c[0], b = c[1];  // 取出这条走廊连接的两个房间
            g[a].insert(b);  // a 的邻居集合里记录 b
            g[b].insert(a);  // b 的邻居集合里记录 a（无向图两边都存）
        }  // 建图循环结束
        int ans = 0;  // 统计三元环被数到的总次数
        for (int c = 1; c <= n; ++c) {  // 枚举每个房间作为三元环的中间点 c
            vector<int> nxt;  // 把邻居集合转成数组，便于用下标两两枚举
            nxt.assign(g[c].begin(), g[c].end());  // 拷贝邻居集合到数组中
            int m = nxt.size();  // 邻居个数
            for (int i = 0; i < m; ++i) {  // 枚举第一个邻居
                for (int j = i + 1; j < m; ++j) {  // 枚举第二个邻居，j 从 i+1 开始避免重复枚举同一对
                    int a = nxt[i], b = nxt[j];  // 取出这一对不同邻居 a、b
                    ans += g[b].count(a);  // a 与 b 也相邻，则 c-a-b-c 构成一个长度为 3 的环
                }  // 第二个邻居循环结束
            }  // 第一个邻居循环结束
        }  // 中间点枚举结束
        return ans / 3;  // 同一个三元环会被它的 3 个顶点各数一次，所以要除以 3
    }  // 方法结束
};  // 类定义结束