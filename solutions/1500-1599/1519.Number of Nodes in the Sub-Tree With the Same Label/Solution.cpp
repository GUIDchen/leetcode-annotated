// 题目：1519. 子树中标签相同的节点数（Number of Nodes in the Sub-Tree With the Same Label）
// 核心思路：从根做一次 DFS，用全局计数器 cnt[字母] 记录已访问节点的标签数；进入子树前取快照，退出时再取一次，两次差值就是该子树中同标签节点数。
// 时间复杂度：O(n)，每个节点只进出各一次（26 个字母视为常数）；空间复杂度：O(n)，邻接表 + 递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {  // n：节点个数；edges：无向边；labels：每个节点的字符标签
        vector<vector<int>> g(n);  // 邻接表：g[i] 存与节点 i 相连的所有节点
        for (auto& e : edges) {  // 逐条边建无向图
            int a = e[0], b = e[1];  // 取出这条边的两个端点
            g[a].push_back(b);  // a → b
            g[b].push_back(a);  // b → a（无向边必须双向添加）
        }  // 建图结束
        vector<int> ans(n);  // 答案数组，ans[i] 最终是节点 i 子树中与它标签相同的节点数
        int cnt[26]{};  // 全局计数器，cnt[c] 是当前已访问节点中标签 c 出现的次数；{} 让 26 个元素都初始化为 0
        function<void(int, int)> dfs = [&](int i, int fa) {  // 递归 lambda：i 为当前节点，fa 为父节点（防止沿父边往回走）
            int k = labels[i] - 'a';  // 把字符标签映射成 0~25 的下标
            ans[i] -= cnt[k];  // 先减去「进入子树前」的同类计数，作为快照参与后面的差值
            cnt[k]++;  // 把当前节点自己计入全局计数
            for (int& j : g[i]) {  // 遍历所有邻居
                if (j != fa) {  // 跳过父节点，只往子树方向递归
                    dfs(j, i);  // 递归处理子节点
                }  // if 结束
            }  // for 结束
            ans[i] += cnt[k];  // 再加回退出时的同类计数，与快照之差就是本子树中标签为 k 的节点数
        };  // lambda 定义结束（分号不能漏）
        dfs(0, -1);  // 从根节点 0 开始 DFS，-1 表示没有父节点
        return ans;  // 返回每个节点的统计结果
    }  // 方法结束
};  // 类定义结束
