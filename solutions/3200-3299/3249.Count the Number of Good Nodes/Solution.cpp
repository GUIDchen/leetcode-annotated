// 题目：3249. 统计好节点的数目（Count the Number of Good Nodes）
// 思路：从根 0 做一次 DFS 返回每棵子树的大小；若某节点各子节点的子树大小都相同，它就是好节点。
// 时间复杂度：O(n)，每条边只被访问两次；空间复杂度：O(n)，邻接表与递归栈。
class Solution {  // // LeetCode 约定的题解类
public:  // // 题解方法对外可见
    int countGoodNodes(vector<vector<int>>& edges) {  // // edges 是树的 n-1 条无向边，返回好节点的个数
        int n = edges.size() + 1;  // // 节点总数等于边数加一
        vector<int> g[n];  // // 邻接表，g[i] 保存与节点 i 相邻的所有节点
        for (const auto& e : edges) {  // // 逐条读入无向边
            int a = e[0], b = e[1];  // // 取出这条边连接的两个端点 a、b
            g[a].push_back(b);  // // 把 b 记入 a 的邻接表
            g[b].push_back(a);  // // 把 a 记入 b 的邻接表（无向边要存两次）
        }  // // 建图完成
        int ans = 0;  // // ans 累计好节点的个数
        auto dfs = [&](this auto&& dfs, int a, int fa) -> int {  // // DFS：返回以 a 为根的子树大小；this auto&& dfs 是 C++23 的显式对象参数，让 lambda 能递归调用自己
            int pre = -1, cnt = 1, ok = 1;  // // pre 记录第一个子节点的子树大小（-1 表示还没有），cnt 是当前子树大小，ok 表示各子节点子树大小是否全相同
            for (int b : g[a]) {  // // 遍历 a 的所有邻居
                if (b != fa) {  // // 跳过父节点 fa，只往子节点方向递归
                    int cur = dfs(b, a);  // // 递归求子节点 b 的子树大小
                    cnt += cur;  // // 把子树的节点数累加到当前子树
                    if (pre < 0) {  // // 第一个子节点只用来设置比较基准
                        pre = cur;  // // 记下这个基准值
                    } else if (pre != cur) {  // // 之后的子节点必须与基准相同，否则不是好节点
                        ok = 0;  // // 子树大小不一致，标记 ok = 0
                    }  // // 不一致分支结束
                }  // // 子节点判断结束
            }  // // 邻居遍历结束
            ans += ok;  // // ok 为 1 时 ans 加一，正好把 bool 当整数用
            return cnt;  // // 返回当前子树的大小给父节点
        };  // // DFS lambda 定义结束
        dfs(0, -1);  // // 从根节点 0 开始遍历，根的父节点记为 -1
        return ans;  // // 返回好节点总数
    }  // // 方法结束
};  // // 类结束
