// 3466. 最大硬币收集量 / Maximum Coin Collection
// 核心思路：记忆化搜索，状态为（列号、当前泳道、剩余换道次数），每步可在本列取币或换道后再取，取最大值。
// 复杂度：时间 O(n)，空间 O(n)（状态数 3n 个，每状态 O(1) 转移）。
class Solution {  // 定义题解类
public:  // 公有方法
    long long maxCoins(vector<int>& lane1, vector<int>& lane2) {  // 返回最多换道两次能收集到的最多硬币数
        int n = lane1.size();  // 列数
        long long ans = -1e18;  // 全局答案，初始化为极小值
        vector<vector<vector<long long>>> f(n, vector<vector<long long>>(2, vector<long long>(3, -1e18)));  // 记忆化数组 f[i][j][k]：第 i 列、第 j 条泳道、还剩 k 次换道
        auto dfs = [&](this auto&& dfs, int i, int j, int k) -> long long {  // 递归函数：从第 i 列第 j 条泳道出发、剩余 k 次换道时的最大收益
            if (i >= n) {  // 已经越过最后一列
                return 0LL;  // 无法继续收集硬币
            }  // 结束越界分支
            if (f[i][j][k] != -1e18) {  // 该状态已经计算过
                return f[i][j][k];  // 直接返回记忆值
            }  // 结束记忆命中分支
            int x = j == 0 ? lane1[i] : lane2[i];  // 当前格子的硬币数
            long long ans = max((long long) x, dfs(i + 1, j, k) + x);  // 两种选择：只取当前格，或取当前格后沿本泳道继续
            if (k > 0) {  // 还有剩余换道次数
                ans = max(ans, dfs(i + 1, j ^ 1, k - 1) + x);  // 换到另一条泳道并取当前格
                ans = max(ans, dfs(i, j ^ 1, k - 1));  // 先换道，再在同一列决定是否取币
            }  // 结束换道分支
            return f[i][j][k] = ans;  // 记忆并返回该状态的最优值
        };  // 结束递归函数定义
        for (int i = 0; i < n; ++i) {  // 枚举起点列
            ans = max(ans, dfs(i, 0, 2));  // 从第 0 条泳道、剩余 2 次换道开始搜索
        }  // 结束起点枚举
        return ans;  // 返回最大硬币收集量
    }  // 结束方法
};  // 结束类定义
