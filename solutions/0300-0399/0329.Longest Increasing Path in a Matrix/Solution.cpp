// 题目：329. 矩阵中的最长递增路径（Longest Increasing Path in a Matrix）
// 思路：记忆化 DFS；f[i][j] 表示以 (i,j) 为起点的最长递增路径，向四个方向找严格更大的格子取最大值再加一，每个格子只算一次。
// 时间复杂度：O(m*n)，每个格子只被计算一次；空间复杂度：O(m*n)，记忆化数组加上递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestIncreasingPath(vector<vector<int>>& matrix) {  // matrix：二维矩阵，返回其中最长的严格递增路径长度
        int m = matrix.size(), n = matrix[0].size();  // 行列数：m 行、n 列
        int f[m][n];  // 记忆化数组，f[i][j] 存以 (i,j) 为起点的最长递增路径长度（变长数组，size 由运行时决定）
        memset(f, 0, sizeof(f));  // 全部清零，0 用来表示「还没计算过」
        int ans = 0;  // 保存全局最大路径长度
        int dirs[5] = {-1, 0, 1, 0, -1};  // 5 个元素表示四个方向向量：(dirs[k], dirs[k+1])，k 取 0..3 即上下左右

        function<int(int, int)> dfs = [&](int i, int j) -> int {  // 用 std::function 包一层递归 lambda；[&] 按引用捕获外部变量
            if (f[i][j]) {  // 命中缓存就直接返回，避免同一个格子重复搜索
                return f[i][j];  // 返回已经算好的结果
            }  // if 分支结束
            for (int k = 0; k < 4; ++k) {  // 枚举四个方向
                int x = i + dirs[k], y = j + dirs[k + 1];  // 相邻格子的坐标
                if (x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] > matrix[i][j]) {  // 越界检查 + 下一个格子的值必须严格更大才能走过去
                    f[i][j] = max(f[i][j], dfs(x, y));  // 用子问题结果更新当前格子的「最长后继长度」
                }  // if 分支结束
            }  // 方向循环结束
            return ++f[i][j];  // 先自增再返回：+1 表示把自己也算进路径长度，此后该值即被缓存
        };  // lambda 定义结束

        for (int i = 0; i < m; ++i) {  // 逐行遍历每个格子
            for (int j = 0; j < n; ++j) {  // 逐列遍历每个格子
                ans = max(ans, dfs(i, j));  // 以每个格子为起点算最长路径，更新全局答案
            }  // 列循环结束
        }  // 行循环结束
        return ans;  // 返回最长递增路径长度
    }  // 方法结束
};  // 类结束