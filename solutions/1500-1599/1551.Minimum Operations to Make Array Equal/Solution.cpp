// 题目：1551. 使数组中所有元素相等的最小操作数（Minimum Operations to Make Array Equal）
// 思路：数组为 1,3,5,...,2n-1，每次操作让一对元素同时向中间靠 1，总和不变所以目标值就是平均值 n；
// 时间复杂度：O(n)，枚举左半部分 n/2 个元素；空间复杂度：O(1)，只用若干整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(int n) {  // n：数组长度（数组为前 n 个奇数）
        int ans = 0;  // ans：累计的最小操作次数
        for (int i = 0; i < n >> 1; ++i) {  // 只需看小于平均值 n 的左半部分（共 n/2 个元素）
            ans += n - (i << 1 | 1);  // 第 i 个元素是 2i+1，它要补齐到平均值 n，需要 n-(2i+1) 次操作
        }
        return ans;  // 返回左半部分补齐所需的总操作次数
    }
};