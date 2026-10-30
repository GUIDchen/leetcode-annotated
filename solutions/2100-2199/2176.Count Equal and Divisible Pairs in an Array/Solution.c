// 题目：2176. 统计数组中相等且可以被整除的数对（Count Equal and Divisible Pairs in an Array）
// 思路：直接枚举所有满足 0 <= i < j < n 的下标对，同时检查 nums[i] == nums[j] 与 (i*j) % k == 0。
// 时间复杂度：O(n^2)，双重循环枚举数对；空间复杂度：O(1)，只用了一个计数器。
int countPairs(int* nums, int numsSize, int k) {  // nums：输入数组；numsSize：元素个数；k：整除条件里的除数；返回满足条件的数对个数
    int ans = 0;  // ans 统计答案，初值为 0
    for (int j = 1; j < numsSize; ++j) {  // 外层枚举数对中较大的下标 j，从 1 开始保证前面至少有 i=0
        for (int i = 0; i < j; ++i) {  // 内层枚举较小的下标 i，范围 [0, j)，天然满足 i < j，避免重复计数
            ans += (nums[i] == nums[j] && (i * j % k) == 0);  // 逻辑与的结果为 0/1，两个条件同时成立时把答案加一：值相等，且下标乘积能被 k 整除
        }  // 内层循环结束
    }  // 外层循环结束
    return ans;  // 返回统计到的数对个数
}  // 函数结束（判题片段，不含 main 函数）
