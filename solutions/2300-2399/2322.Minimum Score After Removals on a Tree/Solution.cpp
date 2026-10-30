// 题目：2322. 从树中删除边的最小分数（Minimum Score After Removals on a Tree）
// 核心思路：第一刀把树切成两半并求出其中一侧的异或和，再在这侧内部枚举第二刀，把树分成三段，用三段异或值的极差更新最小分数。
// 时间复杂度：O(n^2)，每条边都会触发一次内部 DFS；空间复杂度：O(n)，用于邻接表与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {  // nums：节点权值；edges：无向边列表
        int n = nums.size();  // 节点个数
        vector<int> g[n];  // 邻接表，g[i] 保存与节点 i 相邻的所有节点
        for (const auto& e : edges) {  // 遍历每条边，构建无向图
            int a = e[0], b = e[1];  // 边的两个端点
            g[a].push_back(b);  // a 的邻居加上 b
            g[b].push_back(a);  // b 的邻居加上 a
        }  // 结束建图循环
        int s = 0, s1 = 0;  // s：全树异或和；s1：割掉第一条边后某一侧的异或和
        int ans = INT_MAX;  // 答案先置为最大整数
        for (int x : nums) {  // 求整棵树的异或和
            s ^= x;  // 依次异或每个节点的权值
        }
        auto dfs = [&](this auto&& dfs, int i, int fa) -> int {  // 递归求以 i 为根、父节点为 fa 的子树异或和（C++23 的 this 推导）
            int res = nums[i];  // 先放入当前节点自身的权值
            for (int j : g[i]) {  // 遍历 i 的所有邻居
                if (j != fa) {  // 跳过父节点，避免走回头路
                    res ^= dfs(j, i);  // 异或上这棵子树的结果
                }  // 结束邻居循环
            }
            return res;  // 返回该子树的异或和
        };
        auto dfs2 = [&](this auto&& dfs2, int i, int fa) -> int {  // 固定第一条边后，在子树内部枚举第二条边
            int res = nums[i];  // 当前节点权值
            for (int j : g[i]) {  // 遍历邻居
                if (j != fa) {  // 不回头
                    int s2 = dfs2(j, i);  // 递归得到 j 子树异或和，它就是第二刀切下的那一部分
                    res ^= s2;  // 把这部分并入当前子树
                    int mx = max({s ^ s1, s2, s1 ^ s2});  // 三段异或值中的最大值
                    int mn = min({s ^ s1, s2, s1 ^ s2});  // 三段异或值中的最小值
                    ans = min(ans, mx - mn);  // 分数是极差，尝试更新最小分数
                }  // 结束邻居循环
            }
            return res;  // 返回该子树的异或和
        };
        for (int i = 0; i < n; ++i) {  // 枚举第一条被删边的一个端点 i
            for (int j : g[i]) {  // 枚举第一条被删边的另一个端点 j
                s1 = dfs(i, j);  // 以 i 为根、绕开 j 求出一侧的异或和
                dfs2(i, j);  // 在这一侧内部枚举第二条边并更新答案
            }
        }
        return ans;  // 返回最小分数
    }
};
