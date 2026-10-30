// 题目：762. 二进制表示中质数个计算置位（Prime Number of Set Bits in Binary Representation）
// 思路：预先列出范围内可能出现的质数，枚举 [left, right] 求每个数二进制 1 的个数再判断是否在集合中。
// 时间复杂度：O(n log C)，n 为区间长度，每个数求 popcount；空间复杂度：O(1)，质数集合与计数器为常数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countPrimeSetBits(int left, int right) {  // 统计 [left, right] 内二进制 1 的个数为质数的整数个数
        unordered_set<int> primes{2, 3, 5, 7, 11, 13, 17, 19};  // 预存可能的置位数质数（20 位以内 1 的个数最多为 20）
        int ans = 0;  // 计数器：满足条件的整数个数
        for (int i = left; i <= right; ++i) {  // 枚举闭区间内每个整数
            ans += primes.count(__builtin_popcount(i));  // GCC 内建函数求二进制 1 的个数，命中质数集合则累加 1
        }
        return ans;  // 返回答案
    }
};
