// 题目：1572. 矩阵对角线元素的和（Matrix Diagonal Sum）
// 思路：一次遍历每一行，同时累加主对角线元素 mat[i][i] 与副对角线元素 mat[i][n-1-i]；中心格子在奇数阶时会被重复计算，需要跳过。
// 时间复杂度：O(n)，n 为矩阵阶数，只遍历 n 行；空间复杂度：O(1)，只用常数个额外变量。
int diagonalSum(int** mat, int matSize, int* matColSize) {  // mat：n×n 矩阵；matSize：行数；matColSize：每行长度（本题用不到）
    int ans = 0;  // 累加两条对角线元素之和
    for (int i = 0; i < matSize; ++i) {  // 逐行处理，i 同时是主对角线的列下标
        ans += mat[i][i];  // 累加主对角线上的元素
        int j = matSize - i - 1;  // 副对角线在第 i 行上的列下标
        if (j != i) {  // 当阶数为奇数时中心格子会被两条对角线共用
            ans += mat[i][j];  // 只有不重合时才累加副对角线元素，避免重复计入
        }
    }
    return ans;  // 返回两条对角线上元素的总和
}
