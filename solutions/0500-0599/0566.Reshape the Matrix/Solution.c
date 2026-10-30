// 题目：566. 重塑矩阵（Reshape the Matrix）
// 思路：若元素总数 matSize×matColSize[0] 与 r×c 不等则原样返回；否则按行优先的一维下标 i 映射：新矩阵 (i/c, i%c)，原矩阵 (i/matColSize[0], i%matColSize[0])。
// 时间复杂度：O(m·n)，每个元素搬运一次；空间复杂度：O(r·c)，新建结果矩阵（C 版由调用者 free）。
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** matrixReshape(int** mat, int matSize, int* matColSize, int r, int c, int* returnSize, int** returnColumnSizes) {  // mat 是原二维矩阵，r、c 是新矩阵行列数，返回新矩阵并回填尺寸
    if (matSize * matColSize[0] != r * c) {  // 元素总数不一致时无法重塑，按题意返回原矩阵
        *returnSize = matSize;  // 返回行数等于原行数
        *returnColumnSizes = matColSize;  // 列大小数组直接复用原矩阵的，调用者仍会负责释放
        return mat;  // 原样返回原矩阵
    }  // 尺寸不匹配分支结束
    *returnSize = r;  // 返回行数等于新行数 r
    *returnColumnSizes = malloc(sizeof(int) * r);  // 为新的列大小数组分配 r 个 int，由调用者 free
    int** ans = malloc(sizeof(int*) * r);  // 为结果矩阵分配 r 个行指针
    for (int i = 0; i < r; i++) {  // 逐行分配列空间
        (*returnColumnSizes)[i] = c;  // 新矩阵每一行都有 c 列
        ans[i] = malloc(sizeof(int) * c);  // 为第 i 行分配 c 个 int
    }  // 行分配结束
    for (int i = 0; i < r * c; i++) {  // 按行优先的一维下标 i 搬运全部元素
        ans[i / c][i % c] = mat[i / matColSize[0]][i % matColSize[0]];  // 一维下标 i 映射到 ans 的 (i/c, i%c)，同时映射回 mat 的 (i/matColSize[0], i%matColSize[0])
    }  // 搬运循环结束
    return ans;  // 返回重塑后的矩阵
}