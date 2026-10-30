// 题目：2529. 正整数和负整数的最大计数（Maximum Count of Positive Integer and Negative Integer）
// 核心思路：一次遍历同时统计正整数个数 a 与负整数个数 b，元素 0 不计入任何一方，最后取二者较大值。
// 时间复杂度：O(n)，只需扫描一遍数组；空间复杂度：O(1)，只用了常数个计数器。
#define max(a, b) (a > b ? a : b)  // 宏函数：返回两个数中的较大者，供末尾比较使用

int maximumCount(int* nums, int numsSize) {  // nums 是升序数组，numsSize 是长度，返回正数个数与负数个数的较大值
    int a = 0, b = 0;  // a 统计正整数个数，b 统计负整数个数，都从 0 开始
    for (int i = 0; i < numsSize; ++i) {  // 从头到尾遍历数组中的每个元素
        if (nums[i] > 0) {  // 当前元素是正整数
            ++a;  // 正整数计数器加一
        } else if (nums[i] < 0) {  // 当前元素是负整数
            ++b;  // 负整数计数器加一
        }  // 元素为 0 时两个分支都不进入，符合题意
    }  // 扫描结束，a、b 就是两类数字的个数
    return max(a, b);  // 返回两者中的较大值即为答案
}  // 函数结束