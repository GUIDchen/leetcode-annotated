// 题目：879. 盈利计划（Profitable Schemes）
// 核心思路：三维记忆化搜索，状态为（计划下标，已用人数，已赚利润封顶到 minProfit），每个计划做「选 / 不选」的决策并累加方案数。
// 时间复杂度：O(m * n * minProfit)，每个状态只算一次；空间复杂度：O(m * n * minProfit)，记忆化表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {  // n：可用员工人数；minProfit：最低利润要求；group：每个计划需要的人数；profit：每个计划带来的利润
        int m = group.size();  // 计划总数，也是搜索的下标上界
        int f[m][n + 1][minProfit + 1];  // 记忆化表：f[i][j][k] 表示处理到第 i 个计划、已用 j 人、已赚 k 利润时，最终能盈利的方案数
        memset(f, -1, sizeof(f));  // 用 -1 表示「尚未计算」：方案数可能是 0，所以不能用 0 当哨兵
        const int mod = 1e9 + 7;  // 题目要求的取模常量
        function<int(int, int, int)> dfs = [&](int i, int j, int k) -> int {  // 递归 lambda：i 为当前计划下标，j 为已用人数，k 为已赚利润（封顶到 minProfit）
            if (i >= m) {  // 所有计划都已决策完
                return k == minProfit ? 1 : 0;  // 利润达到要求算一种可行方案，否则这种选择不可行
            }  // if 结束
            if (f[i][j][k] != -1) {  // 该状态已经计算过
                return f[i][j][k];  // 直接返回缓存值
            }  // if 结束
            int ans = dfs(i + 1, j, k);  // 不选第 i 个计划：人数与利润都不变
            if (j + group[i] <= n) {  // 选第 i 个计划的前提是人数还够用
                ans += dfs(i + 1, j + group[i], min(k + profit[i], minProfit));  // 选它：人数增加，利润累加并封顶到 minProfit（超出部分与刚好达标等价）
            }  // if 结束
            ans %= mod;  // 累加后取模，防止计数溢出
            return f[i][j][k] = ans;  // 写入缓存并返回本状态的方案数
        };  // dfs 定义结束
        return dfs(0, 0, 0);  // 从第 0 个计划、0 人、0 利润开始搜索
    }  // profitableSchemes 结束
};  // Solution 类结束