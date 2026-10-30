// 题目：3704. 统计和为 N 的无零数对（Count No-Zero Pairs That Sum to N）
// 核心思路：按十进制位从低到高做数位 DP，状态为 (进位, A 是否还有位, B 是否还有位)；每一位上 A、B 各自可选 1..9 的任意数字（数字中不允许出现 0），或选 0 表示这个数到此结束；要求 da + db + 进位 的个位等于 N 的当前位，最高位处理完后要求无进位且两数都已结束。
// 复杂度：时间 O(log n)，位数 m 层、每层常数个状态与 10x10 的数字组合；空间 O(1)，只开两个 2x2x2 的滚动数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countNoZeroPairs(long long n) {  // 返回满足 a + b = n 且 a、b 的十进制表示都不含 0 的正整数对个数
        long long trivanople = n;  // 先把参数另存一份，后面按它的十进制写法逐位处理
        std::string s = std::to_string(trivanople);  // 转成十进制字符串，便于逐位取数
        int m = (int) s.size();  // N 的十进制位数
        std::vector<int> digits(m + 1);  // digits[i] 保存 N 的从低往高数第 i 位，多留一位给最高进位
        for (int i = 0; i < m; i++) {  // 从字符串低位到高位依次取数字
            digits[i] = s[m - 1 - i] - '0';  // 字符转数值，下标反转成从低位开始
        }  // 结束拆位
        digits[m] = 0;  // 最高位之后的目标数字视为 0，用来吸收最终进位

        long long dp[2][2][2] = {};  // dp[进位][A 是否还有位][B 是否还有位]，全部初始化为 0
        dp[0][1][1] = 1;  // 最低位开始前没有进位，A、B 都还在构造中，共 1 种

        for (int pos = 0; pos < m + 1; pos++) {  // 从低到高逐位处理，最后多处理一位用于吸收进位
            long long ndp[2][2][2] = {};  // 新一层 DP 数组先全部清零
            int target = digits[pos];  // 这一位要让 a、b 数字之和（含进位）的个位等于 target
            for (int carry = 0; carry <= 1; carry++) {  // 枚举进入这一位时的进位
                for (int aliveA = 0; aliveA <= 1; aliveA++) {  // 枚举 A 是否还有位待填
                    for (int aliveB = 0; aliveB <= 1; aliveB++) {  // 枚举 B 是否还有位待填
                        long long ways = dp[carry][aliveA][aliveB];  // 取出到达该状态的方案数
                        if (!ways) continue;  // 该状态不可达，直接跳过
                        int aDigits[10];  // 这一位 A 可以选的全部数字
                        int aNext[10];  // 与 aDigits 一一对应：选完这个数字后 A 是否还有位
                        int aLen = 0;  // A 的候选数字个数
                        if (aliveA) {  // A 还没结束，这一位必须继续填数
                            for (int d = 1; d <= 9; d++) {  // 无零数不能含 0，只能选 1..9
                                aDigits[aLen] = d;  // 记录候选数字 d
                                aNext[aLen] = 1;  // 填完这一位 A 仍然有效
                                aLen++;  // 候选个数加一
                            }  // 结束 1..9 的候选生成
                            if (pos > 0) {  // 除最低位外，允许用 0 来结束这个数
                                aDigits[aLen] = 0;  // 选 0 表示 A 到此为止
                                aNext[aLen] = 0;  // 之后 A 不再有效
                                aLen++;  // 候选个数加一
                            }  // 结束「结束 A」的候选生成
                        } else {  // A 已经结束，这一位只能补 0 占位
                            aDigits[0] = 0;  // 已结束的数高位补 0
                            aNext[0] = 0;  // 保持已结束状态
                            aLen = 1;  // 只有 1 个候选
                        }  // 结束 A 的候选生成

                        int bDigits[10];  // 这一位 B 可以选的全部数字
                        int bNext[10];  // 与 bDigits 一一对应：选完这个数字后 B 是否还有位
                        int bLen = 0;  // B 的候选数字个数
                        if (aliveB) {  // B 还没结束，这一位必须继续填数
                            for (int d = 1; d <= 9; d++) {  // 无零数不能含 0，只能选 1..9
                                bDigits[bLen] = d;  // 记录候选数字 d
                                bNext[bLen] = 1;  // 填完这一位 B 仍然有效
                                bLen++;  // 候选个数加一
                            }  // 结束 1..9 的候选生成
                            if (pos > 0) {  // 除最低位外，允许用 0 来结束这个数
                                bDigits[bLen] = 0;  // 选 0 表示 B 到此为止
                                bNext[bLen] = 0;  // 之后 B 不再有效
                                bLen++;  // 候选个数加一
                            }  // 结束「结束 B」的候选生成
                        } else {  // B 已经结束，这一位只能补 0 占位
                            bDigits[0] = 0;  // 已结束的数高位补 0
                            bNext[0] = 0;  // 保持已结束状态
                            bLen = 1;  // 只有 1 个候选
                        }  // 结束 B 的候选生成

                        for (int ia = 0; ia < aLen; ia++) {  // 枚举 A 在这一位的每一种选法
                            int da = aDigits[ia];  // A 这一位选的数字
                            int na = aNext[ia];  // 选完之后 A 是否还有位
                            for (int ib = 0; ib < bLen; ib++) {  // 枚举 B 在这一位的每一种选法
                                int db = bDigits[ib];  // B 这一位选的数字
                                int nb = bNext[ib];  // 选完之后 B 是否还有位
                                int sum = da + db + carry;  // 这一位两数之和再加上进位
                                if (sum % 10 != target) continue;  // 个位必须等于 N 的当前位，否则不合法
                                int ncarry = sum / 10;  // 向上产生的进位只能是 0 或 1
                                ndp[ncarry][na][nb] += ways;  // 把方案数累加到新状态
                            }  // 结束 B 的数字枚举
                        }  // 结束 A 的数字枚举
                    }  // 结束 aliveB 枚举
                }  // 结束 aliveA 枚举
            }  // 结束 carry 枚举
            std::memcpy(dp, ndp, sizeof(dp));  // 用新一层 DP 覆盖旧一层，进入下一位
        }  // 结束数位 DP

        return dp[0][0][0];  // 要求最终无进位且 A、B 都已结束，即为所求对数
    }  // 结束 countNoZeroPairs

    long long countPairs(long long n) {  // 与题面同名的入口方法
        return countNoZeroPairs(n);  // 直接复用数位 DP 的实现
    }  // 结束 countPairs
};  // 结束题解类
