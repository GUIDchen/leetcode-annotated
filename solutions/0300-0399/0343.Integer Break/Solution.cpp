// 题目：343. 整数拆分（Integer Break）
// 思路：动态规划，f[i] 表示 i 拆分后的最大乘积；枚举第一部分 j，在「继续拆 i-j」与「不拆 i-j」之间取较大者。
// 时间复杂度：O(n^2)，两层循环枚举拆分点；空间复杂度：O(n)，dp 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int integerBreak(int n) {  // n：要拆分的正整数（n >= 2）；返回拆分后各因子乘积的最大值
        vector<int> f(n + 1);  // vector 默认初始化为 0，下标 1..n 可用
        f[1] = 1;  // 边界：1 不能再拆，令 f[1] = 1 以支撑递推
        for (int i = 2; i <= n; ++i) {  // 自小到大依次计算 f[2] 到 f[n]
            for (int j = 1; j < i; ++j) {  // 枚举第一部分 j，把 i 拆成 j 与 i-j
                f[i] = max({f[i], f[i - j] * j, (i - j) * j});  // 三者取最大：已有的 f[i]、继续拆 i-j 的 f[i-j]*j、不拆 i-j 的 (i-j)*j
            }  // 内层枚举结束
        }  // 外层枚举结束
        return f[n];  // 返回整数 n 的最大乘积
    }  // 方法体结束
};  // 类定义结束