// 题目：793. 阶乘函数后 K 个零（Preimage Size of Factorial Zeroes Function）
// 思路：记 f(n) 为 n! 末尾零的个数，记 g(k) 为使 f(n) >= k 的最小 n；末尾零恰为 k 的 n 是区间 [g(k), g(k+1))，答案即 g(k+1)-g(k)。f 单调不减，所以用二分求 g。
// 时间复杂度：O(log²k)，二分 O(log k) 次、每次 f 花 O(log n)；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int preimageSizeFZF(int k) {  // k：希望 n! 末尾恰好有 k 个零
        return g(k + 1) - g(k);  // 前缀计数之差：f(n) = k 的 n 落在 [g(k), g(k+1)) 这一段
    }  // preimageSizeFZF 结束

    int g(int k) {  // g(k)：使 f(n) >= k 的最小 n，即满足条件的最小下标
        long long left = 0, right = 1ll * 5 * k;  // 二分上下界：n 的上界取 5k，因为 f(5k) = k + k/5 + ... >= k 必然成立
        while (left < right) {  // 标准二分：不断收缩到第一个 f(mid) >= k 的位置
            long long mid = (left + right) >> 1;  // 取中点，右移一位等价于整除 2
            if (f(mid) >= k) {  // mid 的阶乘零数已达标，答案在左半区间（含 mid）
                right = mid;  // 收缩右边界，保留 mid
            } else {  // 零数还不够，答案一定在 mid 右侧
                left = mid + 1;  // 左边界越过 mid
            }  // 分支结束
        }  // 二分结束，此时 left 就是答案
        return (int) left;  // 转回 int 返回最小 n
    }  // g 结束

    int f(long x) {  // f(x)：x! 末尾零的个数，等于 1..x 中因子 5 的总数
        int res = 0;  // 累计因子 5 的个数
        while (x) {  // 反复整除 5，直到 x 变成 0
            x /= 5;  // 先除以 5，得到 floor(x/5) 这一层的贡献
            res += x;  // 累加 x/5 + x/25 + x/125 + ...
        }  // 循环结束
        return res;  // 返回末尾零的个数
    }  // f 结束
};  // 类定义结束