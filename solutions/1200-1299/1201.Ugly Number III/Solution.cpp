// 题目：1201. 丑数 III（Ugly Number III）
// 思路：二分答案——用容斥原理统计 ≤ mid 的丑数个数，找到第一个个数 ≥ n 的位置。
// 时间复杂度：O(log 2e9)，二分约 31 轮；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int nthUglyNumber(int n, int a, int b, int c) {  // n 是目标序号，a、b、c 是三个除数，返回第 n 个丑数
        long long ab = lcm(a, b);  // ab 是 a 与 b 的最小公倍数，用于容斥去重
        long long bc = lcm(b, c);  // bc 是 b 与 c 的最小公倍数
        long long ac = lcm(a, c);  // ac 是 a 与 c 的最小公倍数
        long long abc = lcm(ab, c);  // abc 是三者共同的最小公倍数
        long long l = 1, r = 2000000000;  // 二分区间：左端 1，右端取 2e9 足以覆盖 n ≤ 1e9 的情况
        while (l < r) {  // 二分：找第一个满足「丑数个数 ≥ n」的 mid
            long long mid = (l + r) >> 1;  // 取中点，右移一位等价于除以 2
            if (mid / a + mid / b + mid / c - mid / ab - mid / bc - mid / ac + mid / abc >= n) {  // 容斥原理：三个集合相加、两两交集相减、三者交集加回；个数 ≥ n 说明 mid 足够大
                r = mid;  // 答案在左半区间，把右端收缩到 mid
            } else {  // 否则 mid 还不够
                l = mid + 1;  // 答案在右半区间，排除 mid
            }
        }
        return l;  // l == r，这个位置就是第 n 个丑数
    }

    long long lcm(long long a, long long b) {  // 求最小公倍数：两数之积除以最大公约数
        return a * b / gcd(a, b);  // a * b 用 long long 保存，避免 int 溢出
    }

    long long gcd(long long a, long long b) {  // 辗转相除法求最大公约数
        return b == 0 ? a : gcd(b, a % b);  // b 为 0 时 a 即答案，否则递归处理 b 与 a % b
    }
};