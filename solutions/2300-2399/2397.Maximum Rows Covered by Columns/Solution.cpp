// 题目：2397. 被列覆盖的最多行数（Maximum Rows Covered by Columns）
// 思路：把每行的 1 压缩成位掩码，再枚举所有恰好选中 numSelect 列的列掩码，统计被完全覆盖的行数并取最大值。
// 时间复杂度：O(2^n * m)，枚举 2^n 个列掩码、每个掩码检查 m 行；空间复杂度：O(m)，保存每行的位掩码。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumRows(vector<vector<int>>& matrix, int numSelect) {  // matrix：0/1 矩阵；numSelect：必须选择的列数
        int m = matrix.size(), n = matrix[0].size();  // m 为行数，n 为列数
        int rows[m];  // 位掩码数组：rows[i] 的第 j 位表示第 i 行第 j 列是否为 1
        memset(rows, 0, sizeof(rows));  // 把掩码数组清零，避免残留脏数据
        for (int i = 0; i < m; ++i) {  // 逐行扫描
            for (int j = 0; j < n; ++j) {  // 逐列扫描
                if (matrix[i][j]) {  // 该位置的值是 1
                    rows[i] |= 1 << j;  // 把第 j 位置为 1，表示这一行需要第 j 列被选中才能被覆盖
                }
            }
        }
        int ans = 0;  // 记录被完全覆盖的最多行数
        for (int mask = 1; mask < 1 << n; ++mask) {  // 枚举所有非空的列选择方案，mask 的第 j 位为 1 表示选中第 j 列
            if (__builtin_popcount(mask) != numSelect) {  // 选中的列数必须正好等于 numSelect
                continue;  // 列数不符，跳过这个方案
            }
            int t = 0;  // 当前方案下被完全覆盖的行数
            for (int x : rows) {  // 逐行检查
                t += (x & mask) == x;  // 行掩码是列掩码的子集时 (x & mask) == x，说明该行的 1 全被覆盖
            }
            ans = max(ans, t);  // 用当前方案的行数更新最大值
        }
        return ans;  // 返回最多能被覆盖的行数
    }
};