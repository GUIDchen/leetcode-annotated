// 题目：2553. 分割数组中数字的数位（Separate the Digits in an Array）
// 思路：两遍扫描——第一遍统计所有数字的总位数并分配结果数组，第二遍从后往前把每个数字从低位到高位填入，保证数位顺序与原数字一致。
// 时间复杂度：O(总位数)，每个数位只被数一次、写一次；空间复杂度：O(总位数)，即返回数组占用的内存（不计输出则为 O(1)）。
// 题面提示：返回数组需要由本题解用 malloc 分配，调用者会负责 free()，所以下面必须动态申请内存
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* separateDigits(int* nums, int numsSize, int* returnSize) {  // nums 是输入数组，numsSize 是数组长度；*returnSize 用来回传结果数组的长度
    int n = 0;  // n 统计把所有数字拆成数位后的总个数，也就是结果数组的长度
    for (int i = 0; i < numsSize; i++) {  // 第一遍遍历：只统计位数总数，暂时不写结果
        int t = nums[i];  // 用临时变量 t 保存当前数字，避免改动原数组
        while (t != 0) {  // 每除一次 10 就少一位，直到 t 变成 0
            t /= 10;  // 丢掉 t 的最低位
            n++;  // 丢掉一位说明原数有一位，总数加一
        }  // while 结束
    }  // 第一遍遍历结束，n 就是答案所需长度
    int* ans = malloc(sizeof(int) * n);  // 按总位数分配结果数组
    for (int i = numsSize - 1, j = n - 1; i >= 0; i--) {  // 第二遍遍历：从后往前填，因为从最低位取出的数位要放到数组末尾
        int t = nums[i];  // 再次用临时变量取出当前数字
        while (t != 0) {  // 反复取最低位，直到 t 归零
            ans[j--] = t % 10;  // t % 10 就是当前最低位，写入位置 j，然后 j 左移一位
            t /= 10;  // 去掉刚取出的最低位，准备取下一位
        }  // while 结束
    }  // 第二遍遍历结束，所有数位已按原顺序填好
    *returnSize = n;  // 通过指针回传结果数组长度，调用者据此遍历
    return ans;  // 返回动态分配的结果数组
}  // separateDigits 函数结束