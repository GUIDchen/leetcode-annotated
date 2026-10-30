// 题目：1470. 重新排列数组（Shuffle the Array）
// 核心思路：结果数组长度为 2n，第 i 对依次放 nums[i] 与 nums[i + n]。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(n)，新建长度为 2n 的返回数组。
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* shuffle(int* nums, int numsSize, int n, int* returnSize) {  // nums 长度为 2n，n 为每半段的长度；*returnSize 用来输出结果长度
    int* ans = (int*) malloc(sizeof(int) * n * 2);  // 按判题器要求用 malloc 分配 2n 个 int
    for (int i = 0; i < n; i++) {  // 遍历前半段的每个下标
        ans[2 * i] = nums[i];  // 每对的第一项来自数组前半段
        ans[2 * i + 1] = nums[i + n];  // 每对的第二项来自数组后半段
    }  // 循环体结束
    *returnSize = n * 2;  // 告诉调用方返回数组的长度
    return ans;  // 返回新数组，由调用方负责 free
}  // 函数结束
