// 题目：886. 可能的二分法（Possible Bipartition）
// 思路：把「互相讨厌」建成无向图，DFS 二分染色；相邻点一旦同色就说明无法分成两组。
// 时间复杂度：O(n + m)，m 为讨厌关系数，每条边访问常数次；空间复杂度：O(n + m)，邻接表 + 染色数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {  // n 个人（编号 1..n），dislikes 为互相讨厌的人对
        unordered_map<int, vector<int>> g;  // 邻接表：把讨厌关系建成无向图
        for (auto& e : dislikes) {  // 逐条关系建边
            int a = e[0] - 1, b = e[1] - 1;  // 编号从 1..n 平移成 0..n-1，方便直接当下标用
            g[a].push_back(b);  // a 讨厌 b，加边 a→b
            g[b].push_back(a);  // b 也讨厌 a，加反向边，构成无向图
        }  // 建图完成
        vector<int> color(n);  // 染色数组：0 表示未访问，1 和 2 表示分属两组
        function<bool(int, int)> dfs = [&](int i, int c) -> bool {  // 深度优先染色：尝试把结点 i 染成颜色 c
            color[i] = c;  // 先给当前结点上色
            for (int j : g[i]) {  // 遍历 i 的所有邻居
                if (!color[j] && !dfs(j, 3 - c)) return false;  // 邻居未染色则递归染成相反色 3-c，递归失败说明冲突
                if (color[j] == c) return false;  // 邻居与自己同色，说明出现冲突，不能二分
            }  // 邻居检查完毕
            return true;  // 以 i 为起点的连通块染色成功
        };  // lambda 表达式定义结束
        for (int i = 0; i < n; ++i) {  // 图可能不连通，需要对每个连通块都尝试染色
            if (!color[i] && !dfs(i, 1)) return false;  // 未染色的点作为新连通块起点，先染成 1 号色
        }  // 所有连通块都已检查
        return true;  // 全部连通块都成功二分染色，返回 true
    }  // 方法结束
};  // 类定义结束
