// 题目：2455. 可被三整除的偶数的平均值（Average Value of Even Numbers That Are Divisible by Three）
// 思路：既被 2 整除又被 3 整除等价于被 6 整除，故一次遍历筛选出 %6==0 的数，边累加边计数，最后求平均。
// 时间复杂度：O(n)，只需扫描数组一遍；空间复杂度：O(1)，只用到两个计数变量。
int averageValue(int* nums, int numsSize) {  // nums：输入数组指针；numsSize：数组长度；返回满足条件的数的平均值
    int s = 0, n = 0;  // s 保存满足条件的数之和，n 保存满足条件的数的个数
    for (int i = 0; i < numsSize; ++i) {  // 从前往后枚举每个下标
        if (nums[i] % 6 == 0) {  // 能被 6 整除 ⇔ 同时是 3 的倍数且是偶数，正是题目要求的数
            s += nums[i];  // 把这个数累加到总和里
            ++n;  // 满足条件的个数增加 1
        }
    }
    return n == 0 ? 0 : s / n;  // 一个都没有时按题意返回 0；否则整数除法即向下取整，得到平均值
}