// 题目：483. 最小好进制（Smallest Good Base）
// 思路：若 num 在 k 进制下全为 1 且有 len 位，则 num = 1 + k + ... + k^(len-1)。位数 len 越大进制 k 越小，因此从 len = 63 递减到 2，对每个 len 二分求出 k，第一个命中的就是最小好进制。
// 时间复杂度：O(log²num)，外层最多 62 个长度，每个长度二分 O(log num) 次、每次求和 O(log num)；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的题解方法
    string smallestGoodBase(string n) {  // n 是十进制字符串形式的目标值，返回最小好进制的字符串形式
        long long num = stoll(n);  // 转成 64 位整数（题面保证 n ≤ 10^18，long long 足够）
        for (int len = 63; len >= 2; --len) {  // 枚举“全 1”表示的位数 len，从大到小试
            long long radix = getRadix(len, num);  // 在该位数下二分求进制
            if (radix != -1) {  // 找到满足条件的进制
                return to_string(radix);  // 位数最多时进制最小，第一次命中的就是答案
            }  // 结束 if
        }  // 结束 len 的枚举
        return to_string(num - 1);  // 兜底：num 用两位全 1 表示时进制是 num - 1，一定成立
    }  // 结束题解方法

    long long getRadix(int len, long long num) {  // len：全 1 的位数；num：目标值；不存在时返回 -1
        long long l = 2, r = num - 1;  // 进制下界为 2，上界为 num - 1（k > num - 1 时连两位都凑不出 num）
        while (l < r) {  // 二分查找最小的 radix 使得 calc(radix, len) >= num
            long long mid = (l + r) >> 1;  // 取中点（用右移一位代替除以 2）
            if (calc(mid, len) >= num) {  // 当前进制的值已经不小于 num
                r = mid;  // 答案在左半区间（含 mid）
            } else {  // 否则
                l = mid + 1;  // 说明 mid 太小，答案在右半区间
            }  // 结束 if-else 分支
        }  // 循环结束时 l == r，是第一个使值 >= num 的位置
        return calc(r, len) == num ? r : -1;  // 必须恰好等于 num 才是合法进制，否则返回 -1 表示该位数无解
    }  // 结束 getRadix

    long long calc(long long radix, int len) {  // 计算 1 + radix + ... + radix^(len-1)
        long long p = 1, sum = 0;  // p 是当前的幂 radix^i，sum 是累加和
        for (int i = 0; i < len; ++i) {  // 一共累加 len 项
            if (LLONG_MAX - sum < p) {  // 加上 p 会溢出 long long 时提前截断
                return LLONG_MAX;  // 返回 LLONG_MAX 当作“无穷大”，保证上面二分仍能正确比较
            }  // 结束 if
            sum += p;  // 累加当前幂
            if (LLONG_MAX / p < radix) {  // 下一次乘 radix 若会溢出，就饱和处理
                p = LLONG_MAX;  // 饱和成 LLONG_MAX，避免有符号整数溢出
            } else {  // 否则
                p *= radix;  // 正常乘上进制，得到下一项
            }  // 结束 if-else 分支
        }  // 结束 for 循环
        return sum;  // 返回等比级数的和
    }  // 结束 calc
};  // 结束题解类
