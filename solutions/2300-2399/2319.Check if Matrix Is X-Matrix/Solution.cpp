// 题目：2319. 判断矩阵是否是一个 X 矩阵（Check if Matrix Is X-Matrix）
// 核心思路：逐格检查，两条对角线上的元素必须非 0，非对角线元素必须为 0，发现违例立刻返回 false。
// 时间复杂度：O(n²)，遍历整个矩阵；空间复杂度：O(1)，只用到下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkXMatrix(vector<vector<int>>& grid) {  // grid：n×n 矩阵；返回它是否是一个 X 矩阵
        int n = grid.size();  // 取出矩阵边长 n
        for (int i = 0; i < n; ++i) {  // 逐行扫描
            for (int j = 0; j < n; ++j) {  // 逐列扫描，(i, j) 为当前格子坐标
                if (i == j || i + j == n - 1) {  // 当前格子在主对角线（i==j）或副对角线（i+j==n-1）上
                    if (!grid[i][j]) {  // 对角线上的元素不能为 0
                        return false;  // 为 0 则不满足条件，立即返回 false
                    }  // 内层 if 结束
                } else if (grid[i][j]) {  // 非对角线上的元素必须为 0，非 0 即为违例
                    return false;  // 非对角线出现非 0 值，立即返回 false
                }  // if-else 分支结束
            }  // 列循环结束
        }  // 行循环结束
        return true;  // 全部格子都符合要求，返回 true
    }  // checkXMatrix 结束
};  // 类定义结束