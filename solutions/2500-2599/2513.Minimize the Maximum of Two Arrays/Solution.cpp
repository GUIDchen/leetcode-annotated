// 题目：2513. 最小化两个数组中的最大值（Minimize the Maximum of Two Arrays）
// 思路：可行性关于上界 x 单调（x 可行则更大也可行），于是二分答案；用整除计数分别算出 [1,x] 中不能被 d1 整除、不能被 d2 整除、以及两者都不能整除的数字个数来判定可行性。
// 时间复杂度：O(log 1e10)，约 34 次二分；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimizeSet(int divisor1, int divisor2, int uniqueCnt1, int uniqueCnt2) {  // 两个约数分别约束两个数组，uniqueCnt 是各数组需要的互异元素个数
        long left = 1, right = 1e10;  // 二分区间 [1, 1e10]，上界取题目允许的最大值
        long divisor = lcm((long) divisor1, (long) divisor2);  // 两约数的最小公倍数，用于数出同时被两者整除的个数
        while (left < right) {  // 二分寻找最小的可行上界
            long mid = (left + right) >> 1;  // 取中点，右移一位等价于除以 2
            long cnt1 = mid / divisor1 * (divisor1 - 1) + mid % divisor1;  // [1, mid] 中不能被 divisor1 整除的个数：每 d1 个里留 d1-1 个，再加上不完整的一段
            long cnt2 = mid / divisor2 * (divisor2 - 1) + mid % divisor2;  // [1, mid] 中不能被 divisor2 整除的个数
            long cnt = mid / divisor * (divisor - 1) + mid % divisor;  // [1, mid] 中两个约数都不能整除的个数，这些数才能同时分给两个数组
            if (cnt1 >= uniqueCnt1 && cnt2 >= uniqueCnt2 && cnt >= uniqueCnt1 + uniqueCnt2) {  // 三个条件都成立说明 mid 足够大
                right = mid;  // 可行则把上界收窄到 mid
            } else {  // mid 太小，凑不出足够的数
                left = mid + 1;  // 抬高下界
            }
        }
        return left;  // 二分收敛时 left 就是最小可行上界
    }
};