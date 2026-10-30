// 3869. 统计区间内奇妙数的数目 / Count Fancy Numbers in a Range
// 核心思路：区间计数转为前缀差 count(r) - count(l-1)，用数位 DP 同时枚举数位与数位和；状态 st 记录单调性（0 前导零 / 1 严格增 / 2 严格减 / 3 已破坏），数位本身单调即好数，否则再判断数位和是否为好数。
// 复杂度：时间复杂度 O(位数 × 数位和 × 10 × 4)（记忆化状态数），空间复杂度 O(位数 × 数位和 × 10 × 4)。
class Solution {  // LeetCode 题解类
public:  // 公有成员
    long long countFancy(long long l, long long r) {  // 返回闭区间 [l, r] 内奇妙数的个数
        auto check = [&](int s) -> bool {  // 判断数位和 s 本身是否为好数
            if (s < 100) {  // 一位数或两位数
                return s % 11 != 0;  // 一位数恒为好数；两位数两数码不同（严格增或严格减）等价于不是 11 的倍数
            }  // 下面处理三位数数位和（本题只会是 100..135）
            int mid = (s / 10) % 10;  // 取十位数字，即中间位
            int last = s % 10;  // 取个位数字，即最后一位
            return mid > 1 && mid < last;  // 百位恒为 1，严格递增即 1 < 十位 < 个位；三位数不存在严格递减的好数
        };  // check 定义结束

        string num = to_string(l - 1);  // 取上界 l-1 的十进制字符串
        int n = num.size();  // 上界的位数
        vector f(n, vector(9 * n + 1, vector(10, vector<long long>(4, -1))));  // 记忆化表 f[pos][数位和][前一位][状态]，-1 表示未计算

        auto dfs = [&](this auto&& dfs, int pos, int s, int prev, int st, bool lim) -> long long {  // 数位 DP：位次、数位和、前一位、单调性状态、是否贴上限
            if (pos >= n) {  // 所有数位都已填完
                if (st != 3) return 1;  // 数位严格单调（含只有一位的情形），本身即好数
                return check(s) ? 1LL : 0LL;  // 数位不单调，退化为判断数位和是否为好数
            }  // 递归边界结束

            if (!lim && f[pos][s][prev][st] != -1) {  // 不贴上限且该状态已算过
                return f[pos][s][prev][st];  // 直接复用记忆化结果
            }  // 记忆化命中结束

            int up = lim ? num[pos] - '0' : 9;  // 当前位可填的最大数字
            long long res = 0;  // 当前状态下的方案数

            for (int i = 0; i <= up; i++) {  // 枚举当前位填入的数字
                int nxtSt = st;  // 下一状态先继承当前状态

                if (st == 0) {  // 之前全是前导零
                    if (prev == 0)  // 前一位仍是前导零
                        nxtSt = 0;  // 继续保持前导零状态
                    else if (i > prev)  // 当前位比前一位大
                        nxtSt = 1;  // 转入严格递增状态
                    else if (i < prev)  // 当前位比前一位小
                        nxtSt = 2;  // 转入严格递减状态
                    else  // 与前一位相等
                        nxtSt = 3;  // 单调性被破坏
                } else if (st == 1) {  // 已处于严格递增状态
                    if (i > prev)  // 仍然严格递增
                        nxtSt = 1;  // 保持严格递增
                    else  // 不再递增
                        nxtSt = 3;  // 单调性被破坏
                } else if (st == 2) {  // 已处于严格递减状态
                    if (i < prev)  // 仍然严格递减
                        nxtSt = 2;  // 保持严格递减
                    else  // 不再递减
                        nxtSt = 3;  // 单调性被破坏
                } else {  // 状态已是 3
                    nxtSt = 3;  // 单调性已破坏，状态不再变化
                }  // 状态转移结束

                res += dfs(pos + 1, s + i, i, nxtSt, lim && i == up);  // 递归下一位并累加方案数
            }  // 当前位的枚举结束

            if (!lim) {  // 只在不贴上限时记忆
                f[pos][s][prev][st] = res;  // 写入记忆化表
            }  // 记忆化写入结束

            return res;  // 返回当前状态的方案数
        };  // dfs 定义结束

        long long a = dfs(0, 0, 0, 0, true);  // 统计 [0, l-1] 内的奇妙数个数

        num = to_string(r);  // 换成上界 r 的字符串
        n = num.size();  // 位数可能改变，同步更新
        f.assign(n, vector(9 * n + 1, vector(10, vector<long long>(4, -1))));  // 按新位数重建记忆化表

        long long b = dfs(0, 0, 0, 0, true);  // 统计 [0, r] 内的奇妙数个数

        return b - a;  // 前缀计数相减得到 [l, r] 的答案
    }  // 方法结束
};  // 类结束
