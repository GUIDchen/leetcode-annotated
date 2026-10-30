// 题目：1230. 抛掷硬币（Toss Strange Coins）
// 思路：二维概率 DP，f[i][j] 表示前 i 枚硬币中恰好 j 枚正面朝上的概率；第 i 枚为反面时乘 (1 - prob[i-1]) 继承 j，为正面时乘 prob[i-1] 由 j-1 转移而来。
// 时间复杂度：O(n × target)，两层循环；空间复杂度：O(n × target)，DP 表规模。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    double probabilityOfHeads(vector<double>& prob, int target) {  // prob[i]：第 i 枚硬币正面朝上的概率；target：要求正面朝上的硬币数，返回对应概率
        int n = prob.size();  // n：硬币总数
        double f[n + 1][target + 1];  // DP 表：f[i][j] = 前 i 枚硬币里恰好 j 枚正面的概率；两维都多留一格以免判边界
        memset(f, 0, sizeof(f));  // 整个表清零，后面只做加法累加，先置 0 才安全
        f[0][0] = 1;  // 初始化：0 枚硬币凑出 0 个正面的概率是 1（乘法单位元）
        for (int i = 1; i <= n; ++i) {  // 逐枚加入硬币，i 表示已经考虑前 i 枚
            for (int j = 0; j <= min(i, target); ++j) {  // j 枚举当前可能凑出的正面数，上限是 i 与 target 的较小值
                f[i][j] = (1 - prob[i - 1]) * f[i - 1][j];  // 第 i 枚是反面：乘 (1 - prob[i-1])，正面数不变，继承 f[i-1][j]
                if (j > 0) {  // j > 0 时才能讨论「第 i 枚是正面」这种转移
                    f[i][j] += prob[i - 1] * f[i - 1][j - 1];  // 第 i 枚是正面：乘 prob[i-1]，由「前 i-1 枚有 j-1 个正面」转移而来
                }  // 结束正面转移分支
            }  // 结束 j 的枚举
        }  // 结束 i 的枚举
        return f[n][target];  // 前 n 枚恰好 target 个正面的概率就是答案
    }  // 方法结束
};  // 类定义结束