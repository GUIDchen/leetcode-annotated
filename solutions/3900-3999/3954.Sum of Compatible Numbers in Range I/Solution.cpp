// 题目：3954. 区间内的兼容数字之和 I（Sum of Compatible Numbers in Range I）
// 思路：在 [max(1, n-k), n+k] 内逐个枚举 x，若 n & x == 0（二进制上没有重叠的 1）就说明兼容，把 x 累加到答案。
// 复杂度：时间 O(k)，空间 O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int sumOfGoodIntegers(int n, int k) {  // n 是基准数，k 是允许的差值范围
        int ans = 0;  // ans 累加所有兼容数字之和
        int start = max(1, n - k);  // 左端点至少取 1，避免出现非正数
        int end = n + k;  // 右端点为 n + k
        for (int x = start; x <= end; ++x) {  // 闭区间枚举每一个候选数 x
            if ((n & x) == 0) {  // 按位与为 0 表示二进制上没有重叠的 1，即两者兼容
                ans += x;  // 兼容就把它加到答案里
            }
        }
        return ans;  // 返回区间内所有兼容数字之和
    }
};