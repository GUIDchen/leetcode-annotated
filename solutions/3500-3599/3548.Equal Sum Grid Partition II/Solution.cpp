// 题目：3548. 等和矩阵分割 II（Equal Sum Grid Partition II）
// 思路：先按行切分，用两个哈希表记录上下两侧的取值频次，靠两侧差值判断能否删掉一个格子；再把矩阵转置重复同样的逻辑，以覆盖按列切分。
// 时间复杂度：O(m * n)，check 与转置各遍历一次矩阵；空间复杂度：O(m * n)，哈希表最多保存矩阵中所有不同的取值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canPartitionGrid(vector<vector<int>>& grid) {  // grid：m 行 n 列的整数矩阵
        return check(grid) || check(rotate(grid));  // 先尝试水平切割，再转置后尝试垂直切割
    }

private:  // 以下为内部辅助函数
    bool check(const vector<vector<int>>& g) {  // 只考虑水平切割：允许在上方块中去掉至多一个格子
        int m = g.size(), n = g[0].size();  // m：行数；n：列数
        long long s1 = 0, s2 = 0;  // s1：上方部分的和；s2：下方部分的和

        unordered_map<long long, int> cnt1, cnt2;  // cnt1 / cnt2 分别统计上方 / 下方各取值的出现次数

        for (auto& row : g) {  // 初始时整张表都属于下方
            for (int x : row) {  // 遍历该行元素
                s2 += x;  // 累加下方和
                cnt2[x]++;  // 下方该取值的计数加一
            }
        }

        for (int i = 0; i < m - 1; i++) {  // 枚举行切割线：第 0~i 行归上方，并保证下方至少剩一行
            for (int x : g[i]) {  // 把第 i 行整行从下方搬到上方
                s1 += x;  // 上方和增加
                s2 -= x;  // 下方和减少
                cnt1[x]++;  // 上方该取值的计数加一
                cnt2[x]--;  // 下方该取值的计数减一
            }

            if (s1 == s2) return true;  // 两侧已经相等，不需要再删格子

            if (s1 < s2) {  // 上方偏小，只能从下方删掉一个值等于差值的格子
                long long diff = s2 - s1;  // 需要补上的差值
                if (cnt2[diff] > 0) {  // 下方确实存在值等于 diff 的格子
                    if (
                        (m - i - 1 > 1 && n > 1) || (i == m - 2 && (g[i + 1][0] == diff || g[i + 1][n - 1] == diff)) || (n == 1 && (g[i + 1][0] == diff || g[m - 1][0] == diff))) return true;  // 删掉该格子后下方被切走的部分仍非空且不割裂
                }
            } else {  // 下方偏小，只能从上方删掉一个值等于差值的格子
                long long diff = s1 - s2;  // 需要补上的差值
                if (cnt1[diff] > 0) {  // 上方确实存在值等于 diff 的格子
                    if (
                        (i + 1 > 1 && n > 1) || (i == 0 && (g[0][0] == diff || g[0][n - 1] == diff)) || (n == 1 && (g[0][0] == diff || g[i][0] == diff))) return true;  // 删掉该格子后上方剩余部分仍非空且不割裂
                }
            }
        }

        return false;  // 所有切割线都无法通过删掉一个格子配平
    }

    vector<vector<int>> rotate(vector<vector<int>>& grid) {  // 把矩阵转置，使按列切分变成按行切分
        int m = grid.size(), n = grid[0].size();  // m：原行数；n：原列数
        vector<vector<int>> t(n, vector<int>(m));  // 转置后的矩阵是 n 行 m 列
        for (int i = 0; i < m; i++) {  // 遍历原矩阵的每一行
            for (int j = 0; j < n; j++) {  // 遍历该行的每一列
                t[j][i] = grid[i][j];  // 行列下标互换，完成转置
            }
        }
        return t;  // 返回转置后的矩阵
    }
};
