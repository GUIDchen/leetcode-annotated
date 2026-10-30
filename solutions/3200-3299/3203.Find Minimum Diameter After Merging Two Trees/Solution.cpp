// 题目：3203. 合并两棵树后的最小直径（Find Minimum Diameter After Merging Two Trees）
// 思路：先用两次 DFS 分别求出两棵树的直径 d1、d2；新直径只有三种可能——d1、d2、把两棵树各自「半径向上取整」后加一条新边，取三者最大值即可最小化。
// 时间复杂度：O(n + m)，两棵树各做两次 DFS；空间复杂度：O(n + m)，邻接表与递归栈。
class Solution {  // LeetCode 题解类，固定入口名
public:  // 解法方法对外可见
    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {  // 返回合并后的最小直径；edges1、edges2 分别是两棵树的边集
        int d1 = treeDiameter(edges1);  // 先求第一棵树的直径
        int d2 = treeDiameter(edges2);  // 再求第二棵树的直径
        return max({d1, d2, (d1 + 1) / 2 + (d2 + 1) / 2 + 1});  // 答案取三者最大值：只保留第一棵、只保留第二棵、或经新增边把两棵树连起来（各自半径向上取整再加 1）
    }  // 方法结束

    int treeDiameter(vector<vector<int>>& edges) {  // 用两次 DFS 求一棵树的直径（以边数计）
        int n = edges.size() + 1;  // n 个结点的树有 n-1 条边，所以结点数等于边数加一
        vector<int> g[n];  // 邻接表：g[u] 存放所有与 u 相邻的结点
        for (auto& e : edges) {  // 遍历每条边，双向建图
            int a = e[0], b = e[1];  // 取出边的两个端点
            g[a].push_back(b);  // 建立 a → b 的边
            g[b].push_back(a);  // 建立 b → a 的边
        }  // 建图结束
        int ans = 0, a = 0;  // ans 记录最远距离，a 记录这一轮 DFS 走到的最远结点
        auto dfs = [&](this auto&& dfs, int i, int fa, int t) -> void {  // 递归 lambda（C++23 的 deducing this）：从 i 出发求到各点的距离，fa 是父结点、t 是当前距离
            for (int j : g[i]) {  // 枚举 i 的所有邻居
                if (j != fa) {  // 不回头访问父结点，避免在树中绕圈
                    dfs(j, i, t + 1);  // 继续向子树递归，距离加一
                }  // 邻居遍历结束
            }  // 处理完所有子树后，再判断当前结点是否是更远的点
            if (ans < t) {  // 如果当前距离比已记录的最远距离更远
                ans = t;  // 更新最远距离
                a = i;  // 同时记下这个最远结点，作为下一轮 DFS 的起点
            }  // 判断结束
        };  // lambda 定义结束
        dfs(0, -1, 0);  // 第一次 DFS：从任意点 0 出发，找到直径的一个端点 a
        dfs(a, -1, 0);  // 第二次 DFS：从端点 a 出发，得到的 ans 就是直径长度
        return ans;  // 返回这棵树的直径（边数）
    }  // treeDiameter 方法结束
};  // 题解类结束
