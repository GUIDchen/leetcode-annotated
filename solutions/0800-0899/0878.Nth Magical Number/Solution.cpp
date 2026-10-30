// 题目：878. 第 N 个神奇数字（Nth Magical Number）
// 核心思路：二分答案，用容斥原理 ⌊x/a⌋ + ⌊x/b⌋ - ⌊x/lcm(a,b)⌋ 统计不超过 x 的神奇数个数，找第一个个数达到 n 的 x。
// 时间复杂度：O(log((a + b) * n))，二分次数为对数级；空间复杂度：O(1)，只用常数个变量。
using ll = long long;  // 给长整型起别名，二分上界与中间值都可能超出 int 范围

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    const int mod = 1e9 + 7;  // 题目要求的取模常量

    int nthMagicalNumber(int n, int a, int b) {  // n：要求的第几个；a、b：两个正整数，神奇数是能被 a 或 b 整除的数
        int c = lcm(a, b);  // 最小公倍数，用于容斥去重（同时是 a 和 b 的倍数会被数两次）
        ll l = 0, r = 1ll * (a + b) * n;  // 二分区间：答案必小于 (a + b) * n，用 long long 防止乘法溢出
        while (l < r) {  // 二分查找最小的 x，使不超过 x 的神奇数个数达到 n
            ll mid = l + r >> 1;  // 取中点；加号优先级高于移位，所以等价于 (l + r) / 2
            if (mid / a + mid / b - mid / c >= n)  // 容斥原理：被 a 或 b 整除的个数等于两个整除个数之和减去被最小公倍数整除的个数
                r = mid;  // 个数已达到 n，答案可能就是 mid，向左收缩并保留 mid
            else  // 个数不足 n，说明答案一定在 mid 右侧
                l = mid + 1;  // 下界右移一位，丢弃 mid
        }  // 二分结束，l 就是第 n 个神奇数
        return l % mod;  // 按题目要求取模后返回
    }  // nthMagicalNumber 结束
};  // Solution 类结束