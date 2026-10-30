// 题目：2319. 判断矩阵是否是一个 X 矩阵（Check if Matrix Is X-Matrix）
// 核心思路：遍历每个格子，主对角线（i==j）与副对角线（i+j==n-1）上的元素必须非 0，其余位置的元素必须为 0，任一处不满足即返回 false。
// 时间复杂度：O(n²)，需要检查全部 n² 个格子；空间复杂度：O(1)，只用循环变量。
bool checkXMatrix(int** grid, int gridSize, int* gridColSize) {  // grid：n×n 矩阵；gridSize 为边长；返回该矩阵是否为 X 矩阵
    for (int i = 0; i < gridSize; i++) {  // 逐行扫描
        for (int j = 0; j < gridSize; j++) {  // 逐列扫描，此时 (i, j) 就是当前格子的坐标
            if (i == j || i + j == gridSize - 1) {  // 当前格子位于主对角线（i==j）或副对角线（i+j==n-1）上
                if (grid[i][j] == 0) {  // 对角线上的元素不允许为 0
                    return false;  // 出现 0 说明不是 X 矩阵，立即判负
                }  // 内层 if 结束
            } else if (grid[i][j] != 0) {  // 非对角线上的元素必须为 0
                return false;  // 非对角线出现非 0 值，立即判负
            }  // if-else 分支结束
        }  // 列循环结束
    }  // 行循环结束
    return true;  // 所有格子都满足要求，确认为 X 矩阵
}  // 函数结束