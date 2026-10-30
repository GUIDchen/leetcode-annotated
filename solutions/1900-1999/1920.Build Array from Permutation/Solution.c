// 题目：1920. 基于排列构建数组（Build Array from Permutation）
// 思路：按下标直接映射 ans[i] = nums[nums[i]]，一次线性扫描；结果数组按题目要求用 malloc 分配并交给调用方释放。
// 时间复杂度：O(n)；空间复杂度：O(n)，为返回的结果数组（题目要求必须分配）。
// 下面三行是 LeetCode 题面带过来的提示注释：返回数组必须 malloc，判题器假定它可被 free
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* buildArray(int* nums, int numsSize, int* returnSize) {  // nums 是 0~n-1 的排列；returnSize 用于输出返回数组的长度
    int* ans = malloc(sizeof(int) * numsSize);  // 为结果数组申请 numsSize 个 int 的空间（判题环境已提供 malloc 声明）
    for (int i = 0; i < numsSize; i++) {  // 逐位构造答案
        ans[i] = nums[nums[i]];  // 按题意取 nums[i] 处的值；nums 是排列，下标一定合法
    }  // 结束遍历
    *returnSize = numsSize;  // 告诉调用方结果数组的长度
    return ans;  // 返回新数组，所有权交给调用方
}  // 函数结束