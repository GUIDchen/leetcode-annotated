// 题目：2749. 得到整数零需要执行的最少操作数（Minimum Operations to Make the Integer Zero）
// 思路：设做 k 次操作，剩余 num1 - k*num2 要由 k 个 2 的幂之和凑出；可行性等价于 popcount(x) ≤ k ≤ x，从小到大枚举 k。
// 时间复杂度：O(log(num1))，k 只需枚举到 num1；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 公有成员：判题器直接调用下面的方法
    int makeTheIntegerZero(int num1, int num2) {  // num1：初始整数；num2：每次操作额外减去的固定值；返回最少操作次数
        using ll = long long;  // 用 long long 防止 k * num2 过程中溢出
        for (ll k = 1;; ++k) {  // 从小到大枚举操作次数 k，第一个可行的 k 即为最小答案
            ll x = num1 - k * num2;  // k 次操作一共减去 k*num2，剩下的 num1-k*num2 必须由 k 个 2 的幂之和凑出
            if (x < 0) {  // 剩余值为负，再增大 k 只会更负，后面都不可能成立
                break;  // 提前结束枚举
            }  // 结束“剩余值为负”分支
            if (__builtin_popcountll(x) <= k && k <= x) {  // 二进制中 1 的个数是凑出 x 所需的最少 2 的幂个数，需 ≤ k；k ≤ x 保证每项至少为 1
                return k;  // 找到最小可行操作次数，直接返回
            }  // 结束可行性判断
        }  // 结束枚举循环
        return -1;  // 没有任何 k 可行，按题目要求返回 -1
    }  // 结束题解方法
// 结束题解类
};