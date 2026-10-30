// 题目：1929. 数组串联（Concatenation of Array）
// 思路：申请 2n 个 int 的空间，一趟循环把原数组元素同时写到前 n 位与后 n 位，即得 nums 与自身首尾相接的结果。
// 时间复杂度：O(n)，只扫一遍原数组；空间复杂度：O(n)，返回数组需要 2n 个 int。
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getConcatenation(int* nums, int numsSize, int* returnSize) {  // nums：原数组；numsSize：元素个数；returnSize：输出结果长度
    int* ans = malloc(sizeof(int) * numsSize * 2);  // 申请 2n 个 int 的堆空间存放串联结果
    for (int i = 0; i < numsSize; i++) {  // 逐个复制原数组元素
        ans[i] = ans[i + numsSize] = nums[i];  // 同时写两份：下标 i 与下标 i+n
    }
    *returnSize = numsSize * 2;  // 通过指针告诉调用者返回数组的长度
    return ans;  // 返回堆上分配的结果数组，由调用者负责释放
}