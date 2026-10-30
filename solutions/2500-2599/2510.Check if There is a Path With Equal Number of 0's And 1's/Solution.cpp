// 题目：2510. 检查是否有路径经过相同数量的 0 和 1（Check if There is a Path With Equal Number of 0's And 1's）
// 思路：路径长度固定为 m+n-1 个格子，为奇数时必然无解；否则记一半为 s，记忆化深搜每个格子的「已累计 1 的个数」，超过 s 或 0 超过 s 就剪枝，到终点时 1 的个数恰为 s 即成功。
// 时间复杂度：O(m * n * (m + n))，状态数为格子数乘累计 1 的个数；空间复杂度：O(m * n * (m + n))，记忆化数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isThereAPath(vector<vector<int>>& grid) {  // grid：只含 0 和 1 的矩阵，判断是否存在 0 与 1 数量相等的路径
        int m = grid.size(), n = grid[0].size();  // m 为行数，n 为列数
        int s = m + n - 1;  // 从左上角到右下角路径上的格子总数
        if (s & 1) return false;  // 格子数为奇数时无法平分 0 与 1，直接无解
        int f[m][n][s];  // 记忆化数组：f[i][j][k] 表示在 (i,j) 且已累计 k 个 1 时能否走通，-1 表示未访问
        s >>= 1;  // s 变为路径上应当出现的 1 的个数（格子总数的一半）
        memset(f, -1, sizeof f);  // 把记忆化数组全部置为 -1，表示都还没搜索过
        function<bool(int, int, int)> dfs = [&](int i, int j, int k) -> bool {  // 记忆化深搜的 lambda，按引用捕获外部变量
            if (i >= m || j >= n) return false;  // 越界说明这条走法非法
            k += grid[i][j];  // 进入当前格子，把它累加到 1 的计数上
            if (f[i][j][k] != -1) return f[i][j][k];  // 该状态已经搜过，直接复用缓存结果
            if (k > s || i + j + 1 - k > s) return false;  // 1 或 0 的个数已超过一半，后续无法再平衡，剪枝
            if (i == m - 1 && j == n - 1) return k == s;  // 到达终点：1 恰为一半即成功（0 自然也恰为一半）
            f[i][j][k] = dfs(i + 1, j, k) || dfs(i, j + 1, k);  // 向下或向右任一方向能走通即可，并把结果记入缓存
            return f[i][j][k];  // 返回该状态的结果
        };
        return dfs(0, 0, 0);  // 从左上角出发，初始已累计 1 的个数为 0
    }
};