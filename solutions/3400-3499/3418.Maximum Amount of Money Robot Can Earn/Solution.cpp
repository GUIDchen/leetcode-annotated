// 3418. 机器人可以获得的最大金币数 / Maximum Amount of Money Robot Can Earn
// 核心思路：记忆化搜索 dfs(i, j, k)，k 为剩余可抵消负值的次数；正常转移直接累加金币，遇到负数时可消耗一次 k 把这枚负币当作没吃
// 复杂度：时间 O(m·n·3)，空间 O(m·n·3) 用于记忆化数组
class Solution {  // 定义题解类
public:  // 公有方法区
    int maximumAmount(vector<vector<int>>& coins) {  // 求机器人从左上角走到右下角能获得的最大金币数
        int m = coins.size(), n = coins[0].size();  // 网格的行数与列数
        vector<vector<vector<int>>> f(m, vector<vector<int>>(n, vector<int>(3, -1)));  // 记忆化数组：f[i][j][k] 表示状态 (i, j, k) 的最优值，-1 表示未计算
        auto dfs = [&](this auto&& dfs, int i, int j, int k) -> int {  // 定义递归 lambda：i、j 为位置，k 为剩余抵消次数
            if (i >= m || j >= n) {  // 越界说明这条路不可达
                return INT_MIN / 2;  // 返回极小值，避免非法路径被选中（取半以规避后续加法溢出）
            }  // 越界分支结束
            if (f[i][j][k] != -1) {  // 该状态已经算过则直接返回缓存值
                return f[i][j][k];  // 返回缓存的最优值
            }  // 已访问缓存分支结束
            if (i == m - 1 && j == n - 1) {  // 到达终点时的基准情形
                return k > 0 ? max(0, coins[i][j]) : coins[i][j];  // 终点若还有抵消次数，可把负金币抵消为 0；否则只能拿到当前金币
            }  // 终点分支结束
            int ans = coins[i][j] + max(dfs(i + 1, j, k), dfs(i, j + 1, k));  // 正常走法：吃掉当前金币，再从下方或右方取较大者
            if (coins[i][j] < 0 && k > 0) {  // 若当前金币为负且仍有抵消次数，可以消耗一次把它消掉
                ans = max({ans, dfs(i + 1, j, k - 1), dfs(i, j + 1, k - 1)});  // 直接跳过这枚负币，从下方或右方继续递归，取三者最大值
            }  // 抵消分支结束
            return f[i][j][k] = ans;  // 把答案写入记忆化数组并返回
        };  // lambda 定义结束
        return dfs(0, 0, 2);  // 从左上角出发，初始有 2 次抵消机会
    }  // 方法结束
};  // 类定义结束
