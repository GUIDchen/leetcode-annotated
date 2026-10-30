// 题目：2246. 相邻字符不同的最长路径（Longest Path With Different Adjacent Characters）
// 思路：树形 DP，dfs 返回以结点 i 为起点向下的最长合法单链，回溯时用「历史最长子链 + 当前子链」拼出过 i 的路径并更新答案。
// 时间复杂度：O(n)，每个结点只被访问一次；空间复杂度：O(n)，邻接表与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestPath(vector<int>& parent, string s) {  // parent：每个结点的父结点（parent[0] = -1）；s：每个结点上的字符
        int n = parent.size();  // 结点总数
        vector<int> g[n];  // 邻接表形式的树：g[u] 存放 u 的所有孩子结点
        for (int i = 1; i < n; ++i) {  // 根结点固定是 0，其余结点逐个挂到它的父亲下面
            g[parent[i]].push_back(i);  // 把子结点 i 接到 parent[i] 的孩子列表中
        }  // 建树完成
        int ans = 0;  // 记录「两条不同子链拼接成」的最长路径边数
        function<int(int)> dfs = [&](int i) -> int {  // 递归 lambda：返回以 i 为起点向下的最长「相邻字符不同」单链长度（单位是边）
            int mx = 0;  // mx：以 i 为顶点的最长合法单链，初值 0 表示只取 i 自己
            for (int j : g[i]) {  // 遍历 i 的每个孩子
                int x = dfs(j) + 1;  // 孩子子树里的最长单链 + 边 (i, j) 本身这条边
                if (s[i] != s[j]) {  // 只有父子字符不同时，这两段才能接在一起
                    ans = max(ans, mx + x);  // 用「之前最长的另一条子链」与当前子链拼成经过 i 的路径，更新答案
                    mx = max(mx, x);  // 再把当前子链纳入 mx，供后面的兄弟结点拼接使用
                }  // 该孩子处理完毕
            }  // 所有孩子处理完毕
            return mx;  // 返回向下的最长单链给父亲结点使用
        };  // lambda 定义结束
        dfs(0);  // 从根结点开始 DFS
        return ans + 1;  // ans 统计的是边数，题目要的是结点数，故加 1（空路径时也能得到 1）
    }  // 方法结束
};  // 类定义结束
