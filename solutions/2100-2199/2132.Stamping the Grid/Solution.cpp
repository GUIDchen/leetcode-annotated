// 题目：2132. 用邮票贴满网格图（Stamping the Grid）
// 思路：先用二维前缀和判断每个「邮票大小」的子矩阵是否全为空格，再用二维差分标记这些位置都被邮票覆盖，最后前缀和还原并检查空格是否被贴满。
// 时间复杂度：O(m * n)，网格每个位置常数次操作；空间复杂度：O(m * n)，前缀和数组与差分数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) {  // grid 是 0/1 网格，stampHeight/stampWidth 是邮票的高与宽
        int m = grid.size(), n = grid[0].size();  // m 行、n 列
        vector<vector<int>> s(m + 1, vector<int>(n + 1));  // 二维前缀和数组，下标从 1 开始，多留一行一列哨兵
        for (int i = 1; i <= m; ++i) {  // 逐行构建前缀和
            for (int j = 1; j <= n; ++j) {  // 逐列构建前缀和
                s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + grid[i - 1][j - 1];  // 容斥原理求以 (i,j) 结尾的前缀和
            }
        }

        vector<vector<int>> d(m + 2, vector<int>(n + 2));  // 二维差分数组，四周各多留一圈以便越界标记
        for (int i = 1; i + stampHeight - 1 <= m; ++i) {  // 枚举邮票左上角的行，保证下边界不越界
            for (int j = 1; j + stampWidth - 1 <= n; ++j) {  // 枚举邮票左上角的列，保证右边界不越界
                int x = i + stampHeight - 1, y = j + stampWidth - 1;  // (x, y) 是邮票右下角坐标
                if (s[x][y] - s[x][j - 1] - s[i - 1][y] + s[i - 1][j - 1] == 0) {  // 前缀和查这个子矩阵是否全为空格
                    d[i][j]++;  // 差分标记：子矩阵左上角 +1
                    d[i][y + 1]--;  // 差分标记：右侧一列 -1
                    d[x + 1][j]--;  // 差分标记：下方一行 -1
                    d[x + 1][y + 1]++;  // 差分标记：右下角再 +1 抵消重复扣除
                }
            }
        }

        for (int i = 1; i <= m; ++i) {  // 遍历每一行还原差分
            for (int j = 1; j <= n; ++j) {  // 遍历每一列还原差分
                d[i][j] += d[i - 1][j] + d[i][j - 1] - d[i - 1][j - 1];  // 二维前缀和把差分还原成被覆盖次数
                if (grid[i - 1][j - 1] == 0 && d[i][j] == 0) {  // 空格子却没有任何邮票覆盖，说明贴不满
                    return false;  // 直接返回不可行
                }
            }
        }
        return true;  // 所有空格子都被覆盖，返回可行
    }
};
