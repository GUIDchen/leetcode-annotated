// 题目：3128. 直角三角形（Right Triangles）
// 思路：先统计每行、每列中 1 的个数；再把每个 1 当作直角顶点，它与同行的其它 1、同列的其它 1 各连一条边，方案数为 (行数-1)*(列数-1)。
// 时间复杂度：O(m * n)，两次遍历矩阵；空间复杂度：O(m + n)，保存行、列的 1 计数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long numberOfRightTriangles(vector<vector<int>>& grid) {  // 统计以 1 为直角顶点、两条直角边平行于坐标轴的三角形个数
        int m = grid.size(), n = grid[0].size();  // m 为行数，n 为列数
        vector<int> rows(m);  // rows[i]：第 i 行中 1 的个数
        vector<int> cols(n);  // cols[j]：第 j 列中 1 的个数
        for (int i = 0; i < m; ++i) {  // 第一次遍历：统计每行、每列中 1 的数量
            for (int j = 0; j < n; ++j) {  // 遍历当前行的每一列
                rows[i] += grid[i][j];  // 累加到所在行的计数
                cols[j] += grid[i][j];  // 累加到所在列的计数
            }  // 结束当前行的遍历
        }  // 结束第一次遍历
        long long ans = 0;  // 答案可能超过 int 范围，用 long long 保存
        for (int i = 0; i < m; ++i) {  // 第二次遍历：把每个 1 都当作直角顶点
            for (int j = 0; j < n; ++j) {  // 遍历当前行的每一列
                if (grid[i][j] == 1) {  // 只有值为 1 的格子才能做直角顶点
                    ans += (rows[i] - 1) * (cols[j] - 1);  // 同行其余 1 的个数 × 同列其余 1 的个数
                }  // 结束 if 判断
            }  // 结束列遍历
        }  // 结束行遍历
        return ans;  // 返回三角形总数
    }  // 结束 numberOfRightTriangles 方法
};  // 结束 Solution 类