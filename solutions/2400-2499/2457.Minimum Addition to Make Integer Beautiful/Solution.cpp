// 题目：2457. 美丽整数的最小增量（Minimum Addition to Make Integer Beautiful）
// 思路：先判断 n 的数位和是否已 ≤ target；否则每次把「最低非零位」清零并向高位进一，得到下一个候选数，
// 这种取整方式跳过了所有中间值（中间值的数位和只会更大），循环到数位和满足要求时的增量即最小。
// 时间复杂度：O(log n) 级别的迭代次数，每次线性求数位和；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long makeIntegerBeautiful(long long n, int target) {  // n：初始整数；target：允许的数位和上限；返回最小增量
        using ll = long long;  // 类型别名，后续书写更短
        auto f = [](ll x) {  // lambda：计算十进制各位数字之和
            int y = 0;  // 累计数位和，初值为 0
            while (x) {  // 只要 x 还不为 0 就继续取位
                y += x % 10;  // 取出最低位数字并累加
                x /= 10;  // 去掉最低位，准备处理下一位
            }
            return y;  // 返回求得的数位和
        };

        ll x = 0;  // 需要增加的最小量，从 0（即不动）开始试探
        while (f(n + x) > target) {  // 当前候选数的数位和仍超过 target，说明还需要继续进位取整
            ll y = n + x;  // 当前候选数
            ll p = 10;  // 进位后最低位的权重，初始为 10（进到十位）
            while (y % 10 == 0) {  // 末位是 0 的位加 1 不会改变数位和，可以直接跳过
                y /= 10;  // 去掉末位 0
                p *= 10;  // 权重同步扩大 10 倍
            }
            x = (y / 10 + 1) * p - n;  // 把当前最低非零位清零、向更高一位进一，得到下一个候选数的增量
        }
        return x;  // 此时的 x 就是使数位和 ≤ target 的最小增量
    }
};