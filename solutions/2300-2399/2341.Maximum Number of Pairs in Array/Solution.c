// 题目：2341. 数组能形成多少数对（Maximum Number of Pairs in Array）
// 思路：值域是 0..100，用长度 101 的计数数组统计每个值的出现次数；每个值出现 c 次就能配出 c/2 对，落单个数就是总数减去已成对的元素数。
// 时间复杂度：O(n + 101) 即 O(n)；空间复杂度：O(101) 即 O(1)，另加返回数组的 O(1) 堆空间。
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* numberOfPairs(int* nums, int numsSize, int* returnSize) {  // 返回一个 2 元素数组：[能形成的数对数目, 剩余落单的数目]，数组须由本函数 malloc
    int count[101] = {0};  // 值域 0..100，用下标直接映射值，顺便完成清零
    for (int i = 0; i < numsSize; i++) {  // 第一遍：统计每个值的出现次数
        count[nums[i]]++;  // 值为 nums[i] 的出现次数加一
    }  // 统计结束
    int sum = 0;  // sum 累计能配成的数对总数
    for (int i = 0; i < 101; i++) {  // 第二遍：遍历整个值域
        sum += count[i] >> 1;  // 右移一位等于除以 2 向下取整，即该值能配成的对数
    }  // 配对统计结束
    int* ans = malloc(sizeof(int) * 2);  // 判题器不会替我们释放，返回数组必须用 malloc 申请
    ans[0] = sum;  // 第一个答案：数对数目
    ans[1] = numsSize - sum * 2;  // 第二个答案：总元素数减去已成对的元素，剩下的都是落单的
    *returnSize = 2;  // 通过出参告知调用方返回数组的长度
    return ans;  // 返回结果数组，由调用方负责 free
}  // 函数结束