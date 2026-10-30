// 题目：1139. 最大的以 1 为边界的正方形（Largest 1-Bordered Square）
// 思路：预处理每个格子向右、向下的连续 1 长度，再从大到小枚举边长 k，用四个方向的连续长度判断四条边是否全为 1。
// 时间复杂度：O(m*n*min(m,n))，枚举所有边长与左上角；空间复杂度：O(m*n)，两个方向数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int largest1BorderedSquare(vector<vector<int>>& grid) {  // grid 是 0/1 矩阵，返回边界全为 1 的最大正方形面积
        int m = grid.size(), n = grid[0].size();  // m 行 n 列
        int down[m][n];  // down[i][j] 表示从 (i,j) 向下连续 1 的个数（变长数组，clang 扩展支持）
        int right[m][n];  // right[i][j] 表示从 (i,j) 向右连续 1 的个数
        memset(down, 0, sizeof down);  // 先清零，值为 0 的格子保持 0 即可
        memset(right, 0, sizeof right);  // 同上，清零 right 表
        for (int i = m - 1; i >= 0; --i) {  // 从右下角往左上角递推，保证右方和下方的值已经算好
            for (int j = n - 1; j >= 0; --j) {  // 同一行内也从右往左扫
                if (grid[i][j] == 1) {  // 只有当前格是 1 才需要计算连续长度
                    down[i][j] = i + 1 < m ? down[i + 1][j] + 1 : 1;  // 下方还有行就接上下方格子的值再加 1，否则到底了只算自己这 1 个
                    right[i][j] = j + 1 < n ? right[i][j + 1] + 1 : 1;  // 右方还有列就接上右方格子的值再加 1，否则到边界只算 1 个
                }  // 判断结束
            }  // 列循环结束
        }  // 行循环结束
        for (int k = min(m, n); k > 0; --k) {  // 边长从最大可能值 min(m,n) 开始递减，第一个可行的就是答案
            for (int i = 0; i <= m - k; ++i) {  // 枚举正方形左上角的行（不能越界，所以上界是 m-k）
                for (int j = 0; j <= n - k; ++j) {  // 枚举正方形左上角的列（上界是 n-k）
                    if (down[i][j] >= k && right[i][j] >= k && right[i + k - 1][j] >= k  // 左上角向下、向右都要够 k 个 1，分别对应左边和上边
                        && down[i][j + k - 1] >= k) {  // 下边看左下角向右的连续长度，右边看右上角向下的连续长度
                        return k * k;  // 四条边全部满足，找到了边长为 k 的 1 边界正方形，返回面积
                    }  // 判断结束
                }  // 列枚举结束
            }  // 行枚举结束
        }  // 边长枚举结束
        return 0;  // 矩阵里没有任何 1，按定义返回 0
    }  // 方法结束
};  // 类定义结束