// 题目：1895. 最大的幻方（Largest Magic Square）
// 思路：先做行、列方向的前缀和，使任意子方阵的每行和、每列和都能 O(1) 求出；再从大到小枚举边长 k 与左上角，用 check 校验所有行和、列和以及两条对角线和是否都等于同一值。
// 时间复杂度：O(mn·min(m,n))，枚举边长与位置约 mn·min(m,n) 次、每次校验 O(min(m,n))；空间复杂度：O(mn)，两份前缀和数组。
class Solution {  // LeetCode 约定的题解类
public:  // 成员变量与成员函数对外可见
    vector<vector<int>> rowsum;  // 行方向前缀和：rowsum[i][j] 表示 grid 第 i-1 行前 j 个元素之和
    vector<vector<int>> colsum;  // 列方向前缀和：colsum[i][j] 表示 grid 第 j-1 列前 i 个元素之和
  // 空行：分隔成员变量与成员函数
    int largestMagicSquare(vector<vector<int>>& grid) {  // grid：输入的整数矩阵，返回内部最大的幻方边长
        int m = grid.size(), n = grid[0].size();  // 矩阵的行数 m 与列数 n
        rowsum.assign(m + 1, vector<int>(n + 1, 0));  // 分配 (m+1) x (n+1) 的表，多出的一行一列让递推不必特判边界
        colsum.assign(m + 1, vector<int>(n + 1, 0));  // 列前缀和同样分配 (m+1) x (n+1)，统一按 1 作起始下标
        for (int i = 1; i <= m; ++i) {  // 逐行建立前缀和（i 从 1 开始对应 grid 的第 i-1 行）
            for (int j = 1; j <= n; ++j) {  // 逐列建立前缀和（j 从 1 开始对应 grid 的第 j-1 列）
                rowsum[i][j] = rowsum[i][j - 1] + grid[i - 1][j - 1];  // 本行前缀 = 本行前一列前缀 + 当前格子，得到行内累计和
                colsum[i][j] = colsum[i - 1][j] + grid[i - 1][j - 1];  // 本列前缀 = 上一行同列前缀 + 当前格子，得到列内累计和
            }  // 结束列循环
        }  // 结束行循环
        for (int k = min(m, n); k > 1; --k) {  // 幻方边长不超过 min(m, n)，从大到小枚举，首个满足的 k 就是答案
            for (int i = 0; i + k - 1 < m; ++i) {  // 枚举子方阵左上角的行下标 i
                for (int j = 0; j + k - 1 < n; ++j) {  // 枚举子方阵左上角的列下标 j
                    int i2 = i + k - 1, j2 = j + k - 1;  // 算出右下角坐标 (i2, j2)：k 固定时它就是左上角加 k-1
                    if (check(grid, i, j, i2, j2)) {  // 校验这个 k x k 子方阵是否为幻方
                        return k;  // 是幻方则直接返回当前边长（从大到小枚举保证最大）
                    }  // 结束校验判断
                }  // 结束列枚举
            }  // 结束行枚举
        }  // 结束边长枚举
        return 1;  // 边长 1 的方阵按定义总是幻方，作为兜底答案
    }  // 方法结束
  // 空行：分隔主流程与判定函数
    bool check(vector<vector<int>>& grid, int x1, int y1, int x2, int y2) {  // check：判断以 (x1,y1) 为左上、(x2,y2) 为右下的子方阵所有行、列、对角线和是否相等
        int val = rowsum[x1 + 1][y2 + 1] - rowsum[x1 + 1][y1];  // 以第一行的行和为基准值 val（行前缀和相减得到该行区间和）
        for (int i = x1 + 1; i <= x2; ++i) {  // 从第二行开始逐行比对行和
            if (rowsum[i + 1][y2 + 1] - rowsum[i + 1][y1] != val) {  // 行和不等于基准值，立即判定不是幻方
                return false;  // 返回 false
            }  // 结束行内判断
        }  // 结束逐行比对
        for (int j = y1; j <= y2; ++j) {  // 逐列比对列和（列前缀和相减得到该列区间和）
            if (colsum[x2 + 1][j + 1] - colsum[x1][j + 1] != val) {  // 列和不等于基准值，立即判定不是幻方
                return false;  // 返回 false
            }  // 结束列内判断
        }  // 结束逐列比对
        int s = 0;  // s 用于累计主对角线之和
        for (int i = x1, j = y1; i <= x2; ++i, ++j) {  // 沿主对角线从左上走到右下，i、j 同步自增
            s += grid[i][j];  // 累加对角线元素
        }  // 结束主对角线遍历
        if (s != val) {  // 主对角线和也必须等于基准值
            return false;  // 返回 false
        }  // 结束主对角线判断
        s = 0;  // 清零 s，准备统计副对角线
        for (int i = x1, j = y2; i <= x2; ++i, --j) {  // 沿副对角线从右上走到左下，i 自增、j 自减
            s += grid[i][j];  // 累加副对角线元素
        }  // 结束副对角线遍历
        if (s != val) {  // 副对角线和也必须等于基准值
            return false;  // 返回 false
        }  // 结束副对角线判断
        return true;  // 行列与两条对角线全部相等，确认是幻方
    }  // 方法结束
};  // 类定义结束
