// 题目：785. 判断二分图（Is Graph Bipartite）
// 思路：对每个连通分量 DFS 二染色，颜色取 1 与 -1；若某条边的两端同色说明无法二分。
// 时间复杂度：O(n + m)，每个点与每条边只访问一次；空间复杂度：O(n)，存颜色与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isBipartite(vector<vector<int>>& graph) {  // graph：邻接表；返回这张无向图能否被二染色
        int n = graph.size();  // 结点个数
        vector<int> color(n);  // color[v]：0 表示未染色，1 与 -1 表示两种颜色（默认初始化为 0）
        auto dfs = [&](this auto&& dfs, int a, int c) -> bool {  // C++23 显式对象参数：把 lambda 自身作为参数传入，这样 lambda 才能递归调用自己
            color[a] = c;  // 把结点 a 染成颜色 c
            for (int b : graph[a]) {  // 枚举 a 的所有邻居
                if (color[b] == c || (color[b] == 0 && !dfs(b, -c))) {  // 邻居已同色即冲突；邻居未染色时递归染成反色，失败也说明冲突
                    return false;  // 出现矛盾，这片连通分量不是二分图
                }
            }
            return true;  // a 引出的所有分支都染色成功
        };  // 递归 lambda 定义结束
        for (int i = 0; i < n; ++i) {  // 图可能不连通，需要枚举每个点作为新连通分量的起点
            if (color[i] == 0 && !dfs(i, 1)) {  // 未染色的点任选颜色 1 开始染色
                return false;  // 某个分量染色失败，整体不是二分图
            }
        }
        return true;  // 所有连通分量都满足二染色
    }
};
