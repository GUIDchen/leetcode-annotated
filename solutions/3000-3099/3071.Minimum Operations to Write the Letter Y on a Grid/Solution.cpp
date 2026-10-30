// 题目：3071. 在矩阵上写出字母 Y 所需的最少操作次数（Minimum Operations to Write the Letter Y on a Grid）
// 核心思路：先按「Y 的三条笔画」把格子分成 Y 区域与非 Y 区域，分别统计 0/1/2 的出现次数；再枚举两区域各自的目标颜色（必须不同），用「总数 - 已符合的格数」得到改动次数并取最小。
// 时间复杂度：O(n²)，一次遍历统计 n² 个格子，之后只有 9 种颜色组合；空间复杂度：O(1)，只用两个长度为 3 的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumOperationsToWriteY(vector<vector<int>>& grid) {  // grid：n×n 且只含 0、1、2 的矩阵；返回写出字母 Y 的最少操作次数
        int n = grid.size();  // 矩阵边长 n
        int cnt1[3]{};  // cnt1[c]：属于 Y 区域的格子中，值为 c 的个数
        int cnt2[3]{};  // cnt2[c]：不属于 Y 区域的格子中，值为 c 的个数
        for (int i = 0; i < n; ++i) {  // 枚举行下标 i
            for (int j = 0; j < n; ++j) {  // 枚举列下标 j，逐格判断是否落在字母 Y 上
                bool a = i == j && i <= n / 2;  // 笔画一：左上到中心的主对角线（i == j），且只取上半部分
                bool b = i + j == n - 1 && i <= n / 2;  // 笔画二：右上到中心的反对角线（i + j == n - 1），且只取上半部分
                bool c = j == n / 2 && i >= n / 2;  // 笔画三：从中心向下的竖线（j == n / 2），且只取下半部分；中心格被多条笔画重叠覆盖也只算一次
                if (a || b || c) {  // 命中任一笔画即为 Y 区域
                    ++cnt1[grid[i][j]];  // Y 区域中当前颜色的计数加一
                } else {  // else：该格不属于字母 Y
                    ++cnt2[grid[i][j]];  // 非 Y 区域中当前颜色的计数加一
                }
            }
        }
        int ans = n * n;  // 答案上界取 n*n，即最坏情况整张表都要改
        for (int i = 0; i < 3; ++i) {  // 枚举 Y 区域最终统一成的颜色 i
            for (int j = 0; j < 3; ++j) {  // 枚举 Y 以外区域最终统一成的颜色 j
                if (i != j) {  // 两区域颜色必须不同，题目要求 Y 与背景颜色相异
                    ans = min(ans, n * n - cnt1[i] - cnt2[j]);  // 不动代价 = 总格数 - 已符合 i 的 Y 格数 - 已符合 j 的非 Y 格数，取最小值
                }
            }
        }
        return ans;  // 返回最少操作次数
    }
};