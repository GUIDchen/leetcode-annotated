// 题目：3116. 单面值组合的第 K 小金额（Kth Smallest Amount With Single Denomination Combination）
// 思路：二分答案 mx，用容斥原理统计 [1, mx] 内能被至少一种面值整除的金额个数，个数达到 k 的最小 mx 即答案。
// 时间复杂度：O(2^m·m·log(1e11))，m 为面值个数，每次判定枚举全部子集；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long findKthSmallest(vector<int>& coins, int k) {  // coins：面值数组；k：要求的第 k 小金额
        using ll = long long;  // 用别名简化写法，金额可能超出 int 范围
        ll l = 1, r = 1e11;  // 二分区间：答案至少为 1，上界取 1e11 足以覆盖题目数据范围
        int n = coins.size();  // 面值个数

        auto check = [&](ll mx) {  // 闭包：判断不超过 mx 的合法金额是否至少有 k 个
            ll cnt = 0;  // 统计 [1, mx] 内能被至少一种面值整除的金额个数
            for (int i = 1; i < 1 << n; ++i) {  // 枚举所有非空子集，用容斥去重
                ll v = 1;  // 当前子集面值的最小公倍数
                for (int j = 0; j < n; ++j) {  // 逐位检查子集里包含哪些面值
                    if (i >> j & 1) {  // 第 j 个面值属于当前子集
                        v = lcm(v, coins[j]);  // 把该面值并入最小公倍数
                        if (v > mx) {  // 公倍数已超过 mx，后续倍数都不可能有贡献
                            break;  // 提前结束内层枚举，避免无用计算
                        }  // 结束当前面值判断
                    }  // 结束内层面值枚举
                }  // 结束子集枚举（内层）
                int m = __builtin_popcount(i);  // 子集大小决定容斥的符号
                if (m & 1) {  // 奇数个面值：加
                    cnt += mx / v;  // 不超过 mx 的 v 的倍数共有 mx / v 个
                } else {  // 偶数个面值：减
                    cnt -= mx / v;  // 容斥去掉重复计数的部分
                }  // 结束符号判断
            }  // 结束子集枚举（外层）
            return cnt >= k;  // 合法金额已够 k 个，说明答案不超过 mx
        };  // 闭包定义结束

        while (l < r) {  // 二分寻找最小的满足 check 的 mx
            ll mid = (l + r) >> 1;  // 取中点，用移位代替除法
            if (check(mid)) {  // mid 已够 k 个，答案可能更小
                r = mid;  // 把右边界收缩到 mid
            } else {  // 否则 mid 不够，答案一定更大
                l = mid + 1;  // 左边界推到 mid + 1
            }  // 结束判定分支
        }  // 结束二分循环
        return l;  // 收敛后 l 就是第 k 小的金额
    }  // 结束 findKthSmallest
};  // 类定义结束