// 题目：3742. 网格中得分最大的路径（Maximum Path Score in a Grid）
// 核心思路：记忆化搜索，dfs(i, j, k) 表示「从 (0,0) 走到 (i,j)、还剩 k 点花费额度」时的最大分数；当前格的分数累加进去，值大于 0 时消耗一次额度；越界或额度为负说明路径非法，返回负无穷以便被 max 淘汰。
// 复杂度：时间 O(m*n*k)，每个状态只算一次；空间 O(m*n*k)，三维记忆化表加上递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxPathScore(vector<vector<int>>& grid, int k) {  // grid：取值 0/1/2 的网格；k：总花费上限；返回总花费不超过 k 时的最大分数，无合法路径则返回 -1
        int m = grid.size();  // 行数
        int n = grid[0].size();  // 列数
        int inf = 1 << 30;  // 用一个足够大的数表示无穷
        vector f(m, vector(n, vector<int>(k + 1, -1)));  // 记忆化数组，f[i][j][k] 表示走到 (i,j)、还剩 k 点花费时的最大分数，-1 表示尚未计算

        auto dfs = [&](this auto&& dfs, int i, int j, int k) -> int {  // 显式对象参数的递归 lambda：从 (0,0) 走到 (i,j) 的最大分数
            if (i < 0 || j < 0 || k < 0) {  // 越界或花费额度已经用尽
                return -inf;  // 该前缀路径非法，返回负无穷
            }  // 合法性判断结束
            if (i == 0 && j == 0) {  // 到达起点
                return 0;  // 起点之前还没有累积任何分数
            }  // 起点判断结束
            if (f[i][j][k] != -1) {  // 该状态之前算过
                return f[i][j][k];  // 直接返回记忆化结果
            }  // 记忆化查询结束

            int res = grid[i][j];  // 先计入当前格子的分数
            int nk = k;  // 进入当前格子后的剩余花费额度
            if (grid[i][j] > 0) {  // 当前格子值大于 0，需要花费 1 点
                --nk;  // 消耗一个花费额度
            }  // 额度扣减结束

            int a = dfs(i - 1, j, nk);  // 从上边一格过来的最大分数
            int b = dfs(i, j - 1, nk);  // 从左边一格过来的最大分数
            res += max(a, b);  // 接上更优的那条前缀路径

            return f[i][j][k] = res;  // 写入记忆化数组并返回
        };  // lambda 定义结束

        int ans = dfs(m - 1, n - 1, k);  // 从右下角开始反推整条路径的最大分数
        return ans < 0 ? -1 : ans;  // 答案为负说明不存在合法路径，返回 -1
    }  // 方法结束
};  // 类定义结束
