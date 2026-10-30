// 题目：2482. 行和列中一和零的差值（Difference Between Ones and Zeros in Row and Column）
// 思路：先统计每行、每列的 1 的个数，再对每个格子用 ones(i)+ones(j)-zeros(i)-zeros(j) 计算差值，其中 zeros 由长度减 ones 得到。
// 时间复杂度：O(m·n)，两遍扫描矩阵；空间复杂度：O(m+n)，额外的行列计数数组（返回值本身不计入）。
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** onesMinusZeros(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {  // grid：m×n 的 0/1 矩阵；gridSize：行数；gridColSize：每行长度；返回差值矩阵，并回写行数与每行长度
    int* rows = malloc(sizeof(int) * gridSize);  // 每行 1 的个数，长度是行数
    int* cols = malloc(sizeof(int) * gridColSize[0]);  // 每列 1 的个数，长度是列数 gridColSize[0]
    memset(rows, 0, sizeof(int) * gridSize);  // 清零：memset 按字节置 0，对 int 而言恰好就是数值 0
    memset(cols, 0, sizeof(int) * gridColSize[0]);  // 同样把列计数清零
    for (int i = 0; i < gridSize; i++) {  // 遍历每一行
        for (int j = 0; j < gridColSize[0]; j++) {  // 遍历每一列
            if (grid[i][j]) {  // 只有该格子是 1 才需要累加计数
                rows[i]++;  // 第 i 行 1 的个数加一
                cols[j]++;  // 第 j 列 1 的个数加一
            }  // 结束 if
        }  // 结束列循环
    }  // 结束行循环，rows/cols 统计完成
    int** ans = malloc(sizeof(int*) * gridSize);  // 分配结果矩阵的行指针数组（gridSize 行）
    for (int i = 0; i < gridSize; i++) {  // 逐行构造结果
        ans[i] = malloc(sizeof(int) * gridColSize[0]);  // 为第 i 行分配整行空间
        for (int j = 0; j < gridColSize[0]; j++) {  // 逐列填值
            ans[i][j] = rows[i] + cols[j] - (gridSize - rows[i]) - (gridColSize[0] - cols[j]);  // 行、列的 1 的个数减去各自 0 的个数（zeros = 长度 - ones）
        }  // 结束列循环
    }  // 结束行循环
    *returnSize = gridSize;  // 输出行数
    *returnColumnSizes = gridColSize;  // 每行长度直接复用入参 gridColSize，按题意由调用方 free
    return ans;  // 返回结果矩阵
}  // 结束函数