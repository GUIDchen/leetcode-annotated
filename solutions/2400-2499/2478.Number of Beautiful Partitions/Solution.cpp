// 题目：2478. 完美分割的方案数（Number of Beautiful Partitions）
// 思路：把字符串切成 k 段，每段长度至少 minLength 且以质数数字(2/3/5/7)开头、以非质数数字结尾；f[i][j] 表示前 i 个字符切成 j 段且第 j 段结束在 i 的方案数，g[i][j] 是同一 j 下 f 的前缀和，转移时用 g 一次取到所有合法前一段终点的方案总数。
// 时间复杂度：O(n·k)，i 与 j 两层循环；空间复杂度：O(n·k)，两个 (n+1)×(k+1) 的 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int beautifulPartitions(string s, int k, int minLength) {  // s：原字符串；k：要切成的段数；minLength：每段的最小长度；返回方案数
        int n = s.size();  // 字符串长度，后面所有下标都以它为上界
        auto prime = [](char c) {  // 小工具 lambda：判断字符 c 是否是质数数字(2/3/5/7)
            return c == '2' || c == '3' || c == '5' || c == '7';  // 是 2、3、5、7 之一就返回 true，说明它能作为一段的开头
        };  // lambda 定义结束
        if (!prime(s[0]) || prime(s[n - 1])) return 0;  // 首字符必须是质数数字、末字符必须不是质数数字，否则一段都切不出来，直接返回 0
        vector<vector<int>> f(n + 1, vector<int>(k + 1));  // f[i][j]：前 i 个字符恰好切成 j 段、且第 j 段结束在位置 i 的方案数
        vector<vector<int>> g(n + 1, vector<int>(k + 1));  // g[i][j]：f[0][j]+f[1][j]+...+f[i][j]，即第 j 段结束位置不超过 i 的方案数前缀和
        f[0][0] = g[0][0] = 1;  // 边界：长度为 0 的前缀切成 0 段有 1 种方案（空方案），前缀和同样为 1
        const int mod = 1e9 + 7;  // 取模常量，防止方案数溢出
        for (int i = 1; i <= n; ++i) {  // i 枚举前 i 个字符，也就是当前这一段的结束位置（1-based 长度）
            if (i >= minLength && !prime(s[i - 1]) && (i == n || prime(s[i]))) {  // 位置 i 能作为段尾的条件：长度够 minLength、第 i 个字符不是质数数字、且不是末尾时下一个字符必须是质数数字（下一段的开头）
                for (int j = 1; j <= k; ++j) {  // j 枚举已经切出的段数
                    f[i][j] = g[i - minLength][j - 1];  // 前一段最多结束在 i-minLength，用前缀和一次性累加所有合法前一段终点的方案数
                }  // 结束段数枚举
            }  // 结束「位置 i 能否作段尾」的判断
            for (int j = 0; j <= k; ++j) {  // 无论 i 能否作段尾，都要把 f[i][j] 并进前缀和 g
                g[i][j] = (g[i - 1][j] + f[i][j]) % mod;  // 前缀和递推：g[i][j] = g[i-1][j] + f[i][j]，并即时取模
            }  // 结束前缀和更新循环
        }  // 结束 i 的枚举
        return f[n][k];  // 答案：整个字符串恰好切成 k 段的方案数
    }  // 结束题解方法
};  // 结束题解类