// 题目：132. 分割回文串 II（Palindrome Partitioning II）
// 思路：区间 DP 预处理 g[i][j] 判断 s[i..j] 是否回文，再一次线性 DP：f[i] 为前缀 s[0..i] 的最少切分数，枚举最后一段回文。
// 时间复杂度：O(n^2)，两层预处理加两层切分 DP；空间复杂度：O(n^2)，回文表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minCut(string s) {  // 返回把 s 切成若干回文段所需的最少切刀数
        int n = s.size();  // n 是字符串长度
        bool g[n][n];  // 回文判定表：g[i][j] 为真表示 s[i..j] 是回文串
        memset(g, true, sizeof(g));  // 用 memset 把每字节置 1（非零即 true），先假定所有区间都回文，长度 0/1 的区间本来也成立
        for (int i = n - 1; ~i; --i) {  // 起点 i 从 n-1 递减到 0；~i 等价于 i >= 0，写法更紧凑
            for (int j = i + 1; j < n; ++j) {  // 终点 j 从 i+1 开始，长度小于 2 的区间已在初值中为真
                g[i][j] = s[i] == s[j] && g[i + 1][j - 1];  // 递推：首尾字符相同且去掉首尾仍是回文，则整段回文
            }
        }
        int f[n];  // f[i] 表示前缀 s[0..i] 切成全回文的最少切分数
        iota(f, f + n, 0);  // iota 把 f 填成 0,1,2,...,n-1，对应最坏情况“隔一个字符切一刀”
        for (int i = 1; i < n; ++i) {  // 从左往右计算每个前缀
            for (int j = 0; j <= i; ++j) {  // 枚举最后一段回文的起点 j，即 s[j..i]
                if (g[j][i]) {  // 只有 s[j..i] 回文才能把它当作最后一段
                    f[i] = min(f[i], j ? 1 + f[j - 1] : 0);  // j 为 0 说明整段前缀就是回文、不用切；否则在前缀 f[j-1] 后多加一刀
                }
            }
        }
        return f[n - 1];  // 整个字符串的最少切分数
    }
};