// 题目：576. 出界的路径数（Out of Boundary Paths）
// 核心思路：记忆化 DFS，f[i][j][k] 表示从 (i,j) 出发、还剩 k 步时走出边界的方案数，四方向转移并取模。
// 时间复杂度：O(m * n * maxMove)，每个状态只算一次；空间复杂度：O(m * n * maxMove) 的记忆化数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {  // m 行 n 列，最多走 maxMove 步，起点为 (startRow, startColumn)
        int f[m][n][maxMove + 1];  // 记忆化数组：f[i][j][k] 表示从 (i,j) 走 k 步出界的方案数
        memset(f, -1, sizeof(f));  // 把数组全部置为 -1，表示该状态还没被计算过
        const int mod = 1e9 + 7;  // 答案需要对 1e9+7 取模
        const int dirs[5] = {-1, 0, 1, 0, -1};  // 四个方向的增量对：相邻两项组成 (行增量, 列增量)
        auto dfs = [&](this auto&& dfs, int i, int j, int k) -> int {  // C++23 递归 lambda：this auto&& 让 lambda 内部能调用自己
            if (i < 0 || i >= m || j < 0 || j >= n) {  // 当前位置已越界
                return k >= 0;  // 越界即这一步成功出界（此时 k 一定 >= 0），计为 1 条路径
            }  // 越界判断结束
            if (k <= 0) {  // 还没出界但步数已用完
                return 0;  // 无法再走，方案数为 0
            }  // 步数判断结束
            if (f[i][j][k] != -1) {  // 该状态之前算过
                return f[i][j][k];  // 直接返回缓存值，避免重复计算
            }  // 缓存判断结束
            int ans = 0;  // 累计从 (i,j,k) 出发的出界方案数
            for (int d = 0; d < 4; ++d) {  // 依次尝试上下左右四个方向
                int x = i + dirs[d], y = j + dirs[d + 1];  // 沿当前方向走一步后的新坐标
                ans = (ans + dfs(x, y, k - 1)) % mod;  // 递归子问题并累加，同时取模防溢出
            }  // 四方向枚举结束
            return f[i][j][k] = ans;  // 记忆化后返回当前状态的答案
        };  // lambda 定义结束
        return dfs(startRow, startColumn, maxMove);  // 从起点、剩余 maxMove 步开始求解
    }  // findPaths 结束
};  // 类定义结束
