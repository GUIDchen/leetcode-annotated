// 题目：840. 矩阵中的幻方（Magic Squares In Grid）
// 思路：枚举每个 3×3 子矩阵，检查数字是否恰为 1..9 且互不重复、两条对角线和相等、三行三列之和都与之相等；满足即是 3 阶幻方。
// 时间复杂度：O(m·n)，每个位置只检查常数大小的 3×3 子矩阵；空间复杂度：O(1)，只用到若干个长度 3 与 16 的数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numMagicSquaresInside(vector<vector<int>>& grid) {  // grid 是 m×n 矩阵，返回其中 3×3 幻方的个数
        int m = grid.size();  // 矩阵行数
        int n = grid[0].size();  // 矩阵列数
        int ans = 0;  // 计数器，统计幻方的个数
        auto check = [&](int i, int j) {  // 局部 lambda：判断以 (i,j) 为左上角的 3×3 子矩阵是否为幻方，是返回 1，否则 0
            if (i + 3 > m || j + 3 > n) {  // 子矩阵越出矩阵边界
                return 0;  // 直接判定不是幻方
            }  // if 结束
            vector<int> cnt(16);  // 值域为 1..9，cnt[v] 统计数字 v 在子矩阵中出现的次数
            vector<int> row(3);  // 三行各自的和
            vector<int> col(3);  // 三列各自的和
            int a = 0, b = 0;  // a 是主对角线之和，b 是副对角线之和
            for (int x = i; x < i + 3; ++x) {  // 遍历子矩阵的行
                for (int y = j; y < j + 3; ++y) {  // 遍历子矩阵的列
                    int v = grid[x][y];  // 当前格子的值
                    if (v < 1 || v > 9 || ++cnt[v] > 1) {  // 必须落在 1..9，且加入后不能重复出现（先自增再判 >1）
                        return 0;  // 违反任一条件，该子矩阵不是幻方
                    }  // if 结束
                    row[x - i] += v;  // 累加到所在行（x-i 是子矩阵内的行号）
                    col[y - j] += v;  // 累加到所在列（y-j 是子矩阵内的列号）
                    if (x - i == y - j) {  // 相对行号等于相对列号，落在主对角线上
                        a += v;  // 累加主对角线之和
                    }  // if 结束
                    if (x - i + y - j == 2) {  // 相对行号与相对列号之和为 2，落在副对角线上
                        b += v;  // 累加副对角线之和
                    }  // if 结束
                }  // 列循环结束
            }  // 行循环结束
            if (a != b) {  // 两条对角线和必须相等
                return 0;  // 不相等说明不是幻方
            }  // if 结束
            for (int k = 0; k < 3; ++k) {  // 逐行逐列检查
                if (row[k] != a || col[k] != a) {  // 每行、每列之和都必须等于对角线和
                    return 0;  // 不满足说明不是幻方
                }  // if 结束
            }  // for 结束
            return 1;  // 全部条件满足，是幻方
        };  // lambda 定义结束
        for (int i = 0; i < m; ++i) {  // 枚举 3×3 子矩阵的左上角行
            for (int j = 0; j < n; ++j) {  // 枚举 3×3 子矩阵的左上角列
                ans += check(i, j);  // 是幻方就计数加一（check 返回 0 或 1）
            }  // 列循环结束
        }  // 行循环结束
        return ans;  // 返回幻方个数
    }  // 方法结束
};