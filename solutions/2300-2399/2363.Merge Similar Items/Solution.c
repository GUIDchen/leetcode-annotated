// 题目：2363. 合并相似的物品（Merge Similar Items）
// 思路：价值范围只有 1..1000，用长度 1001 的计数数组按下标累加权重，最后按下标升序输出非零项。
// 时间复杂度：O(n + m + 1000)，近似线性；空间复杂度：O(1000)，是常数级额外空间。
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** mergeSimilarItems(int** items1, int items1Size, int* items1ColSize, int** items2, int items2Size,  // 入参是两组「价值, 权重」二元组，ColSize 数组表示每行 2 列
    int* items2ColSize, int* returnSize, int** returnColumnSizes) {  // returnSize 输出行数，returnColumnSizes 输出每行的列数
    int count[1001] = {0};  // 计数数组：下标是价值，元素是累计权重，初始化全为 0
    for (int i = 0; i < items1Size; i++) {  // 遍历第一个物品数组
        count[items1[i][0]] += items1[i][1];  // 把该物品的权重累加到对应价值的下标上
    }
    for (int i = 0; i < items2Size; i++) {  // 遍历第二个物品数组
        count[items2[i][0]] += items2[i][1];  // 相同价值的权重继续累加，实现两个数组的合并
    }
    int** ans = malloc(sizeof(int*) * (items1Size + items2Size));  // 结果行数不超过两数组长度之和，按上界分配行指针数组
    *returnColumnSizes = malloc(sizeof(int) * (items1Size + items2Size));  // 每行固定 2 列，按同一上界分配列数数组
    int size = 0;  // 记录已经写入的结果行数
    for (int i = 0; i < 1001; i++) {  // 按价值从小到大扫描，天然满足题目要求的升序
        if (count[i]) {  // 权重非 0，说明该价值在两个数组中至少出现过一次
            ans[size] = malloc(sizeof(int) * 2);  // 为该行分配 2 个 int 的空间
            ans[size][0] = i;  // 第 0 列写价值
            ans[size][1] = count[i];  // 第 1 列写合并后的权重
            (*returnColumnSizes)[size] = 2;  // 告诉判题器这一行有 2 列
            size++;  // 行数自增，准备写下一行
        }
    }
    *returnSize = size;  // 通过指针返回最终行数
    return ans;  // 返回二维结果数组，由判题器负责 free
}