// 题目：188. 买卖股票的最佳时机 IV（Best Time to Buy and Sell Stock IV）
// 思路：记忆化搜索。dfs(i,j,k) 表示第 i 天、还剩 j 次交易额度、当前是否持股(k=1 持股)时的最大收益，用三维数组缓存。
// 时间复杂度：O(n·k)，每个状态只计算一次；空间复杂度：O(n·k)，记忆化数组的开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxProfit(int k, vector<int>& prices) {  // k 是最多交易次数，prices 是每日股价
        int n = prices.size();  // 天数
        int f[n][k + 1][2];  // 记忆化数组：f[天][剩余次数][是否持股]；用变长数组省去手动开堆
        memset(f, -1, sizeof(f));  // 全部初始化为 -1，表示该状态还没被计算过（收益不会为负）
        function<int(int, int, int)> dfs = [&](int i, int j, int k) -> int {  // 递归函数：注意形参 k 遮蔽了外层 k
            if (i >= n) {  // 已经越过最后一天，没有股票可交易
                return 0;  // 收益为 0，是递归的边界
            }
            if (f[i][j][k] != -1) {  // 该状态之前算过
                return f[i][j][k];  // 直接返回缓存值，避免重复搜索
            }
            int ans = dfs(i + 1, j, k);  // 方案一：今天什么都不做，收益与明天相同
            if (k) {  // 当前持股，只能选择卖出
                ans = max(ans, prices[i] + dfs(i + 1, j, 0));  // 以今天的价格卖出，之后回到空仓
            } else if (j) {  // 当前空仓且还有交易次数，可以选择买入
                ans = max(ans, -prices[i] + dfs(i + 1, j - 1, 1));  // 花钱买入（收益为负），次数减 1 并转为持股
            }
            return f[i][j][k] = ans;  // 先写入缓存，再把该状态的最优值返回
        };
        return dfs(0, k, 0);  // 从第 0 天、k 次额度、空仓状态开始搜索
    }
};